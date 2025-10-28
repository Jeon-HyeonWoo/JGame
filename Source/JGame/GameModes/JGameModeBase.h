// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JGameModeBase.generated.h"

class UJExperienceDefinition;
class UJPawnData;
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
	* HandleStartingNewPlayer
	* Signals that player is ready to enter the game
	*/
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) final;
	/*
	* SpawnDefaultPawnAtTransForm
	*/
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) final;
	/*
	* GetDefaultPawnClassForController
	*/
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) final;

	/*
	* member method
	*/
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);
	bool IsExperienceLoaded() const;
	void OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience);
	const UJPawnData* GetPawnDataForController(const AController* InController) const;

	
};
