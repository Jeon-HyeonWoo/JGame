// Fill out your copyright notice in the Description page of Project Settings.


#include "JAssetManager.h"
#include "JGame/JLogChannels.h"

UJAssetManager::UJAssetManager()
{
}

UJAssetManager& UJAssetManager::Get()
{
	check(GEngine);

	if (UJAssetManager* Singleton = Cast<UJAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(JLog, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini(Project Setting), It must be JAssetManager"));

	//Dummy for Complie
	return *NewObject<UJAssetManager>();
}
