// Fill out your copyright notice in the Description page of Project Settings.


#include "JGameModeBase.h"
#include "JGameStateBase.h"
#include "JGame/Player/JPlayerState.h"
#include "JGame/Player/JPlayerController.h"
#include "JGame/Character/JCharacter.h"
#include "JExperienceManagerComponent.h"

AJGameModeBase::AJGameModeBase()
{
	GameStateClass = AJGameStateBase::StaticClass();
	PlayerStateClass = AJPlayerState::StaticClass();
	PlayerControllerClass = AJPlayerController::StaticClass();
	DefaultPawnClass = AJCharacter::StaticClass();
}
void AJGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	/*
	* - 모든 액터가 BeginPlay()초기화 설정을 다 마친 이후.
	* - InitGame은 극 초기 단계라 Experience가 생성되기 이전 임으로, 한 프레임 이후에 실행시킨다.
	*/
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void AJGameModeBase::InitGameState()
{
	Super::InitGameState();

	UJExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnJExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AJGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{

}

void AJGameModeBase::OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience)
{

}
