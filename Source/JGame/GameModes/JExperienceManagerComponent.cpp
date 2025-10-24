// Fill out your copyright notice in the Description page of Project Settings.


#include "JExperienceManagerComponent.h"
#include "JGame/System/JAssetManager.h"
#include "JGame/GameModes/JExperienceDefinition.h"

void UJExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnJExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}

void UJExperienceManagerComponent::ServerSetCurrentExperience(FPrimaryAssetId ExperienceId)
{
	UJAssetManager& AssetManager = UJAssetManager::Get();

	TSubclassOf<UJExperienceDefinition> AssetClass;
	{
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
		AssetClass = Cast<UClass>(AssetPath.TryLoad());
	}

	const UJExperienceDefinition* Experience = GetDefault<UJExperienceDefinition>(AssetClass);
	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	{
		CurrentExperience = Experience;
	}

	StartExperienceLoad();
}

void UJExperienceManagerComponent::StartExperienceLoad()
{
}

void UJExperienceManagerComponent::OnExperienceLoadComplete()
{
}

void UJExperienceManagerComponent::OnExperienceFullLoadCompleted()
{
}
