// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerDataTableClass.h"

UMyGameInstance::UMyGameInstance()
{
	FString PlayerDataPath = TEXT("DataTable'/Game/File/Json/PlayerData.PlayerData'");
	//E:/Unreal/ZombieShooting/Content/File/Json/PlayerData.uasset
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYER(*PlayerDataPath);
	if (DT_ABPLAYER.Succeeded())
	{
		FPlayerTable = DT_ABPLAYER.Object;
	}
}

/*
void UMyGameInstance::JsonSave()
{
	
	FString jsonstr;
	TSharedRef<TJsonWriter<TCHAR>> jsonObj = TJsonWriterFactory<>::Create(&jsonstr);

	jsonObj->WriteObjectStart();
	jsonObj->WriteValue<const char*>("Name", "Player1");
	jsonObj->WriteValue<int>("Hp", 100);
	jsonObj->WriteValue<const char*>("Gun", "Riffle");
	jsonObj->WriteValue<int>("Stage", 1);
	jsonObj->WriteObjectEnd();
	jsonObj->Close();

	FFileHelper::SaveStringToFile(*jsonstr, TEXT("/Game/File/Json/PlayerData.json"));
	
}

// �̰� �̾��ϱ⿡�� �������
void UMyGameInstance::JsonLoad()
{
	
	FString result;
	FFileHelper::LoadFileToString(result, *(FPaths::GameDevelopersDir()+"PlayerData.Json"));
	TSharedPtr<FJsonValue> jsonObject;
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(result);
	if (FJsonSerializer::Deserialize(reader, jsonObject))
	{
		const TArray<TSharedPtr<FJsonValue>> arr = jsonObject->AsArray();
		for (auto it = arr.CreateConstIterator(); it; it++)
		{
			FString val = (*it)->AsObject()->GetStringField("Name");
			myPlayerData.Name = val;
			val = (*it)->AsObject()->GetStringField("Hp");
			myPlayerData.Hp = FCString::Atoi(*val);
			val = (*it)->AsObject()->GetStringField("Gun");
			myPlayerData.Gun = val;
			val = (*it)->AsObject()->GetStringField("Stage");
			myPlayerData.Stage = FCString::Atoi(*val);
		}
	}
	
}
*/
FString UMyGameInstance::GetPlayerName()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	FString PlayerName = PlayerData->PlayerName;
	return PlayerName;
}

int UMyGameInstance::GetPlayerHp()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	int PlayerHp = PlayerData->PlayerHp;
	return PlayerHp;
}

FString UMyGameInstance::GetPlayerGun()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	FString PlayerGun = PlayerData->PlayerGun;
	return PlayerGun;
}

int UMyGameInstance::GetPlayerStage()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	int PlayerStage = PlayerData->PlayerStage;
	return PlayerStage;
}

float UMyGameInstance::GetPlayerBgmPower()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	float PlayerBgmPower = PlayerData->PlayerBgmPower;
	return PlayerBgmPower;
}

void UMyGameInstance::SetPlayerBgmPower(float fBgmPower)
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	PlayerData->PlayerBgmPower = fBgmPower;
}

void UMyGameInstance::SetPlayerDataDefault()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("PlayerInfo", TEXT(""));
	PlayerData->PlayerName = "Player";
	PlayerData->PlayerHp = 100;
	PlayerData->PlayerGun = "Punch";
	PlayerData->PlayerStage = 1;
}