// Fill out your copyright notice in the Description page of Project Settings.


#include "THEACTORSGRABBER.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"


#define OUT

// Sets default values for this component's properties
UTHEACTORSGRABBER::UTHEACTORSGRABBER()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTHEACTORSGRABBER::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("GRABBER ONLINE"));
	FindPhysicsHandle();
	SetupInputComponent();
}

void UTHEACTORSGRABBER::SetupInputComponent()  // Set up the Input Component for Binding Key Presses
{
InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent)
		{
			InputComponent->BindAction("Grab",IE_Pressed, this, &UTHEACTORSGRABBER::Grab);
			InputComponent->BindAction("Release",IE_Pressed, this, &UTHEACTORSGRABBER::Release);
		}
}

void UTHEACTORSGRABBER::FindPhysicsHandle() // Check for Physics Handle Component:
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

		if (!PhysicsHandle)
		{
			UE_LOG(LogTemp, Error, TEXT("NO PHYSICS HANDLE WAS FOUND ON %s"), *GetOwner()->GetName());
		}
}

void UTHEACTORSGRABBER::Grab()
{
	// Only Ray cast when key is pressed

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor*ActorHit = HitResult.GetActor();

	// Try to reach any actors with a "physics body" collision channel set.
	// If we hit something, then attach the physics handle:

	if(ActorHit)
		{
			if(!PhysicsHandle)	{return;}
		// TakeKeyMechanism();
		PhysicsHandle->GrabComponentAtLocation(
		ComponentToGrab,
		NAME_None,
		GetReach()
		);
		}
	
}

FVector UTHEACTORSGRABBER::GetReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	( 
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UTHEACTORSGRABBER::GetHeldReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	( 
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * HeldReachFloat;
}

void UTHEACTORSGRABBER::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Release PRESSED"));
	//  Remove (release) the physics handle:
	if (!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UTHEACTORSGRABBER::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached, move the object we are holding

	// DrawDebugLine
	// (
	// 	GetWorld(),
	// 	PlayerViewPointLocationFunction(),
	// 	GetReach(),
	// 	FColor(255, 255, 255),
	// 	false,
	// 	0.f,
	// 	0,
	// 	5.f
	// );
	
	if(PhysicsHandle->GrabbedComponent)
	{
		if (!PhysicsHandle) {return;}
		PhysicsHandle->SetTargetLocation(GetHeldReach());
	}
}

FHitResult UTHEACTORSGRABBER::GetFirstPhysicsBodyInReach() const
{
	

	// RAY CAST! ( REACH ) 

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocationFunction(),
		GetReach(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// What was hit by reach?
	AActor* ActorHit =	Hit.GetActor();
	if (ActorHit)
	{
	UE_LOG(LogTemp, Warning, TEXT("%s WAS HIT BY LINE TRACE"), *ActorHit->GetName());
				for (UActorComponent* Component : ActorHit->GetComponents())
					{
						if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
							{
								PrimComp->SetSimulatePhysics(true);
							}
					}
	};
	return Hit;
}

// void UTHEACTORSGRABBER::TakeKeyMechanism()
// {
// 	for (UActorComponent* Component : ->GetComponents())
// {
// 	if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
// 	{
// 		PrimComp->SetSimulatePhysics(true);
// 	}
// }
// }





FVector UTHEACTORSGRABBER::PlayerViewPointLocationFunction() const
{
// Get the Player's Viewpoint:
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( 
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;

	// UE_LOG(LogTemp, Warning, TEXT
	// 		(
	// 			"ViewpointLocation is %s, rotation is %s"
	// 		), 
	// 			*PlayerViewPointLocation.ToString(), 
	// 			*PlayerViewPointRotation.ToString()
	// );

	//^^ Log, to test
}

// FVector UTHEACTORSGRABBER::AdjustReach() const
// {
//     FVector PlayerViewPointLocation;
// 	FRotator PlayerViewPointRotation;

// 	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
// 	( 
// 		OUT PlayerViewPointLocation, 
// 		OUT PlayerViewPointRotation
// 	);

// 	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * HeldReach;
// }

// void UTHEACTORSGRABBER::SetPhysicsTrue()
// {
// 	for (UActorComponent* Component : ->GetComponents())
// {
// 	if(// what was hit has the floating key effect component?? ))
// 	//then do this and 
// 	if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
// 	{
// 		PrimComp->SetSimulatePhysics(true);
// 	}
// }
// }