// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSimulation.h"

// Sets default values
ALevelSimulation::ALevelSimulation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	/*
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			FString RoomName = FString::Printf(TEXT("Room %d %d"), i, j);
			URoom* r = CreateDefaultSubobject<URoom>(*RoomName);
			Level.Add(r);
		}
	}
	*/
	//Population = NewObject<UPopulation>();
	
}

// Called when the game starts or when spawned
void ALevelSimulation::BeginPlay()
{
	Super::BeginPlay();
	
	MutationRate = 0.2f;
	CurrentGeneration = 1;
	LastGenAverageFitness = 0.0f;
	LastGenMaxFitness = 0.0f;
	BestDNA = "N/A";
	BestFitness = 0.0f;


	MaxGenerations = 1000;
	CurrentAction = 0;
	PopulationSize = 1000;
	NumActions = 40;
	Cooldown = 0.2f;
	Player.Initialize();

	Level.SetNum(Width * Height);

	/* //LEVEL 44

	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			Level[i + j * Width].ValidActions.Add(Action::Up);
			Level[i + j * Width].ValidActions.Add(Action::Down);
			Level[i + j * Width].ValidActions.Add(Action::Left);
			Level[i + j * Width].ValidActions.Add(Action::Right);
			Level[i + j * Width].ValidActions.Add(Action::Wait);
			Level[i + j * Width].Position = FVector2D(i, j );
			Level[i + j * Width].TileToGoal = Width * Height;

			//RemoveBoundaryActions
			if (i == 0) {
				Level[i + j * Width].ValidActions.Remove(Action::Left);
			}

			if (i == 5) {
				Level[i + j * Width].ValidActions.Remove(Action::Right);
			}

			if (j == 0) {
				Level[i + j * Width].ValidActions.Remove(Action::Down);
			}

			if (j == 5) {
				Level[i + j * Width].ValidActions.Remove(Action::Up);
			}

			//RemoveWalledActions
			if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 1 && j == 4) || (i == 2 && j == 0) || (i == 3 && j == 0) || (i == 3 && j == 1) || (i == 3 && j == 2) || (i == 3 && j == 3) || (i == 3 && j == 4) || (i == 5 && j == 2)) {
				Level[i + j * Width].ValidActions.Remove(Action::Up);
				//Level[i + (j+1) * 6].ValidActions.Remove(Action::Down);
			}

			if ((i == 0 && j == 1) || (i == 0 && j == 3) || (i == 1 && j == 5) || (i == 2 && j == 1) || (i == 3 && j == 1) || (i == 3 && j == 2) || (i == 3 && j == 3) || (i == 3 && j == 4) || (i == 3 && j == 5) || (i == 5 && j == 3)) {
				Level[i + j * Width].ValidActions.Remove(Action::Down);
			}

			if ((i == 0 && j == 1) || (i == 0 && j == 3) || (i == 1 && j == 1) || (i == 1 && j == 2) || (i == 1 && j == 3) || (i == 4 && j == 3) || (i == 4 && j == 4)) {
				Level[i + j * Width].ValidActions.Remove(Action::Right);
				//Level[(i+1) + j * 6].ValidActions.Remove(Action::Left);
			}

			if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 2 && j == 1) || (i == 2 && j == 2) || (i == 2 && j == 3) || (i == 5 && j == 3) || (i == 5 && j == 4)) {
				Level[i + j * Width].ValidActions.Remove(Action::Left);
			}
		}
	}
	*/

	
	//LEVEL 12
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			Level[i + j * Width].ValidActions.Add(Action::Up);
			Level[i + j * Width].ValidActions.Add(Action::Down);
			Level[i + j * Width].ValidActions.Add(Action::Left);
			Level[i + j * Width].ValidActions.Add(Action::Right);
			Level[i + j * Width].ValidActions.Add(Action::Wait);
			Level[i + j * Width].Position = FVector2D(i, j);
			Level[i + j * Width].TileToGoal = Width * Height;

			//RemoveBoundaryActions
			if (i == 0) {
				Level[i + j * Width].ValidActions.Remove(Action::Left);
			}

			if (i == Width-1) {
				Level[i + j * Width].ValidActions.Remove(Action::Right);
			}

			if (j == 0) {
				Level[i + j * Width].ValidActions.Remove(Action::Down);
			}

			if (j == Height - 1) {
				Level[i + j * Width].ValidActions.Remove(Action::Up);
			}

			//RemoveWalledActions
			if ((i == 1 && j == 0) || (i == 0 && j == 2) ||(i == 2 && j == 0) || (i == 2 && j == 1) || (i == 3 && j == 1) || (i == 3 && j == 2) || (i == 4 && j == 2)) {
				Level[i + j * Width].ValidActions.Remove(Action::Up);
				//Level[i + (j+1) * 6].ValidActions.Remove(Action::Down);
			}

			if ((i == 1 && j == 1) || (i == 0 && j == 3) || (i == 2 && j == 1) || (i == 2 && j == 2) || (i == 3 && j == 2) || (i == 3 && j == 3) || (i == 4 && j == 3)) {
				Level[i + j * Width].ValidActions.Remove(Action::Down);
			}

			if ((i == 0 && j == 1) || (i == 0 && j == 2) || (i == 0 && j == 3) || (i == 1 && j == 2) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 2 && j == 4) || (i == 3 && j == 3)) {
				Level[i + j * Width].ValidActions.Remove(Action::Right);
				//Level[(i+1) + j * 6].ValidActions.Remove(Action::Left);
			}

			if ((i == 1 && j == 1) || (i == 1 && j == 2) || (i == 1 && j == 3) || (i == 2 && j == 2) || (i == 2 && j == 3) || (i == 3 && j == 2) || (i == 3 && j == 4) || (i == 4 && j == 3)) {
				Level[i + j * Width].ValidActions.Remove(Action::Left);
			}
		}
	}
	
	


	/*
	//LEVEL 7
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			Level[i + j * Width].ValidActions.Add(Action::Up);
			Level[i + j * Width].ValidActions.Add(Action::Down);
			Level[i + j * Width].ValidActions.Add(Action::Left);
			Level[i + j * Width].ValidActions.Add(Action::Right);
			Level[i + j * Width].ValidActions.Add(Action::Wait);
			Level[i + j * Width].Position = FVector2D(i, j);
			Level[i + j * Width].TileToGoal = Width * Height;

			//RemoveBoundaryActions
			if (i == 0) {
				Level[i + j * Width].ValidActions.Remove(Action::Left);
			}

			if (i == Width-1) {
				Level[i + j * Width].ValidActions.Remove(Action::Right);
			}

			if (j == 0) {
				Level[i + j * Width].ValidActions.Remove(Action::Down);
			}

			if (j == Height - 1) {
				Level[i + j * Width].ValidActions.Remove(Action::Up);
			}

			//RemoveWalledActions
			if ((i == 0 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 2)) {
				Level[i + j * Width].ValidActions.Remove(Action::Up);
				//Level[i + (j+1) * 6].ValidActions.Remove(Action::Down);
			}

			if ((i == 0 && j == 1) || (i == 1 && j == 2) || (i == 1 && j == 3) || (i == 2 && j == 3)) {
				Level[i + j * Width].ValidActions.Remove(Action::Down);
			}

			if ((i == 0 && j == 1) || (i == 2 && j == 2) || (i == 2 && j == 0)) {
				Level[i + j * Width].ValidActions.Remove(Action::Right);
				//Level[(i+1) + j * 6].ValidActions.Remove(Action::Left);
			}

			if ((i == 1 && j == 1) || (i == 3 && j == 2) || (i == 3 && j == 0)) {
				Level[i + j * Width].ValidActions.Remove(Action::Left);
			}
		}
	}
	*/
	
