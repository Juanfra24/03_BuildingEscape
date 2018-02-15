// Copyright Juan Ternicien 2018

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "DrawDebugHelpers.h"

#define OUT


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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Posicion,OUT Rotacion);

	FVector LineTraceEnd = Posicion + Rotacion.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		Posicion,
		LineTraceEnd,
		FColor(255,0,0),
		false,
		0.f,
		0.f,
		15.f
	);


	UE_LOG(LogTemp, Warning, TEXT("Position: %s /// Rotation: %s"), *Posicion.ToString(), *Rotacion.ToString());
}

