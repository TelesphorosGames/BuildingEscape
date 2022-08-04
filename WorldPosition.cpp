// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	
	


    // FString Log = TEXT("Hello");
	// FString* PtrLog = &Log;
	// // Log.Len();  .  would be used as the operator for a DIRECT access to those members
	// // PtrLog->Len();  for indirect access via a pointer
	// UE_LOG(LogTemp, Warning, TEXT("HELLO WORLD %s"), **PtrLog); //  the * is the format specifier used to pass in the string and the second * is the pointer operator
	// // UE_LOG(LogTemp, Display, TEXT("THIS IS A MESSAGE"))
	
	

	FString ObjectName = GetOwner()->GetName();
	
	
	
	FVector ObjectPosition = GetOwner()->GetActorLocation();

	FString PositionString = ObjectPosition.ToString();


	UE_LOG(LogTemp, Error, TEXT("The Object's name is %s and is located at %s"), *ObjectName, *PositionString);



}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

