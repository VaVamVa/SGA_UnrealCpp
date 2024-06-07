#pragma once

#include "CoreMinimal.h"


class Helper
{
public:
	template<typename T>
	static T* CreateSceneComponent(AActor* InOwner, FName InComponentName, USceneComponent* InParentComponent = nullptr)
	{
		T* Component = InOwner->CreateDefaultSubobject<T>(InComponentName);

		if (InParentComponent == nullptr)
			InOwner->SetRootComponent(Component);
		else
			Component->SetupAttachment(InParentComponent);
		
		return Component;
	}

	template<typename T>
	static T* CreateActorComponent(AActor* InOwner, FName InComponentName)
	{
		T* Component = InOwner->CreateDefaultSubobject<T>(InComponentName);
		return Component;
	}

	template<typename T>
	static T* GetAssetFromConstructor(FString Path)
	{
		ConstructorHelpers::FObjectFinder<T> Finder(*Path);

		if (Finder.Succeeded())
			return Cast<T>(Finder.Object);
		return nullptr;
	}

	template<typename T>
	static TSubclassOf<T> GetClassFromConstructor(FString Path)
	{
		ConstructorHelpers::FClassFinder<T> Finder(*Path);

		if (Finder.Succeeded())
			return Finder.Class;
		return nullptr;
	}



	/*
	Have to Follow Name Convention
	SK_ : Skeletal Mesh
	MI_ : Material
	*/
	static int32 MakeDataTableFromPath(FString RootPath, FString ColumName)
	{
		return 0;
	}
};


