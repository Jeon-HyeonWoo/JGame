// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JExperienceDefinition.generated.h"

/*
* forward declare
*/

class UJPawnData;
/**
 * 
 */
UCLASS()
class JGAME_API UJExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UJExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());




public:
	/*
	* member variable 
	*/
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<UJPawnData> DefaultPawnData;
	
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;
};
