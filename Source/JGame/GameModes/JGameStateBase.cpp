// Fill out your copyright notice in the Description page of Project Settings.


#include "JGameStateBase.h"
#include "JExperienceManagerComponent.h"

AJGameStateBase::AJGameStateBase()
{
	ExperienceManagerComponent = CreateDefaultSubobject<UJExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));

}
