// Fill out your copyright notice in the Description page of Project Settings.


#include "Moving_Platform.h"

// Sets default values
AMoving_Platform::AMoving_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoving_Platform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Begin Play :%s"),*Name);

}

// Called every frame
void AMoving_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMoving_Platform::MovePlatform(float DeltaTime)
{
	if(ShouldPlatformReturn())
	{
	    FVector MoveDirection = PlatformVelocity.GetSafeNormal();
	    StartLocation = StartLocation + MoveDirection * MoveDirection;
	    SetActorLocation(StartLocation);
	    PlatformVelocity =-PlatformVelocity;
	}
	else
	{
	 FVector CurrentLocation =GetActorLocation();
	 CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
     SetActorLocation(CurrentLocation);  
	}	
}

void AMoving_Platform::RotatePlatform(float DeltaTime)
{
  AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMoving_Platform::ShouldPlatformReturn() const
 {
    return GetDistanceMoved() > MoveDistance;
 }

 float AMoving_Platform::GetDistanceMoved() const
 {
	return FVector :: Dist(StartLocation, GetActorLocation());
 }