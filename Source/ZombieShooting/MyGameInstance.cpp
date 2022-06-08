// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::JsonSave()
{
	FString jsonstr;
	TSharedRef<TJsonWriter<TCHAR>> jsonObj = TJsonWriterFactory<>::Create(&jsonstr);

	jsonObj->WriteObjectStart();
	jsonObj->WriteValue("Name", "Player1");
	jsonObj->WriteValue("Hp", 100);
	jsonObj->WriteValue("Gun", "Riffle");
	jsonObj->WriteValue("Stage", "1");
	jsonObj->WriteObjectEnd();
	jsonObj->Close();

	FFileHelper::SaveStringToFile(*jsonstr, TEXT("/Game/File/Json/PlayerData.json'"));
}