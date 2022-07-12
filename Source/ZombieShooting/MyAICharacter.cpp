// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "MonsterHP_UW.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.h"
#include "ZombieShooting_AC.h"
#include "MyCharacter.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "MyGameInstance.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_EASYMODEL(TEXT("/Game/File/Mesh/Grux.Grux"));
	if (SK_EASYMODEL.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_EASYMODEL.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrints/Grux_AnimBlueprint.Grux_AnimBlueprint_C"));
	if (PLAYER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// ĳ���Ͱ� �ڿ������� ȸ���ϰ� 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MyAI"));

	// To Damage Particle
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(GetCapsuleComponent());
	MuzzleLocation->SetRelativeLocation(FVector(50.0f, 20.0f, 35.0f));

	/*
	AIWidget = CreateDefaultSubobject<UWidgetComponent>("HPBar");
	static ConstructorHelpers::FClassFinder<UUserWidget> MONSTER_HP(TEXT("/Game/Widget/MonsterHP_WB"));

	if (MONSTER_HP.Succeeded())
	{
		MONSTER_HPClass = MONSTER_HP.Class;
	}

	AIWidget->SetWidgetSpace(EWidgetSpace::World);
	AIWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	AIWidget->SetWidgetClass(MONSTER_HPClass);
	AIWidget->SetVisibility(true);
	AIWidget->RegisterComponent();
	*/

	// Damage effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DAMAGE(TEXT("ParticleSystem'/Game/ParagonGrux/FX/Particles/Abilities/Primary/FX/P_Grux_ApplyBleed.P_Grux_ApplyBleed'"));
	if (DAMAGE.Succeeded())
	{
		DamageParticle = DAMAGE.Object;
	}

	AIControllerClass = AZombieShooting_AC::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttackRange = 250.0f;
	AttackRadius = 50.0f;
	IsAttacking = false;
}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	nMonsterCount = MyGI->GetPlayerStage();
	fAIHp = MyGI->GetMonsterHp("GeneralMonster");
	fMaxHp = fAIHp;
	AttackPower = MyGI->GetMonsterAttackDamage("GeneralMonster");
}

// Called every frame
void AMyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AIAnim = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());

	// �������� �ּ� ó���� ����
	//AIAnim->OnMontageEnded.AddDynamic(this, &AMyAICharacter::OnAttackMontageEnded);

	//AIAnim->OnOnCollisonStart_Attack.AddUObject(this, &AMyAICharacter::AttackCheck);
}
	

void AMyAICharacter::Attack()
{
	auto AnimInstance = Cast<UAIAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayAttackMontage();
}

void AMyAICharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3, // Attack ä�� player�� ��쿡�� �浹 �Ѵ�
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	// �̰Ŵ� �����Ϳ����� ����ϴ°�
	
	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
	
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPunch!")); // �÷��̾ ��ġ�ϴ��� Ȯ�ο�

#endif


	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
			FDamageEvent DamageEvent;
			AMyCharacter* HitCharacter = Cast<AMyCharacter>(HitResult.Actor);
			HitCharacter->TakeDamage(AttackPower, DamageEvent, GetController(), this);
		}
	}
}

void AMyAICharacter::AttackByPlayer(float DamageAmount)
{
	fAIHp -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("AIHit!"));

	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	//GameStatic->SpawnEmitterAttached(DamageParticle, MuzzleLocation, FName("MuzzleLocation"));

	if (fAIHp == 0) // �ǰ� �� ���̸�
	{
		// ��� �ִϸ��̼� ���
		AIAnim->SetDeadAnim();
		
		// �����̺�� Ʈ�� ����
		StopAIController();

		// ���� �ν��Ͻ��� ���� ����� ����
		MyGI->nMonsterDeath++;
	}

	// ���������� ���Ͱ� ��� ������
	if (MyGI->nMonsterDeath == nMonsterCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("GameEnd!"));
		MyGI->SetPlayerStage();
		UGameplayStatics::OpenLevel(GetWorld(), FName("ConceptMap"));
	}

}

void AMyAICharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void AMyAICharacter::StopAIController()
{
	AZombieShooting_AC* AIController = Cast<AZombieShooting_AC>(GetController());

	AIController->StopAI();
}
