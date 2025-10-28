// Fill out your copyright notice in the Description page of Project Settings.


#include "JPlayerState.h"
#include "../GameModes/JExperienceManagerComponent.h"
#include "JGame/GameModes/JGameModeBase.h"

void AJPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UJExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnJExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	
}

void AJPlayerState::OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience)
{
	/*
	* GetAuthGameMode = Get World Current GameMode
	*/
	if (AJGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AJGameModeBase>())
	{
		const UJPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

void AJPlayerState::SetPawnData(const UJPawnData* InPawnData)
{
	check(InPawnData);

	check(!PawnData); 

	PawnData = InPawnData;
}
