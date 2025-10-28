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
	* - ��� ���Ͱ� BeginPlay()�ʱ�ȭ ������ �� ��ģ ����.
	* - InitGame�� �� �ʱ� �ܰ�� Experience�� �����Ǳ� ���� ������, �� ������ ���Ŀ� �����Ų��.
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
	//World�� PlayerController�� ��ȸ
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);

		//PlayerController�� Pawn�� Possess���� �ʾҴٸ�, ReStartPlayer�� ���� Pawn�� �ٽ� Spawn�Ѵ�.
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
	* PlayerState�� Cache�� �Ǿ� �ִٸ�, PlayerState���� PawnData�� ��������,
	* �ƴ϶��, Experience�� ������ PawnData�� �����ϰ� ��������
	*/
	/*
	* PawnData�� override ���� ���, PawnData�� PlayerState���� �����´�.
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
