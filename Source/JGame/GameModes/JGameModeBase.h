// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JGameModeBase.generated.h"

class UJExperienceDefinition;
/**
 * 
 */
UCLASS()
class JGAME_API AJGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AJGameModeBase();
	

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	/* GameStateBase의 생성자가 완료된 이후 */
	virtual void InitGameState() override;

public:
	/*
	* member method
	*/
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience);

};
