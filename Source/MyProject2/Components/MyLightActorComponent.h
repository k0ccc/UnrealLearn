// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyLightActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UMyLightActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyLightActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION()
	void OnOwnerEndOverlap(AActor *OverlappedActor, AActor *OtherActor);

private:
	// Сюда мы сохраним ссылку на лампочку, которую найдем
	// ULightComponent - это "родитель" для всех ламп (Point, Spot, Rect)
	UPROPERTY()
	class ULightComponent *FoundLight;
};
