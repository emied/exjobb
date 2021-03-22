// Fill out your copyright notice in the Description page of Project Settings.
#include "GrabbingGesture.h"

bool UGrabbingGesture::RecordGesture(UPoseableMeshComponent* hand, FString Directory, FString GestureName)
{
	Directory += "\\";
	Directory += GestureName;
	Directory += ".txt";

	FString Output = "";
	int x = 1;

	//Write bone location vector coordinates to file.
	for (int i = 0; i < hand->GetNumBones(); ++i) {
		FName boneName = hand->GetBoneName(i);
		FVector bonePos = hand->GetBoneLocationByName(boneName, EBoneSpaces::ComponentSpace);
		Output += (FString::SanitizeFloat(bonePos.X) + " " + FString::SanitizeFloat(bonePos.Y) + " " + FString::SanitizeFloat(bonePos.Z));
		Output += LINE_TERMINATOR;
	}
	return FFileHelper::SaveStringToFile(Output, *Directory);
}

TArray <FVector> UGrabbingGesture::ReadGestures(TArray<FString> Directory)
{
	TArray<FVector> HandGesture;
	int counter = 0;

	//Read through the .txt file with all gestures 
	for (auto& i : Directory) {

		std::ifstream pathToTxt;

		if (pathToTxt) {

			std::string pathToGesture = TCHAR_TO_UTF8(*Directory[counter]);
			pathToTxt.open(pathToGesture);

			float x, y, z;
			while (pathToTxt >> x >> y >> z) {
				FVector tmp;
				tmp.X = x; tmp.Y = y; tmp.Z = z;
				HandGesture.Add(tmp);
			}

		}
		else GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Red, "READING from file not NOT WORKING");

		++counter;
	}
	return HandGesture;
}

FString UGrabbingGesture::DoesGestureExist(UPoseableMeshComponent* hand, TArray<FVector> WhatGesture)
{
	bool gestureExist = true;
	FString result = "not initialized or not recognized";
	int i = 0;
	int j = 0;
	int const NOBones = hand->GetNumBones();//new gesture every after NumBones is through
	int const NOGestures = WhatGesture.Num() / NOBones; //Total n.o gestures

	//Read through all the bones in the array to find the right gesture.
	for (auto& x : WhatGesture) {

		FName boneName = hand->GetBoneName(i);
		FVector bonePos = hand->GetBoneLocationByName(boneName, EBoneSpaces::ComponentSpace);
		FVector differenceVector = (bonePos - x);
		float absValofDiffVector = FMath::Sqrt((differenceVector.X * differenceVector.X + differenceVector.Y * differenceVector.Y + differenceVector.Z * differenceVector.Z));
		//Threshold value for gestures
		if (absValofDiffVector > 4.0f) { gestureExist = false; }
		i = ((i + 1) % (NOBones)); //Restart count every 78th bone

		if (i == (NOBones - 1)) {
			if (gestureExist == true) {
				if (j == 0) { return "Point"; }
				if (j == 1) { return "Shoot"; }
				if (j == 2) { return "PalmOpen"; }
				if (j == 3) { return "PalmClosed"; }
				if (j == 4) { return "Rock On"; }
			}
		}

		if (i == 0) {
			j = ((j + 1) % (NOGestures));
			gestureExist = true;
		}
	}

	return result;
}

FString UGrabbingGesture::DoActionOrNot(FString Gesture, bool& IsPoint, bool& IsPalmOpen)
{

	FString result = Gesture;

	if (IsPoint == true && Gesture == "Shoot") {
		IsPoint = false;
		return "Teleport";
	}

	if (IsPalmOpen == true && Gesture == "PalmClosed") {
		return ("Grab");
	}

	if (Gesture == "Point") { IsPoint = true; }
	else { IsPoint = false; }

	if (Gesture == "PalmOpen") { IsPalmOpen = true; }
	else { IsPalmOpen = false; }

	return result;
}
