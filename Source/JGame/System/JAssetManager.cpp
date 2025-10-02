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
		//Sync Load�� �ð� üũ
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronous Loaded Asset [%s]"), *AssetPath.ToString()),
				nullptr,
				FScopeLogTime::ScopeLog_Seconds
			);
		}

		//AssetManager�� Sync Load ����
		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		//AssetManager�� Ȱ��ȭ�� �� �Ǿ��� ���, Manager�� ��ġ�� �ʰ� Load����, TryLoad�� ������ ������.
		return AssetPath.TryLoad();
	}

	return nullptr;
}
