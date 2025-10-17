// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JGameStateBase.generated.h"

class UJExperienceManagerComponent;

/**
 * 
 */
UCLASS()
class JGAME_API AJGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	AJGameStateBase();


public:
	UPROPERTY()
	TObjectPtr<UJExperienceManagerComponent> ExperienceManagerComponent;
};
