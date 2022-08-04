// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AudioComponent.h"

#include "FlamesAppearing.h"

// Sets default values for this component's properties
UFlamesAppearing::UFlamesAppearing()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFlamesAppearing::BeginPlay()
{
	Super::BeginPlay();


FindAudioComponent();


	// ...
	
 }


// Called every frame
void UFlamesAppearing::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bRanThis)
	{	if(LightsPressurePlate && LightsPressurePlate->IsOverlappingActor(ActorThatTurnsOnTheLights) && LightsPressurePlate2 && LightsPressurePlate2->IsOverlappingActor(ActorThatTurnsOnTheLightsTwo))
			{
			GetOwner()->SetActorHiddenInGame(false);
			bRanThis = true;
				if(!AudioComponent)
					{return;}
				else{
					AudioComponent->Play();
					}
			}	
	}
}
void UFlamesAppearing::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
		{
			UE_LOG(LogTemp, Error, TEXT(" %s MISSING AUDIO COMPONENT"), *GetOwner()->GetName());
			return;
		}
}

