// Fill out your copyright notice in the Description page of Project Settings.


#include "JGameModeBase.h"
#include "JGameStateBase.h"
#include "JGame/Player/JPlayerState.h"
#include "JGame/Player/JPlayerController.h"
#include "JGame/Character/JCharacter.h"

AJGameModeBase::AJGameModeBase()
{
	GameStateClass = AJGameStateBase::StaticClass();
	PlayerStateClass = AJPlayerState::StaticClass();
	PlayerControllerClass = AJPlayerController::StaticClass();
	DefaultPawnClass = AJCharacter::StaticClass();

}
