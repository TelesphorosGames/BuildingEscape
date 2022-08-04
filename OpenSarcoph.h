// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenSarcoph.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE427_API UOpenSarcoph : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenSarcoph();



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void FindAudioComponent();
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		 
private:

	FVector ClosedSarcoph;
	FVector OpenedSarcoph;


	// = {-383,350,108};

	
	FVector CurrentSarcoph;

	void OpenSarcoph(float DeltaTime);
	void CloseSarcoph(float DeltaTime);
	void NullChecker();
	bool bNullChecked = false;

	bool OpenSarcophSound = false;

	UPROPERTY(EditInstanceOnly)
	ATriggerVolume* SarcophPressurePlate = nullptr;

	UPROPERTY(EditInstanceOnly)
	ATriggerVolume* SarcophPressurePlate2 = nullptr;

	UPROPERTY(EditInstanceOnly)
	AActor* ActorThatOpensTheSarcoph = nullptr;

	UPROPERTY(EditInstanceOnly)
	AActor* ActorThatOpensTheSarcoph2 = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

};
