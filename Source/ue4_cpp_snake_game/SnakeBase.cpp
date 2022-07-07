// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.0f;
	LastMoveDirection = EMovementDirection::LEFT;
	MovementSpeed = 10.0f;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElemet(5);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElemet(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform = FTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		int32 ElementIndex = SnakeElements.Add(NewSnakeElem);
		if (ElementIndex == 0)
			NewSnakeElem->SetFirstElementType();
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	float SpeedMovement = ElementSize;
	if (LastMoveDirection == EMovementDirection::UP)
	{
		MovementVector - FVector(SpeedMovement, 0, 0);
	}
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP : 
		MovementVector.X += SpeedMovement;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= SpeedMovement;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += SpeedMovement;
		break;
	case EMovementDirection::RIGHT :
		MovementVector.Y -= SpeedMovement;
		break;
	}
	//AddActorWorldOffset(MovementVector);
	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}