/*
	//LEVEL 4
for (int i = 0; i < Width; i++) {
	for (int j = 0; j < Height; j++) {
		Level[i + j * Width].ValidActions.Add(Action::Up);
		Level[i + j * Width].ValidActions.Add(Action::Down);
		Level[i + j * Width].ValidActions.Add(Action::Left);
		Level[i + j * Width].ValidActions.Add(Action::Right);
		Level[i + j * Width].ValidActions.Add(Action::Wait);
		Level[i + j * Width].Position = FVector2D(i, j);
		Level[i + j * Width].TileToGoal = Width * Height;

		//RemoveBoundaryActions
		if (i == 0) {
			Level[i + j * Width].ValidActions.Remove(Action::Left);
		}

		if (i == Width - 1) {
			Level[i + j * Width].ValidActions.Remove(Action::Right);
		}

		if (j == 0) {
			Level[i + j * Width].ValidActions.Remove(Action::Down);
		}

		if (j == Height - 1) {
			Level[i + j * Width].ValidActions.Remove(Action::Up);
		}

		//RemoveWalledActions
		if ((i == 0 && j == 1) || (i == 2 && j == 1) ) {
			Level[i + j * Width].ValidActions.Remove(Action::Up);
			//Level[i + (j+1) * 6].ValidActions.Remove(Action::Down);
		}

		if ((i == 0 && j == 2) || (i == 2 && j == 2)) {
			Level[i + j * Width].ValidActions.Remove(Action::Down);
		}

		if ((i == 0 && j == 2) || (i == 1 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 2)) {
			Level[i + j * Width].ValidActions.Remove(Action::Right);
			//Level[(i+1) + j * 6].ValidActions.Remove(Action::Left);
		}

		if ((i == 1 && j == 2) || (i == 2 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 2)) {
			Level[i + j * Width].ValidActions.Remove(Action::Left);
		}
	}
}
*/
	

	TArray<Room> RoomsToExplore;
	
	Level[PositionToIndex(GoalPosition)].TileToGoal = 0;
	Room GoalRoom = Level[PositionToIndex(GoalPosition)];
	RoomsToExplore.Add(GoalRoom);

	
	while (RoomsToExplore.Num() != 0) {
		Room r = RoomsToExplore.Pop();
		
		for (auto a : r.ValidActions) {
			if (a == Action::Wait) continue;
			int  r2Index  = PositionToIndex(r.Position + ActionToFVector2D(a));
			if (Level[r2Index].TileToGoal > r.TileToGoal + 1) {
				Level[r2Index].TileToGoal = r.TileToGoal + 1;
				RoomsToExplore.Add(Level[r2Index]);
			}
		}
	}


	for (auto b : Level) {
		
			FVector Location = FVector(100.f * b.Position.Y, 100.f * b.Position.X, 0.f);
			ABlock* RoomBlock = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
			RoomBlock->SetFloor();

			if (b.Position == GoalPosition) {
				RoomBlock->SetGoal();
			}
			else {
				RoomBlock->SetFloor();
			}
			LevelBlocks.Add(RoomBlock);
			if (!b.ValidActions.Contains(Action::Left)) {
				Location = FVector(100.f * b.Position.Y, 100.f * b.Position.X, 100.f);
				ABlock* RoomWall = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
				RoomWall->SetWall(FVector2D(-1, 0));
				LevelBlocks.Add(RoomWall);
			}
			if (!b.ValidActions.Contains(Action::Right)) {
				Location = FVector(100.f * b.Position.Y, 100.f * b.Position.X, 100.f);
				ABlock* RoomWall = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
				RoomWall->SetWall(FVector2D(1, 0));
				LevelBlocks.Add(RoomWall);
			}
			if (!b.ValidActions.Contains(Action::Down)) {
				Location = FVector(100.f * b.Position.Y, 100.f * b.Position.X, 100.f);
				ABlock* RoomWall = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
				RoomWall->SetWall(FVector2D(0,-1));
				LevelBlocks.Add(RoomWall);
			}
			if (!b.ValidActions.Contains(Action::Up)) {
				Location = FVector(100.f * b.Position.Y, 100.f * b.Position.X, 100.f);
				ABlock* RoomWall = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
				RoomWall->SetWall(FVector2D(0, 1));
				LevelBlocks.Add(RoomWall);
			}
	}

	FVector Location = FVector(100.f * TheseusInitialPosition.Y, 100.f * TheseusInitialPosition.X, 100.f);
	TheseusBlock = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
	TheseusBlock->SetTheseus();

	Location = FVector(100.f * MinotaurInitialPosition.Y, 100.f * MinotaurInitialPosition.X, 100.f);
	MinotaurBlock = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), Location, FRotator::ZeroRotator);
	MinotaurBlock->SetMinotaur();


	P = Population();
	//P.Initialize(PopulationSize, NumActions, FVector2D(4,1), FVector2D(0,5), FVector2D(5,3));
	P.Initialize(PopulationSize, NumActions);

	
	

	
}

