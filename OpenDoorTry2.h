// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoorTry2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE427_API UOpenDoorTry2 : public UActorComponent
{
	GENERATED_BODY()
 
public:	
	// Sets default values for this component's properties
	UOpenDoorTry2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	

	bool OpenDoorSound = false;

 void FindAudioComponent();

private:

	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)	
	float TargetYaw;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensTheDoor = nullptr;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay =2.f;

	float CurrentWorldTime = 0.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
