
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include <string>

#define OUT

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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll trigger volume every frame
	if (GetTotalMassOfActorsOnPlate() > TRIGGER_MASS) {
		OnOpen.Broadcast();
	} else {
		OnClose.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("onClose?"))
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float totalMass = 0.f;

	// Find overlapping Actors
	TArray<AActor*> OverlappingActors;

	if (PressurePlate == nullptr) { return 0.f; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	for (const auto* Actor: OverlappingActors) {
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Total mass: %f"), totalMass)

	return totalMass;
}

