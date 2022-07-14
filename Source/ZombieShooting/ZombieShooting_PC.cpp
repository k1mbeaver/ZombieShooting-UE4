// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieShooting_PC.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieShooting_PC::AZombieShooting_PC()
{

}

void AZombieShooting_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (aPawn)
	{
		myCharacter = Cast<AMyCharacter>(aPawn);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
	}
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

	// ĳ���� �̵� �Լ�
	//InputComponent->BindAxis(TEXT("MoveForward"), this, &AZombieShooting_PC::UpDown);
	//InputComponent->BindAxis(TEXT("MoveRight"), this, &AZombieShooting_PC::LeftRight);
	//InputComponent->BindAxis(TEXT("LookUp"), this, &AZombieShooting_PC::LookUp);
	//InputComponent->BindAxis(TEXT("Turn"), this, &AZombieShooting_PC::Turn);

	// ĳ���� ���� �Լ�
	InputComponent->BindAction("Jump", IE_Pressed, this, &AZombieShooting_PC::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AZombieShooting_PC::StopJumping);

	// ĳ���� ���� �Լ�
	InputComponent->BindAction("Fire", IE_Pressed, this, &AZombieShooting_PC::OnFire);

	// ĳ���� �޸��� �Լ�
	InputComponent->BindAction("Run", IE_Pressed, this, &AZombieShooting_PC::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AZombieShooting_PC::StopRun);

	// ĳ���� ���� �Լ�
	InputComponent->BindAction("ReadyFire", IE_Pressed, this, &AZombieShooting_PC::ReadyFire);
	InputComponent->BindAction("ReadyFire", IE_Released, this, &AZombieShooting_PC::ResetReadyFire);

	// �÷��̾� �Ͻ����� �Լ�
	InputComponent->BindAction("Pause", IE_Pressed, this, &AZombieShooting_PC::PlayerPause);
}

/*
void AZombieShooting_PC::UpDown(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->UpDown(NewAxisValue);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("UpDown!"));
	}
}

void AZombieShooting_PC::LeftRight(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LeftRight(NewAxisValue);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftRight!"));
	}
}

void AZombieShooting_PC::LookUp(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LookUp(NewAxisValue);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LookUp!"));
	}
}

void AZombieShooting_PC::Turn(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->Turn(NewAxisValue);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Turn!"));
	}
}
*/

void AZombieShooting_PC::Jump()
{
	if (myCharacter)
	{
		myCharacter->Jump();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AZombieShooting_PC::StopJumping()
{
	if (myCharacter)
	{
		myCharacter->StopJumping();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopJumping!"));
	}
}

void AZombieShooting_PC::ReadyFire()
{
	if (myCharacter)
	{
		myCharacter->ReadyFire();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("ReadyFire!"));
	}
}

void AZombieShooting_PC::ResetReadyFire()
{
	if (myCharacter)
	{
		myCharacter->ResetReadyFire();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("ResetReadyFire!"));
	}
}

void AZombieShooting_PC::OnFire()
{
	if (myCharacter)
	{
		myCharacter->OnFire();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("OnFire!"));
	}
}

void AZombieShooting_PC::Run()
{
	if (myCharacter)
	{
		myCharacter->Run();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Run!"));
	}
}

void AZombieShooting_PC::StopRun()
{
	if (myCharacter)
	{
		myCharacter->StopRun();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

void AZombieShooting_PC::PlayerPause()
{
	if (myCharacter)
	{
		myCharacter->PlayerPause();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPause!"));
	}
}