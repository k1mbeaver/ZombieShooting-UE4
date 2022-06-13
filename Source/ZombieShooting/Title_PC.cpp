// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_PC.h"
#include "MainTitle_UW.h"
#include "Setting_UW.h"
#include "MainTitle_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

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
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	MyGI->SetPlayerDataDefault();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, MyGI->GetPlayerGun());
	// �װſ� �´� ������ �����Ѵ�. (�̰ŵ� GameInstance �� ���� OpenLevel �ϵ��� ��������)
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonExampleMap"));
}

void ATitle_PC::ReplayGame()
{
	// ���⼭ GameInstance�� ����ؼ� ���� �ִ� Json ������ �о�ͼ� �� ����� 
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, MyGI->GetPlayerGun());
	// �װſ� �´� ������ �����Ѵ�. (�̰ŵ� GameInstance �� ���� OpenLevel �ϵ��� ��������)
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonExampleMap"));
}

void ATitle_PC::SettingGame()
{
	AMainTitle_HUD* HUD = GetHUD<AMainTitle_HUD>();
	if (HUD == nullptr) return;
	// ���� GameInstance�� ���� ���� ���� Slider ���� �޶�����.

	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();

	HUD->SetBgmSlider(MyGI->GetPlayerBgmPower()); // ���⼭ gameinstance���� �����´�.
	// �� �Ŀ� Setting â�� ����.

	HUD->VisibleSetting();
}

void ATitle_PC::BackSetting()
{
	AMainTitle_HUD* HUD = GetHUD<AMainTitle_HUD>();
	if (HUD == nullptr) return;

	HUD->HiddenSetting();
}

void ATitle_PC::CheckSetting()
{
	AMainTitle_HUD* HUD = GetHUD<AMainTitle_HUD>();
	if (HUD == nullptr) return;
	// �Է��� ���� ���� GameInstance���� �޶�����.
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	MyGI->SetPlayerBgmPower(HUD->GetBgmPower()); // ���⼭ ���� GameInstance�� �ִ´�.
	// �� �Ŀ� setting â�� �����.

	
	HUD->HiddenSetting();
}

void ATitle_PC::ExitGame()
{
	// ����
}