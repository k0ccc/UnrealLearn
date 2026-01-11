// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLightActor.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
// Sets default values
AMyLightActor::AMyLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Включаем Tick только если нужно (для оптимизации лучше выключить, если не используем)
	PrimaryActorTick.bCanEverTick = false;

	// 1. Создаем сферу
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	RootComponent = TriggerSphere;							 // Делаем сферу корнем (или создай SceneComponent для корня)
	TriggerSphere->InitSphereRadius(200.0f);				 // Радиус по умолчанию
	TriggerSphere->SetCollisionProfileName(TEXT("Trigger")); // Настраиваем коллизию как триггер

	// 2. Создаем свет
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent); // Прикрепляем свет к сфере
}

// Called when the game starts or when spawned
void AMyLightActor::BeginPlay()
{
	Super::BeginPlay();

	// Проверяем, существует ли сфера (защита от краша)
	if (TriggerSphere)
	{
		// Это аналог красной нити "Event" в блюпринтах.
		// Мы говорим: "Когда случится OnComponentEndOverlap, вызови мою функцию OnOverlapEnd"
		TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AMyLightActor::OnOverlapEnd);
		TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyLightActor::OnOverlapBegin);
	}
}

// Called every frame
void AMyLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyLightActor::OnOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	// Проверяем, что свет существует и тот, кто вышел - не сама лампочка
	if (PointLight && OtherActor && OtherActor != this && !bLightToggle)
	{
		bLightToggle = true;
		// Логика: Выключаем видимость (или переключаем через ToggleVisibility)
		PointLight->SetVisibility(false);

		// Для отладки (выведет текст на экран)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Свет погас!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, bLightToggle ? TEXT("true") : TEXT("false"));
	}
}

void AMyLightActor::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (PointLight && OtherActor && OtherActor != this && bLightToggle)
	{
		bLightToggle = false;
		PointLight->SetVisibility(true);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Свет!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, bLightToggle ? TEXT("true") : TEXT("false"));
	}
}