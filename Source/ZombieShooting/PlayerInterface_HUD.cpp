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

	CheckUIObject(); // 시작하면 UI를 생성한다.
}

bool APlayerInterface_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI가 없다면 생성.
	{
		return CreateUIObject();
	}
	return true; // 있다면 True.
}

bool APlayerInterface_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerInterfaceMain_UW>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // 만들었다면 true.
		}
	}
	return false; // 못 만들었다면 false.
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
