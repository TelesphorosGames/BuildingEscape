// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenSarcoph.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"



// Sets default values for this component's properties
UOpenSarcoph::UOpenSarcoph()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOpenSarcoph::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
		{
			UE_LOG(LogTemp, Error, TEXT(" %s MISSING AUDIO COMPONENT"), *GetOwner()->GetName());
			return;
		}
}



// Called when the game starts
void UOpenSarcoph::BeginPlay()
{
	Super::BeginPlay();	
	ClosedSarcoph = GetOwner()->GetActorLocation();
	CurrentSarcoph = ClosedSarcoph;
	OpenedSarcoph = {ClosedSarcoph.X, ClosedSarcoph.Y, ClosedSarcoph.Z+85};
	NullChecker();
	FindAudioComponent();
	// ...

	
	
}
  

// Called every frame
void UOpenSarcoph::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

if (bNullChecked)
{
	if(!SarcophPressurePlate2)
	{
		if(SarcophPressurePlate->IsOverlappingActor(ActorThatOpensTheSarcoph)) 
			{
				OpenSarcoph(DeltaTime);
			}
	}
	if(	SarcophPressurePlate->IsOverlappingActor(ActorThatOpensTheSarcoph) && 
		SarcophPressurePlate2->IsOverlappingActor(ActorThatOpensTheSarcoph2))
		{
			OpenSarcoph(DeltaTime);
		}
	else
	{
	CloseSarcoph(DeltaTime);
	}
}

}
void UOpenSarcoph::OpenSarcoph(float DeltaTime)
{
	CurrentSarcoph = FMath::VInterpTo(CurrentSarcoph, OpenedSarcoph, DeltaTime, 1);
	GetOwner()->SetActorLocation(CurrentSarcoph);	
	
	if(!AudioComponent){return;}
	if (!OpenSarcophSound)
	{
	AudioComponent->Play();
	OpenSarcophSound=true;
	}
}

void UOpenSarcoph::CloseSarcoph(float DeltaTime)
{
	CurrentSarcoph = FMath::VInterpTo(CurrentSarcoph, ClosedSarcoph, DeltaTime, 1);
	GetOwner()->SetActorLocation(CurrentSarcoph);	
	if(!AudioComponent){return;}
	if (OpenSarcophSound)
	{
	AudioComponent->Play();
	OpenSarcophSound=false;
	}
}

void UOpenSarcoph::NullChecker()
{
	if (!ActorThatOpensTheSarcoph)
	{
		{
			UE_LOG(LogTemp,Warning, TEXT("NO ACTOR 1 ASSIGNED TO OPEN Sarcophogus on %s"), *GetOwner()->GetName());
			return;
		}
	} 
	
	if (!ActorThatOpensTheSarcoph2)
			{
				UE_LOG(LogTemp,Warning, TEXT("NO ACTOR 2 ASSIGNED TO OPEN Sarcophogus on %s"), *GetOwner()->GetName());
			}
			if(!SarcophPressurePlate)
			{
				UE_LOG(LogTemp,Warning, TEXT("Sarcophogus PRESSURE PLATE NOT INITIALIZED ON %s"), *GetOwner()->GetName());
				return;
			}
			if (!SarcophPressurePlate2)
			{
			UE_LOG(LogTemp,Warning, TEXT("Sarcophogus PRESSURE PLATE NOT INITIALIZED ON %s"), *GetOwner()->GetName());
			}
	bNullChecked = true;
}