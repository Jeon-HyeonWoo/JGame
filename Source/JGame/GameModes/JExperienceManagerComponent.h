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
 *	해당 Component는 GameState를 Owner로 가지며, Experience의 상태 정보를 가지고 있다.
 *	Experience의 로딩 상태 업데이트 및 이벤트를 관리한다.
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
