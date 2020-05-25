// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (TileAsset.Succeeded()) {
		TileMesh->SetStaticMesh(TileAsset.Object);
	}

	//Initializes the materials
	static ConstructorHelpers::FObjectFinder<UMaterial> FloorMaterialR(TEXT("Material'/Game/FloorMaterial.FloorMaterial'"));
	FloorMaterial = FloorMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> TheseusMaterialR(TEXT("Material'/Game/TheseusMaterial.TheseusMaterial'"));
	TheseusMaterial = TheseusMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MinotaurMaterialR(TEXT("Material'/Game/MinotaurMaterial.MinotaurMaterial'"));
	MinotaurMaterial = MinotaurMaterialR.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> GoalMaterialR(TEXT("Material'/Game/GoalMaterial.GoalMaterial'"));
	GoalMaterial = GoalMaterialR.Object;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::SetFloor() {
	TileMesh->SetMaterial(0, FloorMaterial);
}

void ABlock::SetGoal() {
	TileMesh->SetMaterial(0, GoalMaterial);
}

void ABlock::SetWall(FVector2D Position) {
	if (Position == FVector2D(0, 1)) {
		SetActorScale3D(FVector(.2f, 1.2f, 1.0f));
		SetActorLocation(GetActorLocation() + FVector(50.f, 0.0f, 0.f), false);
	} else if (Position == FVector2D(0, -1)) {
		SetActorScale3D(FVector(.2f, 1.2f, 1.0f));
		SetActorLocation(GetActorLocation() + FVector(-50.f, 0.0f, 0.f), false);
	} else if (Position == FVector2D(1, 0)) {
		SetActorScale3D(FVector(1.2f, .2f, 1.0f));
		SetActorLocation(GetActorLocation() + FVector(0.f, 50.0f, 0.f), false);
	} else if (Position == FVector2D(-1, 0)) {
		SetActorScale3D(FVector(1.2f, 0.2f, 1.0f));
		SetActorLocation(GetActorLocation() + FVector(0.f, -50.0f, 0.f), false);
	}
	TileMesh->SetMaterial(0, FloorMaterial);
}


void ABlock::SetTheseus() {
	SetActorScale3D(FVector(0.8f, 0.8f, 0.8f));
	TileMesh->SetMaterial(0, TheseusMaterial);
}

void ABlock::SetMinotaur() {
	SetActorScale3D(FVector(0.8f, 0.8f, 0.8f));
	TileMesh->SetMaterial(0, MinotaurMaterial);
}