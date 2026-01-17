// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBPSortActors.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMyBPSorActors : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "MyTools", meta = (DevelopmentOnly))
	static void SortActors(UPARAM(ref) TArray<AActor *> &ActorsToSort, bool bAscending);
};

