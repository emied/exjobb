// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunctionLibrary.h"



FQuat UTestFunctionLibrary::EulerToQuatConverssion(FRotator eulerRotation)
{
	FQuat q;


	float yaw, pitch, roll;

	//convert degrees to radians since rotator deals in deegrees but we want radians
	yaw = (eulerRotation.Yaw * PI) / 180;
	pitch = (eulerRotation.Pitch * PI) / 180;
	roll = (eulerRotation.Roll * PI) / 180;

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);


	q.W = cr * cp * cy + sr * sp * sy;
	q.X = sr * cp * cy - cr * sp * sy;
	q.Y = cr * sp * cy + sr * cp * sy;
	q.Z = cr * cp * sy - sr * sp * cy;

	return q;
}

void UTestFunctionLibrary::AddActorLocalRotationQuat(AActor* Actor, const FQuat& deltaRotation)
{

	if (Actor) {
		Actor->AddActorLocalRotation(deltaRotation);
	}
}

void UTestFunctionLibrary::ApplyQuaternionRotation(AActor* Actor,  float inputAxis)
{

	FRotator rotator = FRotator(inputAxis, 0.f, 0.f);
	//FRotator currentRotator = FRotator(0.f, 0.f, 0.f);
	//Actor->GetActorRotation();
	
	
	FQuat currentRotation = Actor->GetActorQuat();
	
	FQuat DesiredRotationLeft = FQuat(FRotator(inputAxis, 0.f, 0.f));
	

	FQuat newQuat = FQuat::Slerp(currentRotation, DesiredRotationLeft, 0.5f);
	//FQuat newQuatInv = FQuat::Slerp(currentRotation, DesiredRotationRight, 0.5f);
	
	Actor->AddActorLocalRotation(newQuat);
	//if (inputAxis < 0) {
	//	Actor->SetActorRotation(newQuat);
	//}

	
}

FRotator UTestFunctionLibrary::ApplyQuaternionRotationComponent(USceneComponent* sceneComponent, float inputX, float inputY)
{
	float rotator = 0;

	bool isRotating = false;
	FQuat currentRot = FQuat(sceneComponent->USceneComponent::GetComponentRotation());

	FQuat DesiredRotationLeft = FQuat(FRotator(0.f, -inputX*0.2, -inputY*0.2));


	FQuat newQuat = FQuat::Slerp(currentRot, DesiredRotationLeft, 0.5f);


	if (inputX != 0 || inputY != 0) {
		//sceneComponent->SetWorldRotation(newQuat);
		//sceneComponent->SetRelativeRotation(newQuat);
		sceneComponent->AddLocalRotation(DesiredRotationLeft);
	}
	
	
	return newQuat.Rotator();
	
}

void UTestFunctionLibrary::ApplyQuaternionRotationForGrabbedObjects(USceneComponent* hitComponent, USceneComponent* motionController, FRotator initialRot)
{
	FRotator motionControllerRotation = motionController->GetComponentRotation();
	
	FQuat initialQuat = FQuat(initialRot);
	
	FQuat motionControllerQuatRot = FQuat(motionControllerRotation);

	FQuat newQuat = FQuat(motionControllerQuatRot.X*1.5f, motionControllerQuatRot.Y*1.5f, motionControllerQuatRot.Z*1.5f, motionControllerQuatRot.W);
	hitComponent->SetWorldRotation(newQuat);
}


void UTestFunctionLibrary::ApplyTeleportationRotationQuat(UCameraComponent* camera, FRotator arrowRotation, FRotator currentRotation)
{

	FQuat arrowQuat = FQuat(arrowRotation);
	FQuat currentQuat = FQuat(currentRotation);


	FQuat desiredQuat = arrowQuat*currentQuat;


	camera->SetWorldRotation(desiredQuat);

	
}

void UTestFunctionLibrary::DestroyActorOnButtonPress(AActor* Actor)
{
	if (Actor) {
		Actor->K2_DestroyActor();
	}
}

bool UTestFunctionLibrary::IsSelectable(AActor* actor)
{
	if (actor) {
		return true;
	}
	else
	{
		return false;
	}
}

void UTestFunctionLibrary::SetHighlight(UPrimitiveComponent* hitComponent)
{

	if (hitComponent){
		hitComponent->SetRenderCustomDepth(true);
		hitComponent->SetCustomDepthStencilValue(2.f);
	}
	
	
	
}

void UTestFunctionLibrary::DeleteHighlight(UPrimitiveComponent* hitComponent)
{
	if (hitComponent) {
		hitComponent->SetRenderCustomDepth(false);
		hitComponent->SetCustomDepthStencilValue(0.f);
	}
}

void UTestFunctionLibrary::RotateSelectionUMGWidget(USceneComponent* camera, USceneComponent* widget)
{

	FVector cameraPos = camera->GetComponentLocation();
	FVector widgetPos = widget->GetComponentLocation();

	FRotator firstRotation = UKismetMathLibrary::FindLookAtRotation( widgetPos, cameraPos);

	float yaw, pitch, roll;

	yaw = firstRotation.Yaw - 90.f;

	roll = 90.f;
	pitch = -90.f;

	FRotator targetRotation = FRotator(pitch, roll, yaw);
	//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %f - %f - %f"), targetRotation.Pitch, targetRotation.Yaw, targetRotation.Roll));

	widget->SetWorldRotation(targetRotation);
}

void UTestFunctionLibrary::SetSimulatePhysicsToValid(UPrimitiveComponent* comp)
{
	if (comp) {
		comp->SetSimulatePhysics(false);
	}
}

float UTestFunctionLibrary::SetInitialDistance(USceneComponent* LeftController, USceneComponent* RightController)
{
	FVector leftPos = LeftController->GetComponentLocation();
	FVector rightPos = RightController->GetComponentLocation();

	FVector distanceVec = leftPos - rightPos;

	float initialDistance = distanceVec.Size();
	
	return initialDistance;
	
}

FRotator UTestFunctionLibrary::GetObjectPlacementRotationFromNormal(FVector normal)
{

	float x = normal.X;
	float y = normal.Y;
	float z = normal.Z;
	FRotator outRotation = FRotator(); //initialize

	if (y < -0.5) {
		outRotation = FRotator(-90.f, -90.f, 0.f);
	}
	else if (y > 0.5) {
		outRotation = FRotator(90.f, -90.f, 0.f);
	}

	else if (x < -0.5) {
		outRotation = FRotator(-90.f, 90.f, 90.f);
		
	}
	else if (x > 0.5) {
		outRotation = FRotator(90.f, 180.f, 0.f);
	}
	else if (z > 0.5) {
		outRotation = FRotator(0.f, 180.f, 0.f);
	}

	return outRotation;
}

bool UTestFunctionLibrary::isDetachable(UPrimitiveComponent* comp)
{
	if (comp) {
		return true;
	}
	else {
		return false;
	}
}

UPrimitiveComponent* UTestFunctionLibrary::isDetachableComponent(UPrimitiveComponent* comp)
{
	if (comp) {
		return comp;
	}
	else {
		return nullptr;
	}
	
}








