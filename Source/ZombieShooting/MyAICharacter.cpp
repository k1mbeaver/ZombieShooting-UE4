// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.h"
#include "ZombieShooting_AC.h"
#include "MyCharacter.h"
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

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MyAI"));

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

	fAIHp = MyGI->GetMonsterHp("GeneralMonster");
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

	// 끄기전에 주석 처리후 빌드
	AIAnim->OnMontageEnded.AddDynamic(this, &AMyAICharacter::OnAttackMontageEnded);

	AIAnim->OnOnCollisonStart_Attack.AddUObject(this, &AMyAICharacter::AttackCheck);
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
		ECollisionChannel::ECC_GameTraceChannel3, // Attack 채널 player의 경우에만 충돌 한다
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	// 이거는 에디터에서만 사용하는거
	
	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
	
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPunch!")); // 플레이어가 펀치하는지 확인용

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

	if (fAIHp == 0) // 피가 다 까이면
	{
		AIAnim->SetDeadAnim();
		StopAIController();
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
