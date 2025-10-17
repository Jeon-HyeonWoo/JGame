// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JPlayerState.generated.h"


class UJExperienceDefinition;
class UJPawnData;

/**
 * 
 */
UCLASS()
class JGAME_API AJPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	virtual void PostInitializeComponents() final;

	void OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience);

public:

	UPROPERTY()
	TObjectPtr<const UJPawnData> PawnData;
};
