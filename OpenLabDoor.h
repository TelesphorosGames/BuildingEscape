// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenLabDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE427_API UOpenLabDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenLabDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindAudioComponent();
	void OpenLabDoor(float DeltaTime);
	void CloseLabDoor(float DeltaTime);

	bool OpenLabDoorSound = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
 
private:

	FVector ClosedDoorSpot;

	FVector OpenDoorZ = {5038,240,-535};

	FVector CurrentZPosition;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* LabPressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensTheLab = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* LabPressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensTheLab2 = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay =2.f;

	float DoorLastOpened = 0.f;
	
	float CurrentWorldTime =0.f;


	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;




		
};
