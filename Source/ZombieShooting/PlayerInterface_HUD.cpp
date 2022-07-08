// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInterface_HUD.h"
#include "PlayerInterfaceMain_UW.h"

APlayerInterface_HUD::APlayerInterface_HUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerInterfaceMain_UW> WB_Main(TEXT("WidgetBlueprint'/Game/Widget/PlayerInterfaceMain_WB'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerInterface_HUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
}

bool APlayerInterface_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI�� ���ٸ� ����.
	{
		return CreateUIObject();
	}
	return true; // �ִٸ� True.
}

bool APlayerInterface_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerInterfaceMain_UW>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // ������ٸ� true.
		}
	}
	return false; // �� ������ٸ� false.
}

void APlayerInterface_HUD::SetCurrentBullet(int nCurrentBullet, bool bIsSpecial)
{
	MainUIObject->SetCurrentBullet(nCurrentBullet, bIsSpecial);
}

void APlayerInterface_HUD::SetDefaultBullet(bool bIsSpecial)
{
	MainUIObject->SetDefaultBullet(bIsSpecial);
}

void APlayerInterface_HUD::SetGunName(FString strGunName)
{
	MainUIObject->SetGunName(strGunName);
}
