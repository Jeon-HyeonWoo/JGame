// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JPawnData.generated.h"

/**
 * 
 */
UCLASS()
class JGAME_API UJPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UJPawnData(const FObjectInitializer& ObjecetInitializer = FObjectInitializer::Get());
};
