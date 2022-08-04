// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"

#include "FloatingKeyEffect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE427_API UFloatingKeyEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingKeyEffect();



	void FindAudioComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:

UPROPERTY(EditAnywhere)
AActor* ActorThatFloats = nullptr;
		
UPROPERTY(EditAnywhere)
ATriggerVolume* LabPressurePlate = nullptr;

UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

void SetPhysicsTrue();
FVector PedestalCenter;

	bool bIsAtCenter = false;

		void FloatingKeyEffectX(float DeltaTime);
	



	void CenterItNow();

};
