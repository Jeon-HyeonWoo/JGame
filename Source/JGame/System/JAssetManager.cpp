// Fill out your copyright notice in the Description page of Project Settings.


#include "JAssetManager.h"
#include "JGame/JLogChannels.h"

UJAssetManager::UJAssetManager()
{
}

UJAssetManager& UJAssetManager::Get()
{
	check(GEngine);

	if (UJAssetManager* Singleton = Cast<UJAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(JLog, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini(Project Setting), It must be JAssetManager"));

	//Dummy for Complie
	return *NewObject<UJAssetManager>();
}

bool UJAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLineContent = FCommandLine::Get();

	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));

	return bLogAssetLoads;
}

UObject* UJAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		//Sync Load의 시간 체크
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronous Loaded Asset [%s]"), *AssetPath.ToString()),
				nullptr,
				FScopeLogTime::ScopeLog_Seconds
			);
		}

		//AssetManager로 Sync Load 진행
		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		//AssetManager가 활성화가 안 되었을 경우, Manager를 거치지 않고 Load시행, TryLoad는 굉장히 느리다.
		return AssetPath.TryLoad();
	}

	return nullptr;
}
