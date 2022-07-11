// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInterfaceMain_UW.h"
#include "PlayerInterface_UW.h"

void UPlayerInterfaceMain_UW::SetCurrentBullet(int nCurrentBullet, bool bIsSpecial)
{
	PlayerInterface_WB->SetCurrentBullet(nCurrentBullet, bIsSpecial);
}

void UPlayerInterfaceMain_UW::SetDefaultBullet(bool bIsSpecial)
{
	PlayerInterface_WB->SetDefaultBullet(bIsSpecial);
}

void UPlayerInterfaceMain_UW::SetGunName(FString strGunName)
{
	PlayerInterface_WB->SetGunName(strGunName);
}

void UPlayerInterfaceMain_UW::SetPlayerHP(float fCurrentHP)
{
	PlayerInterface_WB->SetPlayerHP(fCurrentHP);
}