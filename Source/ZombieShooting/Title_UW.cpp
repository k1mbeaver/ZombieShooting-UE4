// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_UW.h"
#include "Components/Button.h"
#include "Title_PC.h"

void UTitle_UW::NativeConstruct()
{
	Super::NativeConstruct();

	BtPlay->OnClicked.AddDynamic(this, &UTitle_UW::PlayHandler);
	BtReplay->OnClicked.AddDynamic(this, &UTitle_UW::ReplayHandler);
	BtSetting->OnClicked.AddDynamic(this, &UTitle_UW::SettingHandler);
	BtExit->OnClicked.AddDynamic(this, &UTitle_UW::ExitHandler);
}

void UTitle_UW::PlayHandler()
{
	// ����ٰ� PC ����
	ATitle_PC* MyPC = Cast<ATitle_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->PlayGame();
	}
}

void UTitle_UW::ReplayHandler()
{
	// ����ٰ� PC ����
	ATitle_PC* MyPC = Cast<ATitle_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->ReplayGame();
	}
}

void UTitle_UW::SettingHandler()
{
	// ����ٰ� PC ����
	ATitle_PC* MyPC = Cast<ATitle_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->SettingGame();
	}
}

void UTitle_UW::ExitHandler()
{
	// ����ٰ� PC ����
	ATitle_PC* MyPC = Cast<ATitle_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->ExitGame();
	}
}

