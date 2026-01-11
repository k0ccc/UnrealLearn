// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLightActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"

// Sets default values for this component's properties
UMyLightActorComponent::UMyLightActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMyLightActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// 1. Получаем ссылку на того, к кому прицепили этот компонент (наш Актор)
	AActor *Owner = GetOwner();
	if (!Owner)
		return; // Если владельца нет (странно, но бывает), выходим

	// 2. Ищем у владельца ЛЮБОЙ компонент света
	// FindComponentByClass ищет первый попавшийся компонент этого типа
	FoundLight = Owner->FindComponentByClass<ULightComponent>();

	if (FoundLight)
	{
		// Опционально: Выведем в лог, что мы нашли лампу (синим цветом)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Чип подключен к: %s"), *Owner->GetName()));
	}
	else
	{
		// Если лампы нет, ругаемся в лог
		UE_LOG(LogTemp, Warning, TEXT("AutoLightSwitch: На акторе %s нет лампочки!"), *Owner->GetName());
	}

	// 3. Подписываемся на событие самого Актора
	// Это значит: "Если кто-то перестанет пересекать границы моего Владельца (Owner), сообщи мне".
	Owner->OnActorEndOverlap.AddDynamic(this, &UMyLightActorComponent::OnOwnerEndOverlap);
}

void UMyLightActorComponent::OnOwnerEndOverlap(AActor *OverlappedActor, AActor *OtherActor)
{
	if (FoundLight && OtherActor && OtherActor != OverlappedActor)
	{
		// Выключаем свет (или можно сделать ToggleVisibility)
		FoundLight->SetVisibility(false);
	}
}

