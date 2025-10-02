// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "JAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class JGAME_API UJAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	//Constructor
	UJAssetManager();

	//Singleton Getter
	static UJAssetManager& Get();

	//Project Property -> Debugging -> Command Arguments -> Add Command Line
	//to determine to use FScopeLogTime
	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);
};
