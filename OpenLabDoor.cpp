
#include "OpenLabDoor.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenLabDoor::UOpenLabDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


	
void UOpenLabDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
		{
			UE_LOG(LogTemp, Error, TEXT(" %s MISSING AUDIO COMPONENT"), *GetOwner()->GetName());
			return;
		}
}


// Called when the game starts
void UOpenLabDoor::BeginPlay()
{
	Super::BeginPlay();

    if (!ActorThatOpensTheLab)
	{
		UE_LOG(LogTemp,Warning, TEXT("NO ACTOR ASSIGNED TO OPEN LAB DOOR"));
		return;
	}
	
	ClosedDoorSpot = GetOwner()->GetActorLocation();
	CurrentZPosition = ClosedDoorSpot;
	FindAudioComponent();

}


// Called every frame
void UOpenLabDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentWorldTime=GetWorld()->GetTimeSeconds();

	if(
		LabPressurePlate && LabPressurePlate->IsOverlappingActor(ActorThatOpensTheLab)
	||	LabPressurePlate2 && LabPressurePlate2->IsOverlappingActor(ActorThatOpensTheLab2)
	)
	{
		if (!ActorThatOpensTheLab || !ActorThatOpensTheLab2)
	{
		UE_LOG(LogTemp,Warning, TEXT("NO ACTOR ASSIGNED TO OPEN DOOR"));
		return;
	}
	if(!LabPressurePlate || ! LabPressurePlate2)
	{
	UE_LOG(LogTemp,Warning, TEXT("LAB PRESSURE PLATE NOT INITIALIZED ON %s"), *GetOwner()->GetName());
	return;
	}
	OpenLabDoor(DeltaTime);
	DoorLastOpened=GetWorld()->GetTimeSeconds();
	// ...
	}
	else
	{
		if (CurrentWorldTime >= DoorLastOpened + DoorCloseDelay)
		{
		CloseLabDoor(DeltaTime);
		}
	}
}


void UOpenLabDoor::OpenLabDoor(float DeltaTime)
{
	CurrentZPosition = FMath::VInterpTo(CurrentZPosition, OpenDoorZ, DeltaTime, .1);
	FVector DoorLocation = GetOwner()->GetActorLocation();
	DoorLocation = CurrentZPosition;
	GetOwner()->SetActorLocation(CurrentZPosition);	
	if(!AudioComponent){return;}
	if (!OpenLabDoorSound)
	{
	AudioComponent->Play();
	OpenLabDoorSound=true;
	}
}

void UOpenLabDoor::CloseLabDoor(float DeltaTime)
{
	CurrentZPosition = FMath::VInterpTo(CurrentZPosition, ClosedDoorSpot, DeltaTime, .1);
	FVector DoorLocation = GetOwner()->GetActorLocation();
	DoorLocation = CurrentZPosition;
	GetOwner()->SetActorLocation(CurrentZPosition);	
	if(!AudioComponent){return;}
	if (OpenLabDoorSound)
	{
	AudioComponent->Play();
	OpenLabDoorSound=false;
	}
}

