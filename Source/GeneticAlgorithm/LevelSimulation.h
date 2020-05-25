// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Population.h"
#include "Block.h"
#include "LevelSimulation.generated.h"

UCLASS(BlueprintType)
class GENETICALGORITHM_API ALevelSimulation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSimulation();

	//UPROPERTY(EditAnywhere)
	//TArray<URoom*> Level;

	Population P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PopulationSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxGenerations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MutationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastGenAverageFitness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastGenMaxFitness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BestDNA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BestFitness;

	TArray<ABlock*> LevelBlocks;
	ABlock* MinotaurBlock;
	ABlock* TheseusBlock;

	UFUNCTION(BlueprintCallable, Category = "Level Sim Functions")
	void SetGenerations(int gen);
	UFUNCTION(BlueprintCallable, Category = "Level Sim Functions")
	void SetNumActions(int num);
	UFUNCTION(BlueprintCallable, Category = "Level Sim Functions")
	void SetPopulationSize(int size);
	UFUNCTION(BlueprintCallable, Category = "Level Sim Functions")
	void SetMutationRate(float rate);

	UFUNCTION(BlueprintCallable, Category = "Level Sim Functions")
	void MoveTheseus(FVector2D Direction);

	UFUNCTION(BlueprintCallable, Category = "Level Sim Functions")
	void ResetTheseus();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Locked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool Completed;
	int CurrentAction;


	void Initialize();

	Agent Player;
	bool Minotaur1stMove;
	bool Minotaur2ndMove;
	float Cooldown;
};
