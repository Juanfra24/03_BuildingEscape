// Copyright Juan Ternicien 2018

#include "OpenDoor.h"

#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "Components/PrimitiveComponent.h"

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
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressur Plate component"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate()> TriggerMass)
	{
		OnOpen.Broadcast();
	}

	else {
		OnClose.Broadcast();
	}
}
float UOpenDoor::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;

	TArray <AActor*> ActoresSobre;

	if (!PressurePlate){return 0.f;	}
	PressurePlate->GetOverlappingActors(OUT ActoresSobre);

	///Iterar sobre ellos

	for (const auto* Actor : ActoresSobre)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}


