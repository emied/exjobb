// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "CppQuestPawn.generated.h"


UCLASS()
class EXJOBB_API ACppQuestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACppQuestPawn();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UCameraComponent* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UMotionControllerComponent* LeftController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UStaticMeshComponent* RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UStaticMeshComponent* LeftHand;


};
