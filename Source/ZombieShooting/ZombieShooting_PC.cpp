// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieShooting_PC.h"
#include "MyCharacter.h"

AZombieShooting_PC::AZombieShooting_PC()
{

}

void AZombieShooting_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	myCharacter = Cast<AMyCharacter>(aPawn);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
}

void AZombieShooting_PC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void AZombieShooting_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);

	// 움직임

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AZombieShooting_PC::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AZombieShooting_PC::MoveRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AZombieShooting_PC::LookUpAtRate);
	InputComponent->BindAxis(TEXT("Turn"), this, &AZombieShooting_PC::TurnAtRate);

	// 액션

	//InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABPlayerController::Jump);
	//InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AABPlayerController::CheckMission);
	//InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABPlayerController::Attack);
	//InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AABPlayerController::Run);
	//InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AABPlayerController::StopRun);
}


void AZombieShooting_PC::MoveForward(float Value)
{
	//APawn* const myPawn = GetPawn();
	//AZombieShootingCharacter* myCharacter = Cast<AZombieShootingCharacter>(myPawn);
	if (Value != 0.0f)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
		Direction.Z = 0.0f;
		Direction.Normalize();
		myCharacter->AddMovementInput(Direction, Value);
	}
}

void AZombieShooting_PC::MoveRight(float Value)
{
	//APawn* const myPawn = GetPawn();
	//AZombieShootingCharacter* myCharacter = Cast<AZombieShootingCharacter>(myPawn);
	if (Value != 0.0f)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);
		Direction.Z = 0.0f;
		Direction.Normalize();
		myCharacter->AddMovementInput(Direction, Value);
	}
}

void AZombieShooting_PC::TurnAtRate(float Rate)
{
	//APawn* const myPawn = GetPawn();
	//AZombieShootingCharacter* myCharacter = Cast<AZombieShootingCharacter>(myPawn);
	// calculate delta for this frame from the rate information
	myCharacter->AddControllerYawInput(Rate);
}

void AZombieShooting_PC::LookUpAtRate(float Rate)
{
	//APawn* const myPawn = GetPawn();
	//AZombieShootingCharacter* myCharacter = Cast<AZombieShootingCharacter>(myPawn);
	// calculate delta for this frame from the rate information
	myCharacter->AddControllerPitchInput(Rate);
}
