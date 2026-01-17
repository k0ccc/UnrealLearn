// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBPSortActors.h"

void UMyBPSorActors::SortActors(UPARAM(ref) TArray<AActor *> &ActorsToSort, bool bAscending)
{
    ActorsToSort.Sort([bAscending](const AActor &A, const AActor &B)
        {
        // Проверка на валидность указателей (на случай мусора в массиве)
        if (!IsValid(&A) || !IsValid(&B)) return false; 

        if (bAscending)
        {
            return A.GetActorLabel() < B.GetActorLabel();
        }
        else
        {
            return A.GetActorLabel() > B.GetActorLabel();
        } });
}