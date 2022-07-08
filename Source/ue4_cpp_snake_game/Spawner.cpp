// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Food.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnFood()
{
	FVector NewLocation(FMath::FRandRange(-400, 400), FMath::FRandRange(-400, 400), 0);
	FTransform NewTransform = FTransform(NewLocation);
	GetWorld()->SpawnActor<AFood>(FoodClass, NewTransform);
}