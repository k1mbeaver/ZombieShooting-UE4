// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieShooting_PC.h"

void AZombieShooting_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
}

void AZombieShooting_PC::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
