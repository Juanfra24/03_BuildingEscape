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

	FindPhysicsComponents();
	SetupInputComponent();
}

void UGrabber::FindPhysicsComponents()
{
	PhysucsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysucsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missin physics handle component"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);

		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input handle component"), *GetOwner()->GetName())
	}

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///Le asigna valores a los parametros posicion y rotacion settter/ getter
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Posicion, OUT Rotacion);
	///Crea variable line trace end
	FVector LineTraceEnd = Posicion + Rotacion.Vector() * Reach;

	/// Setup query parameters
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());


	FHitResult Hit;

	///Tal como el getter/setter de la posicion, este devuelve un fhitreult
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		Posicion,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParam
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *ActorHit->GetName())
	}


	return FHitResult();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	GetFirstPhysicsBodyInReach();
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}



