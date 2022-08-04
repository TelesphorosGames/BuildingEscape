// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingKeyEffect.h"

// Sets default values for this component's properties
UFloatingKeyEffect::UFloatingKeyEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingKeyEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FindAudioComponent();
}


// Called every frame
void UFloatingKeyEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

if(LabPressurePlate && LabPressurePlate->IsOverlappingActor(ActorThatFloats))
	{
		
		if (!ActorThatFloats)		
		{
		UE_LOG(LogTemp,Warning, TEXT("NO ACTOR ASSIGNED TO Float"));
		return;
		}
		if(!bIsAtCenter)
			{
				CenterItNow();
			}
			else
			{
		FloatingKeyEffectX(DeltaTime);
			}
		
		
		
	}
else
{
	bIsAtCenter = false;

}
	
}

void UFloatingKeyEffect::FloatingKeyEffectX(float DeltaTime)
{

	
	FVector NewLocation = GetOwner()->GetActorLocation();
	FRotator NewRotation = GetOwner()->GetActorRotation();
	float RunningTime = GetWorld()->GetTimeSeconds();
	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	NewRotation.Yaw += DeltaRotation;
	GetOwner()->SetActorLocationAndRotation(NewLocation, NewRotation);
	
	
	
	// GetOwner()->SetActorEnableCollision(false);
	
}

// void UFloatingKeyEffect::SetPhysicsFalse()
// {
// 	for (UActorComponent* Component : GetComponents())
// 	{
// 		if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
// 		{
// 			PrimComp->SetSimulatePhysics(true);
// 		}
// 	}
// }

void UFloatingKeyEffect::CenterItNow()
{
PedestalCenter = LabPressurePlate->GetActorLocation();

GetOwner()->SetActorLocation(PedestalCenter);
GetOwner()->DisableComponentsSimulatePhysics();
bIsAtCenter = true;
// UE_LOG(LogTemp, Error, TEXT(" FUCK"));
// UE_LOG(LogTemp, Error, TEXT("THE string of PedestalCenter.Z is %f"), PedestalCenter.Z);
// float TargetCenter = PedestalCenter.Z + 20;
// UE_LOG(LogTemp, Error, TEXT("And the new target is %f"), TargetCenter);

AudioComponent->Play();

}


void UFloatingKeyEffect::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
		{
			UE_LOG(LogTemp, Error, TEXT(" %s MISSING AUDIO COMPONENT"), *GetOwner()->GetName());
			return;
		}
}

void UFloatingKeyEffect::SetPhysicsTrue()
{
	for (UActorComponent* Component : ActorThatFloats->GetComponents())
{
	if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
	{
		PrimComp->SetSimulatePhysics(true);
	}
}
}
