
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
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

	// find Actor
	AActor * owner = GetOwner();
	FQuat rot = owner->GetTransform().GetRotation();

	UE_LOG(LogTemp, Warning, TEXT("Door Z rotation is %s"), *rot.ToString());

	// create rotation
	FRotator NewRotation = FRotator(0.0f, 70.f ,0.0f);

	// set door rotation
	owner->SetActorRotation(NewRotation);

	UE_LOG(LogTemp, Warning, TEXT("New door rotation is %s"), *rot.ToString());

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

