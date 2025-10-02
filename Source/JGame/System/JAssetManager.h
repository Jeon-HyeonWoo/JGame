// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "JAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class JGAME_API UJAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	//Constructor
	UJAssetManager();

	/*
	* UAssetManager's Interface
	*/
	virtual void StartInitialLoading() override;

	//Singleton Getter
	static UJAssetManager& Get();

	//to determine to use FScopeLogTime
	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);
	
	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	/* Thread-Safe 메모리에 로딩된 에셋 캐싱 */
	void AddLoadedAsset(const UObject* Asset);

	//GC의 대상
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	//Object 단위의 Lock
	FCriticalSection SyncObject;
	
};

template<typename AssetType>
inline AssetType* UJAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();
	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();

		if (!LoadedAsset)
		{
			LoadedAsset = cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to Load Asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}
}

template<typename AssetType>
inline TSubclassOf<AssetType> UJAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();

		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to Load Asset class [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}
}

