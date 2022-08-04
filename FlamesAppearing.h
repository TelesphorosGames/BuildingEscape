// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "FlamesAppearing.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE427_API UFlamesAppearing : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlamesAppearing();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindAudioComponent();

		private:

		UPROPERTY(EditAnywhere)
	ATriggerVolume* LightsPressurePlate = nullptr;
 
	UPROPERTY(EditAnywhere)
	ATriggerVolume* LightsPressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatTurnsOnTheLights = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatTurnsOnTheLightsTwo = nullptr;

	bool bRanThis = false;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

};
