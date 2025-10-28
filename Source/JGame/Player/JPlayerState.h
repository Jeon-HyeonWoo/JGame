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

	/*
	* AActor's Interface
	*/
	virtual void PostInitializeComponents() final;


	/*
	* member method
	*/
	template<class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }
	void OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience);
	void SetPawnData(const UJPawnData* InPawnData);

public:

	UPROPERTY()
	TObjectPtr<const UJPawnData> PawnData;
};
