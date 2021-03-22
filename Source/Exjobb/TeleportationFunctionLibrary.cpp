// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportationFunctionLibrary.h"

FRotator UTeleportationFunctionLibrary::FindPointingVector(UPoseableMeshComponent* leftHand, UPoseableMeshComponent* rightHand, bool isLeftHand, bool isRightHand)
{
	FRotator resultRot;

	if(isRightHand == true){
	FVector fingerEnd = rightHand->GetBoneLocationByName("r_index_finger_tip_marker", EBoneSpaces::WorldSpace);
	FVector fingerStart = rightHand->GetBoneLocationByName("r_index_pip_fe_axis_marker", EBoneSpaces::WorldSpace);
	FVector result = (fingerEnd - fingerStart).GetSafeNormal();
	resultRot = result.Rotation();

	}
	if (isLeftHand == true) {
		FVector fingerEnd = leftHand->GetBoneLocationByName("l_index_finger_tip_marker", EBoneSpaces::WorldSpace);
		FVector fingerStart = leftHand->GetBoneLocationByName("l_index_pip_fe_axis_marker", EBoneSpaces::WorldSpace);
		FVector result = (fingerEnd - fingerStart).GetSafeNormal();
		resultRot = result.Rotation();
	}

	return resultRot;
}

FVector UTeleportationFunctionLibrary::FindUsedHand(UPoseableMeshComponent* leftHand, UPoseableMeshComponent* rightHand, bool isLeftHand, bool isRightHand)
{
	FVector bonePos;

	if (isLeftHand == true) {
		bonePos = leftHand->GetBoneLocationByName("l_index_finger_tip_marker", EBoneSpaces::WorldSpace);
	}

	if (isRightHand == true) {
		bonePos = rightHand->GetBoneLocationByName("r_index_finger_tip_marker", EBoneSpaces::WorldSpace);
	}

	return bonePos;
}

