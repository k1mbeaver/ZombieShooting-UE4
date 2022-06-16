// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZombieShooting_PC.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTING_API AZombieShooting_PC : public APlayerController
{
	GENERATED_BODY()
		AZombieShooting_PC();
public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PostInitializeComponents() override; // 여기서 빙의되는지 알 수 있음
	virtual void SetupInputComponent() override;

private:
	//UPROPERTY()
	//class AZombieShootingCharacter* myCharacter;

protected:
	//UFUNCTION()
	//void MoveForward(float Val);
	//UFUNCTION()
	//void MoveRight(float Val);
	//UFUNCTION()
	//void TurnAtRate(float Rate);
	//UFUNCTION()
	//void LookUpAtRate(float Rate);
};
