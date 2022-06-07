// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_PC.h"
#include "MainTitle_UW.h"
#include "Kismet/GameplayStatics.h"
// #include "PlayerInstance.h" ���� ���

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
	// ���⼭ GameInstance�� ����ؼ� Json ������ ����Ʈ ������ �����ϰ�

	// �װſ� �´� ������ �����Ѵ�. (�̰ŵ� GameInstance �� ���� OpenLevel �ϵ��� ��������)
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonExampleMap"));
}

void ATitle_PC::ReplayGame()
{
	// ���⼭ GameInstance�� ����ؼ� ���� �ִ� Json ������ �о�ͼ� �� ����� 

	// �װſ� �´� ������ �����Ѵ�. (�̰ŵ� GameInstance �� ���� OpenLevel �ϵ��� ��������)
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonExampleMap"));
}

void ATitle_PC::SettingGame()
{
	// Setting �ϴ� â���� ���� ���� ������ �̵�
}

void ATitle_PC::ExitGame()
{
	// ����
}