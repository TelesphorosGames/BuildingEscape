// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"



#include "THEACTORSGRABBER.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE427_API UTHEACTORSGRABBER : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTHEACTORSGRABBER();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:


	float HeldReachFloat = 150.f;

	float Reach = 200.f;
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;
	class UInputComponent* InputComponent = nullptr;
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	// void TakeKeyMechanism();

	// Return the first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	// void SetPhysicsTrue();
	// Return LineTraceEnd

	FVector GetReach() const;
	FVector GetHeldReach() const;

	FVector PlayerViewPointLocationFunction() const;
	// FVector AdjustReach() const;
};
