// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;
class ASpawner;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class UE4_CPP_SNAKE_GAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
		float ElementSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Points = -18;

	UPROPERTY(EditDefaultsOnly)
		int32 DefaultPoints = 6;

	UPROPERTY()
		TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
		EMovementDirection LastMoveDirection;

	UPROPERTY(BlueprintReadWrite)
		ASpawner* SpawnerActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddSnakeElement(int ElementsNum = 1);
	void Move();
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);
	void KillSnake();
	void SpawnNewFood();
};
