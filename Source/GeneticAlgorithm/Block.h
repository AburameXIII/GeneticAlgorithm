// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class GENETICALGORITHM_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TileMesh;

	void SetFloor();
	void SetWall(FVector2D Position);
	void SetTheseus();
	void SetMinotaur();
	void SetGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	class UMaterial* FloorMaterial;
	class UMaterial* TheseusMaterial;
	class UMaterial* MinotaurMaterial;
	class UMaterial* GoalMaterial;

};
