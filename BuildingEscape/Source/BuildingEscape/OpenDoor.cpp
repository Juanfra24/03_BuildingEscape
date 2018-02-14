// Copyright Juan Ternicien 2018

#include "OpenDoor.h"

#include "Gameframework/Actor.h"
#include "Engine/World.h"


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
	
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{	

	Owner->SetActorRotation(FRotator(0.0f,OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	
	Owner->SetActorRotation(FRotator(0.0f,CloseAngle, 0.f));
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds()-LastDoorOpenTime >= DoorCloseDelay )
	{
		CloseDoor();
	}
}

