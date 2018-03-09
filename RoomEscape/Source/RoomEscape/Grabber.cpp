

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello Grabber!"));

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		playerViewPointLocation,
		playerViewPointRotation
	);
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"), 
		*playerViewPointLocation.ToString(), 
		*playerViewPointRotation.ToString()
	)

	FVector lineTraceEnd = playerViewPointLocation + (playerViewPointRotation.Vector() * Reach);

	// Draw trace
	DrawDebugLine(
		GetWorld(), playerViewPointLocation,
		lineTraceEnd, FColor(200, 10, 30), false, 0.f, 0.f, 10.f
	);


	// See where it went
}

