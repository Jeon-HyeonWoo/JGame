// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JUserFacingExperience.generated.h"

/**
 * 
 */
UCLASS()
class JGAME_API UJUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	/* the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapID;
	
	/* the gameplay experience to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "JExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
	
};
