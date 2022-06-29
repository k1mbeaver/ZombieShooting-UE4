// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"
#include "NavigationSystem.h"
#include "MyAICharacter.h"
#include "MyGameInstance.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	static ConstructorHelpers::FObjectFinder<AMyAICharacter> AI_CHARACTER(TEXT("Blueprint'/Game/BluePrints/BP_MyAICharacter.BP_MyAICharacter'"));
	if (AI_CHARACTER.Succeeded())
	{
		DefaultAI = AI_CHARACTER.Object;
	}
	*/
}

void AAISpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	//nHowManyAI = MyGI->GetPlayerStage();
}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();


	/*
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	
	for (int i = 0; i < 3; i++)
	{
		FNavLocation SpawnLocation;
		NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 4000.0f, SpawnLocation);

		GetWorld()->SpawnActor<AMyAICharacter>(AMyAICharacter::StaticClass(), SpawnLocation.Location, FName("None");
	}
	*/
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AAISpawner::GetPlayerStageAI()
{
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	int nHowManyAI = MyGI->GetPlayerStage();

	return nHowManyAI;
}

