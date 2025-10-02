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

	UJAssetManager();

	static UJAssetManager& Get();
};
