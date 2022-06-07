// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_PC.h"
#include "MainTitle_UW.h"
#include "Kismet/GameplayStatics.h"
// #include "PlayerInstance.h" 만들어서 사용

ATitle_PC::ATitle_PC()
{
	static ConstructorHelpers::FClassFinder<UMainTitle_UW> WBTitle(TEXT("WidgetBlueprint'/Game/Widget/MainTitle_WB.MainTitle_WB_C'"));
	if (WBTitle.Succeeded())
	{
		TitleUIClass = WBTitle.Class;
	}
}

void ATitle_PC::BeginPlay()
{
	Super::BeginPlay();

	TitleUIObject = CreateWidget<UMainTitle_UW>(this, TitleUIClass);
	TitleUIObject->AddToViewport();
	TitleUIObject->SetVisibility(ESlateVisibility::Hidden);

	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());

	FTimerHandle StartAnimDelayTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StartAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TitleUIObject->SetVisibility(ESlateVisibility::Visible);
		}), 1.0f, false);
}

void ATitle_PC::PlayGame()
{
	// 여기서 GameInstance를 사용해서 Json 파일을 디폴트 값으로 설정하고

	// 그거에 맞는 레벨을 실행한다. (이거도 GameInstance 값 따라서 OpenLevel 하도록 설정하자)
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonExampleMap"));
}

void ATitle_PC::ReplayGame()
{
	// 여기서 GameInstance를 사용해서 원래 있던 Json 파일을 읽어와서 그 값대로 

	// 그거에 맞는 레벨을 실행한다. (이거도 GameInstance 값 따라서 OpenLevel 하도록 설정하자)
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonExampleMap"));
}

void ATitle_PC::SettingGame()
{
	// Setting 하는 창으로 가기 위한 레벨로 이동
}

void ATitle_PC::ExitGame()
{
	// 종료
}