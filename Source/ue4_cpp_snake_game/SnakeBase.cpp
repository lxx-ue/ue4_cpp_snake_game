// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "Spawner.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.0f;
	LastMoveDirection = EMovementDirection::LEFT;
	MovementSpeed = 0.5f;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(3);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform = FTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		int32 ElementIndex = SnakeElements.Add(NewSnakeElem);
		Points += DefaultPoints;
		if (ElementIndex == 0)
			NewSnakeElem->SetFirstElementType();
		else 
			NewSnakeElem->MeshComponent->SetVisibility(false);
		MovementSpeed = FMath::Clamp(MovementSpeed - 0.01, 0.1, 0.5);
		SetActorTickInterval(MovementSpeed);
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	if (LastMoveDirection == EMovementDirection::UP)
	{
		MovementVector - FVector(ElementSize, 0, 0);
	}
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP : 
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT :
		MovementVector.Y -= ElementSize;
		break;
	}
	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
		CurrentElement->MeshComponent->SetVisibility(true);
	}
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

void ASnakeBase::KillSnake()
{
	for (auto elem : SnakeElements)
		elem->Destroy();
	Destroy();
}

void ASnakeBase::SpawnNewFood()
{
	SpawnerActor->SpawnFood();
}