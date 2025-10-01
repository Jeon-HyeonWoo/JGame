// Copyright Epic Games, Inc. All Rights Reserved.

#include "JGame.h"
#include "Modules/ModuleManager.h"

class FJGameModule : public FDefaultGameModuleImpl
{
public:

	virtual void StartupModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("Module Startup Test"));
	}

	virtual void ShutdownModule() override
	{

	}
};



IMPLEMENT_PRIMARY_GAME_MODULE(FJGameModule, JGame, "JGame");
