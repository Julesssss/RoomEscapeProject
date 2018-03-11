#pragma once

#include "Grabber.h"
#include "Engine/Engine.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsComponent();
	FindInputComponent();
}

void UGrabber::FindPhysicsComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Object %s does not have PhysicsHandle!"), *GetOwner()->GetName());
	}
}

void UGrabber::FindInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		// Bind inputs
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Object %s does not have InputComponent!"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab"));

	// If hit PhysicsBody, attatch Physics handle
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = hitResult.GetComponent();
	auto ActorHit = hitResult.GetActor();

	if (ActorHit) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ActorHit->GetActorLocation(),
			true // allow rotation
		);
	}

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Drop"));
	PhysicsHandle->ReleaseComponent();
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If PhysicsHandleAttached, 
	if (PhysicsHandle->GrabbedComponent) {
		// Move object we are 'holding'
		PhysicsHandle->SetTargetLocation(GetLineReachEnd());
	}

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {

	

	//DrawDebugLine(
	//	GetWorld(), playerViewPointLocation,
	//	lineTraceEnd, FColor(200, 10, 30), false, 0.f, 0.f, 10.f
	//);

	/// Line trace (Ray casting) to reach out
	FHitResult lineTraceHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT lineTraceHit,
		GetLineReachStart(),
		GetLineReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// get Actor that was Hit
	AActor* actorHit = lineTraceHit.GetActor();

	/*if (actorHit) {
	UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorHit->GetName()))
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(
	TEXT("Line trace hit: %s"), *(actorHit->GetName())));
	}*/

	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), (*actorHit->GetName()))
	}

	return lineTraceHit;
}

FVector UGrabber::GetLineReachStart() {
	/// Get player view point
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	return playerViewPointLocation;
}

FVector UGrabber::GetLineReachEnd() {
	/// Get player view point
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	return playerViewPointLocation + (playerViewPointRotation.Vector() * Reach);
}
