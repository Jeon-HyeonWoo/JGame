// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "JExperienceManagerComponent.generated.h"

class UJExperienceDefinition;

enum class EJExperienceLoadState
{
	Unload,
	Loading,
	Loaded,
	Deactivating,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnJExperienceLoaded, const UJExperienceDefinition*);

/**
 *	�ش� Component�� GameState�� Owner�� ������, Experience�� ���� ������ ������ �ִ�.
 *	Experience�� �ε� ���� ������Ʈ �� �̺�Ʈ�� �����Ѵ�.
 */
UCLASS()
class JGAME_API UJExperienceManagerComponent : public UGameStateComponent //UGameFrameworkComponent, pulic ActorComponent
{
	GENERATED_BODY()
	
public:

	bool IsExperienceLoaded() { return (LoadState == EJExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }


	void CallOrRegister_OnExperienceLoaded(FOnJExperienceLoaded::FDelegate&& Delegate);
public:

	UPROPERTY()
	TObjectPtr<const UJExperienceDefinition> CurrentExperience;

	EJExperienceLoadState LoadState = EJExperienceLoadState::Unload;

	FOnJExperienceLoaded OnExperienceLoaded;
};
