// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/PoseableMeshComponent.h"
#include "TeleportationFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class EXJOBB_API UTeleportationFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Hand Tracking Category")
		static FRotator FindPointingVector(UPoseableMeshComponent* leftHand, UPoseableMeshComponent* rightHand, bool isLeftHand, bool isRightHand);
		
		UFUNCTION(BlueprintCallable, Category = "Hand Tracking Category")
		static FVector FindUsedHand(UPoseableMeshComponent* leftHand, UPoseableMeshComponent* rightHand, bool isLeftHand, bool isRightHand);

};
