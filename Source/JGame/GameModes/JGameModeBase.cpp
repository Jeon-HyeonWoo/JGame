// Fill out your copyright notice in the Description page of Project Settings.


#include "JGameModeBase.h"
#include "JGameStateBase.h"
#include "JGame/Player/JPlayerState.h"
#include "JGame/Player/JPlayerController.h"
#include "JGame/Character/JCharacter.h"
#include "JExperienceManagerComponent.h"
#include "JGame/JLogChannels.h"
#include "JGame/Character/JPawnData.h"
#include "JGame/GameModes/JExperienceDefinition.h"

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

UClass* AJGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const UJPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
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
	//World의 PlayerController를 순회
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);

		//PlayerController가 Pawn을 Possess하지 않았다면, ReStartPlayer를 통해 Pawn을 다시 Spawn한다.
		if (PC && PC->GetPawn() == nullptr)
		{
			if (PlayerCanRestart(PC))
			{
				/*
				* Same Spawn Player Actor Logic
				* 1. FindPlayerStartSpot
				* 2. if PawnClass is nullptr, Spawned DefualtPawn
				*/
				RestartPlayer(PC);
			}
		}
	}
}

const UJPawnData* AJGameModeBase::GetPawnDataForController(const AController* InController) const
{
	/*
	* PlayerState가 Cache가 되어 있다면, PlayerState에서 PawnData를 가져오기,
	* 아니라면, Experience에 지정된 PawnData를 안전하게 가져오기
	*/
	/*
	* PawnData가 override 됐을 경우, PawnData는 PlayerState에서 가져온다.
	*/
	if (InController)
	{
		if (const AJPlayerState* JPS = InController->GetPlayerState<AJPlayerState>())
		{
			if (const UJPawnData* PawnData = JPS->GetPawnData<UJPawnData>())
			{
				return PawnData;
			}
		}
	}

	check(GameState);
	UJExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UJExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	if (ExperienceManagerComponent->IsExperienceLoaded())
	{
		const UJExperienceDefinition* Experience = ExperienceManagerComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData)
		{
			return Experience->DefaultPawnData;
		}
	}

	return nullptr;
}
