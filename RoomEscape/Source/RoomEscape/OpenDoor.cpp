
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include <string>


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// set door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));

}

void UOpenDoor::CloseDoor()
{
	// set door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.f, 0.0f));

	FQuat rot = Owner->GetTransform().GetRotation();
	UE_LOG(LogTemp, Warning, TEXT("New door rotation is %s"), *rot.ToString());
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll trigger volume every frame

	// if ActorThatOpens is in volume, open door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}

	// check if time to close door
	if (GetWorld()->GetTimeSeconds() > (DoorLastOpenTime + DoorCloseDelay)) {
		CloseDoor();
	}

}