// Called every frame
void ALevelSimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Completed) {
		if (P.Generation < MaxGenerations) {
			if (CurrentAction < NumActions) {
				P.Run(CurrentAction);
				CurrentAction++;
			}
			else {
				P.Evaluate();
				LastGenAverageFitness = P.AverageFit;
				LastGenMaxFitness = P.MaxFit;
				CurrentAction = 0;
				CurrentGeneration++;

				if (LastGenMaxFitness > BestFitness) {
					BestFitness = LastGenMaxFitness;
					BestDNA = P.BestDNA;
				}

				if (P.Generation == MaxGenerations - 1 ) {
					Completed = true;
				}
				else {
					P.Selection();
				}
			}
		}
	}


	if (Cooldown <= 0.0f) {

		if (Locked) {
			if (Minotaur1stMove) {
				FVector Location = FVector(100.f * Player.MinotaurPosition.Y, 100.f * Player.MinotaurPosition.X, 100.f);
				MinotaurBlock->SetActorLocation(Location, false);
				if (Player.Caught || Player.Escaped) {
					if (Player.Caught) {
						MinotaurBlock->SetActorLocation(MinotaurBlock->GetActorLocation() + FVector(0, 0, 100), false);
					}
					Locked = true;
				}
				else {
					Player.MoveMinotaur();
					Minotaur1stMove = false;
					Minotaur2ndMove = true;
				}
			}
			else if (Minotaur2ndMove) {
				FVector Location = FVector(100.f * Player.MinotaurPosition.Y, 100.f * Player.MinotaurPosition.X, 100.f);
				MinotaurBlock->SetActorLocation(Location, false);
				

				if (Player.Caught || Player.Escaped) {
					if (Player.Caught) {
						MinotaurBlock->SetActorLocation(MinotaurBlock->GetActorLocation() + FVector(0, 0, 100), false);
					}

					Locked = true;
				}
				else {
					Locked = false;
				}
			}
			else {
				FVector Location = FVector(100.f * Player.TheseusPosition.Y, 100.f * Player.TheseusPosition.X, 100.f);
				TheseusBlock->SetActorLocation(Location, false);
				if (Player.Caught || Player.Escaped) {
					if (Player.Caught) {
						MinotaurBlock->SetActorLocation(MinotaurBlock->GetActorLocation() + FVector(0, 0, 100), false);
					}
					Locked = true;
				}
				else {
					Player.MoveMinotaur();
					Minotaur1stMove = true;
				}

				
			}
		}

		Cooldown = 0.1f;
	}
	else {
		Cooldown -= DeltaTime;
	}
	
}
	
	

