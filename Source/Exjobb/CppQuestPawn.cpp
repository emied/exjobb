// Fill out your copyright notice in the Description page of Project Settings.


#include "CppQuestPawn.h"

// Sets default values
ACppQuestPawn::ACppQuestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	Head = CreateDefaultSubobject<UCameraComponent>(TEXT("Head"));

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));


	Head->SetupAttachment(SceneRoot);
	LeftController->SetupAttachment(Head);
	RightController->SetupAttachment(Head);

}

// Called when the game starts or when spawned
void ACppQuestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppQuestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACppQuestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

