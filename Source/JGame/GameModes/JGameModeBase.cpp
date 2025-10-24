// Fill out your copyright notice in the Description page of Project Settings.


#include "JGameModeBase.h"
#include "JGameStateBase.h"
#include "JGame/Player/JPlayerState.h"
#include "JGame/Player/JPlayerController.h"
#include "JGame/Character/JCharacter.h"
#include "JExperienceManagerComponent.h"
#include "JGame/JLogChannels.h"

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

void AJGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	/*
	*  Experience is not loaded, player can not enter the game
	*/
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

APawn* AJGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(JLog, Log, TEXT("SpawnDefaultPawnAtTransform_Implementation is called!"));
	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void AJGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("JExperienceDefinition"), FName("B_DefaultExperience"));
	}

	OnMatchAssignmentGiven(ExperienceId);
}

void AJGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	check(ExperienceId.IsValid());

	UJExperienceManagerComponent* ExperienceManagerComponent = GameState->GetComponentByClass<UJExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->ServerSetCurrentExperience(ExperienceId);
}

bool AJGameModeBase::IsExperienceLoaded() const
{
	check(GameState);
	UJExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	return ExperienceManagerComponent->IsExperienceLoaded();
}

void AJGameModeBase::OnExperienceLoaded(const UJExperienceDefinition* CurrentExperience)
{

}