void ALevelSimulation::SetGenerations(int gen) {
	MaxGenerations = gen;
	if (P.Generation >= MaxGenerations) Completed = true;
	else Completed = false;

}
void ALevelSimulation::SetNumActions(int num) {
	Completed = true;
	NumActions = num;
	Initialize();
	Completed = false;
}

void  ALevelSimulation::SetPopulationSize(int size) {
	Completed = true;
	PopulationSize = size;
	Initialize();
	Completed = false;
}


void ALevelSimulation::SetMutationRate(float rate) {
	MutationRate = rate;
	MutationProbability = rate;
}


void ALevelSimulation::Initialize() {
	CurrentAction = 0;

	CurrentGeneration = 1;
	LastGenAverageFitness = 0.0f;
	LastGenMaxFitness = 0.0f;
	BestDNA = "N/A";
	BestFitness = 0.0f;

	P.Initialize(PopulationSize, NumActions);
}


void ALevelSimulation::MoveTheseus(FVector2D Direction) {
	Minotaur1stMove = false;
	Minotaur2ndMove = false;
	Locked = true;
	if (Direction == FVector2D(1, 0)) {
		Player.MoveTheseusWithAction(Action::Right);
	}
	else if (Direction == FVector2D(-1, 0)) {
		Player.MoveTheseusWithAction(Action::Left);
	}
	else if (Direction == FVector2D(0, 1)) {
		Player.MoveTheseusWithAction(Action::Up);
	}
	else if (Direction == FVector2D(0, -1)) {
		Player.MoveTheseusWithAction(Action::Down);
	}
	else if (Direction == FVector2D(0, 0)) {
		Player.MoveTheseusWithAction(Action::Wait);
	}
	

}

void ALevelSimulation::ResetTheseus() {
	Minotaur1stMove = false;
	Minotaur2ndMove = false;
	Locked = true;


	FVector Location = FVector(100.f * TheseusInitialPosition.Y, 100.f * TheseusInitialPosition.X, 100.f);
	TheseusBlock->SetActorLocation(Location, false);

	Location = FVector(100.f * MinotaurInitialPosition.Y, 100.f * MinotaurInitialPosition.X, 100.f);
	MinotaurBlock->SetActorLocation(Location, false);

	Player.Initialize();


	Locked = false;

}