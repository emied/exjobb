// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportationFunctionLibrary.h"

FRotator UTeleportationFunctionLibrary::FindPointingVector(UPoseableMeshComponent* leftHand, UPoseableMeshComponent* rightHand)
{
	FVector fingerEnd = rightHand->GetBoneLocationByName("r_index_finger_tip_marker", EBoneSpaces::WorldSpace);
	FVector fingerStart = rightHand->GetBoneLocationByName("r_index_pip_fe_axis_marker", EBoneSpaces::WorldSpace);
	FVector result = (fingerEnd - fingerStart).GetSafeNormal();
	FRotator resultRot = result.Rotation();
	return resultRot;
}
