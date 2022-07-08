// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerInterface_HUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTING_API APlayerInterface_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerInterface_HUD();
	virtual void BeginPlay() override;

public:
	void SetCurrentBullet(int nMissionClear, bool bIsSpecial);
	void SetDefaultBullet(bool bIsSpecial);
	void SetGunName(FString strGunName);

private:
	TSubclassOf<class UPlayerInterfaceMain_UW> MainUIClass;
	class UPlayerInterfaceMain_UW* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
