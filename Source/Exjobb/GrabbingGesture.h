// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/PoseableMeshComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Math/Vector.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "GrabbingGesture.generated.h"


/**
 *
 */
UCLASS()
class EXJOBB_API UGrabbingGesture : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Hand Tracking Category")
		static bool RecordGesture(UPoseableMeshComponent* hand, FString Directory, FString GestureName);

	UFUNCTION(BlueprintCallable, Category = "Hand Tracking Category")
		static TArray <FVector> ReadGestures(TArray<FString> Directory);

	UFUNCTION(BlueprintCallable, Category = "Hand Tracking Category")
		static FString DoesGestureExist(UPoseableMeshComponent* hand, TArray<FVector> WhatGesture);

	UFUNCTION(BlueprintCallable, Category = "Hand Tracking Category")
		static FString DoActionOrNot(FString Gesture, bool& IsPointLeft, bool& IsPalmOpenLeft, bool& IsPointRight, bool& IsPalmOpenRight, bool leftHand, bool rightHand);

};


