	// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZombieShootingProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyAICharacter.h"
#include "MyGameInstance.h"

AZombieShootingProjectile::AZombieShootingProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AZombieShootingProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.0f;
	ProjectileMovement->MaxSpeed = 5000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// BASIC
	AttackPower = 20.0f;
}

void AZombieShootingProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	FString GunName = MyGI->GetPlayerGun();

	if (GunName == TEXT("HEAVYBASIC"))
	{
		AttackPower = 100.0f;
	}

	else if (GunName == TEXT("SHOTGUN"))
	{
		AttackPower = 50.0f;
	}

	else
	{
		AttackPower = 20.0f;
	}

	if (Cast<AMyAICharacter>(Hit.Actor)) // 맞은 대상이 몬스터일 때
	{
		AMyAICharacter* HitCharacter = Cast<AMyAICharacter>(Hit.Actor);
		
		HitCharacter->AttackByPlayer(AttackPower);

		Destroy();
	}

	else
	{
		Destroy();
	}
	/*
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
	*/
}