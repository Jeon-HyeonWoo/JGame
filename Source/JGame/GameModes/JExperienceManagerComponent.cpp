// Fill out your copyright notice in the Description page of Project Settings.


#include "JExperienceManagerComponent.h"

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
