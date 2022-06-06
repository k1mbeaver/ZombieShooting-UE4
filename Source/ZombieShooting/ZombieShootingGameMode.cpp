// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZombieShootingGameMode.h"
#include "ZombieShootingHUD.h"
#include "ZombieShootingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieShootingGameMode::AZombieShootingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AZombieShootingHUD::StaticClass();
}
