// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyLightActor.generated.h"

UCLASS()
class MYPROJECT2_API AMyLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyLightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Компонент лампочки (Point Light)
	// VisibleAnywhere = видно в редакторе, BlueprintReadOnly = нельзя удалить переменную, но можно менять свойства
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Components")
	class UPointLightComponent *PointLight;

	// Компонент триггера (Sphere)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Components")
	class USphereComponent *TriggerSphere;

	// Функция, которая сработает при выходе из триггера
	// UFUNCTION() обязателен, чтобы движок мог вызвать эту функцию как событие!
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
	bool bLightToggle;
};
