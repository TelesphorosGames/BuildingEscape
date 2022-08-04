#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/AudioComponent.h"
#include "OpenDoorTry2.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

UOpenDoorTry2::UOpenDoorTry2()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoorTry2::BeginPlay()
{
	Super::BeginPlay();
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
 
	CurrentYaw = InitialYaw;
	UE_LOG(LogTemp, Warning, TEXT("Initial Yaw for %s is %f"), *GetOwner()->GetName(), InitialYaw);
	TargetYaw = InitialYaw + TargetYaw;
	UE_LOG(LogTemp, Warning, TEXT("TARGET YAW for %s IS %f"),*GetOwner()->GetName(), TargetYaw);

	if(!PressurePlate)
	{
	UE_LOG(LogTemp,Warning, TEXT("PRESSURE PLATE NOT INITIALIZED ON %s"), *GetOwner()->GetName());
	}


	ActorThatOpensTheDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoorTry2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentWorldTime=GetWorld()->GetTimeSeconds();

	if (!ActorThatOpensTheDoor)
	{
		UE_LOG(LogTemp,Warning, TEXT("NO ACTOR ASSIGNED TO OPEN DOOR"));
		return;
	}
	
	if(PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensTheDoor))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened=GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (CurrentWorldTime >= DoorLastOpened + DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	// if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensTheDoor) || PressurePlate2 &&PressurePlate2->IsOverlappingActor(ActorThatOpensTheDoor))
	// {
	// 	OpenDoor(DeltaTime);
	// 	DoorLastOpened=GetWorld()->GetTimeSeconds();
	// }
	// else
	// {
	// 	if (CurrentWorldTime >= DoorLastOpened + DoorCloseDelay)
	// 	{
	// 		CloseDoor(DeltaTime);
	// 	}
	// }
	FindAudioComponent();

}
	
void UOpenDoorTry2::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
		{
			UE_LOG(LogTemp, Error, TEXT(" %s MISSING AUDIO COMPONENT"), *GetOwner()->GetName());
			return;
		}
}


void UOpenDoorTry2::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw= CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);	
	if(!AudioComponent){return;}
	if (!OpenDoorSound)
	{
	AudioComponent->Play();
	OpenDoorSound=true;
	}
}

void UOpenDoorTry2::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 4);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw= CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);	
	if (OpenDoorSound)
	{
		OpenDoorSound = false;
	}
}

float UOpenDoorTry2::TotalMassOfActors() const
{
	float TotalMass =0.f;

	// Find all overlapping Actors
	TArray<AActor*> OverlappingActors;
	if(!PressurePlate)
	{
	UE_LOG(LogTemp,Warning, TEXT("PRESSURE PLATE NOT INITIALIZED ON %s"), *GetOwner()->GetName());
	return TotalMass;}
	PressurePlate->GetOverlappingActors(OverlappingActors);


	// Add up the masses
	for(AActor*Actor : OverlappingActors)
	{
		TotalMass +=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;


}
	
