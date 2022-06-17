// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZombieShootingGameMode.h"
#include "ZombieShootingHUD.h"
#include "ZombieShootingCharacter.h"
#include "ZombieShooting_PC.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieShootingGameMode::AZombieShootingGameMode()
	//: Super()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AMyCharacter::StaticClass();
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// PlayerController
	PlayerControllerClass = AZombieShooting_PC::StaticClass();

	// use our custom HUD class
	HUDClass = AZombieShootingHUD::StaticClass();
}

void AZombieShootingGameMode::PostLogin(APlayerController* NewPlayer)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin End"));

}