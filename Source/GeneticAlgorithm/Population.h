// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum Action {
	Left,
	Right,
	Up,
	Down,
	Wait
};

const Action MinotaurActions[4] = { Action::Left, Action::Right, Action::Up, Action::Down };
const Action MinotaurHorizontalActions[4] = { Action::Left, Action::Right };
const Action MinotaurVerticalActions[4] = { Action::Up, Action::Down };

struct Room  {
	TArray<Action> ValidActions;
	int TileToGoal;
	FVector2D Position;
};

static float MutationProbability = 0.2f;
static int NumActions = 5;
static int Width = 5;
static int Height = 5;
static TArray<Room> Level;

//LEVEL 12 GOAL(0,2) THESEUS(4,3) MINOTAUR(0,2)
//LEVEL 7 GOAL(3,0) THESEUS(2,1) MINOTAUR(3,2)
static FVector2D GoalPosition = FVector2D(0,2);
static FVector2D TheseusInitialPosition = FVector2D(4,3);
static FVector2D MinotaurInitialPosition = FVector2D(0,2);


static Action RandomAction() {
	return (Action)(FMath::Rand() % NumActions);
}

static TArray<Action> RandomDNA(int ActionSize) {
	TArray<Action> Actions;
	for (int i = 0; i < ActionSize; i++) {
		Actions.Add(RandomAction());
	}
	return Actions;
}

static TArray<Action> CrossOver(TArray<Action> ParentA, TArray<Action> ParentB) {
	TArray<Action> NewGenes;
	int GeneSize = ParentA.Num();
	int MiddleIndex = FMath::RandRange(0, GeneSize - 1);

	for (int i = 0; i < GeneSize; i++) {
		if (i < MiddleIndex) {
			NewGenes.Add(ParentA[i]);
		}
		else {
			NewGenes.Add(ParentB[i]);
		}
	}
	return NewGenes;
}

static TArray<Action> CrossOverScramble(TArray<Action> ParentA, TArray<Action> ParentB) {
	TArray<Action> NewGenes;
	int GeneSize = ParentA.Num();

	for (int i = 0; i < GeneSize; i++) {
		if (0.5 < FMath::FRandRange(0.f, 1.0f)) {
			NewGenes.Add(ParentA[i]);

		}
		else {
			NewGenes.Add(ParentB[i]);
		}

	}
	return NewGenes;
}

static void Mutation(TArray<Action>& OriginalDNA) {
	for (int i = 0; i < OriginalDNA.Num(); i++) {
		if (FMath::FRandRange(0.0, 1.0) < MutationProbability) {
			OriginalDNA[i] = RandomAction();
		}
	}
}

static int PositionToIndex(FVector2D Position) {
	return Position.X + Position.Y * Width;
}

static FVector2D ActionToFVector2D(Action a) {
	switch (a) {
	case Action::Left:
		return FVector2D(-1, 0);
		break;
	case Action::Right:
		return FVector2D(1, 0);
		break;
	case Action::Down:
		return FVector2D(0, -1);
		break;
	case Action::Up:
		return FVector2D(0, 1);
		break;
	}
	return FVector2D::ZeroVector;
}

static FString DNAToString(TArray<Action> DNA) {
	FString DNAString = "";
	for (auto a : DNA) {
		switch (a) {
		case Action::Down:
			DNAString += "D ";
			break;
		case Action::Up:
			DNAString += "U ";
			break;
		case Action::Left:
			DNAString += "L ";
			break;
		case Action::Right:
			DNAString += "R ";
			break;
		case Action::Wait:
			DNAString += "W ";
			break;
		}
	}

	return DNAString;
}


class GENETICALGORITHM_API Agent
{
public:
	Agent() {}

	TArray<Action> DNA;
	bool Caught, Escaped;
	float Fitness;

	FVector2D MinotaurPosition;
	FVector2D TheseusPosition;
	int InvalidActions;
	int TotalActions;
	int UndoActions;
	Action LastAction;
	int MinotaurStuckTime;
	TArray<int> TheseusDifferentRoomsExplored;
	TArray<int> MinotaurDifferentRoomsExplored;
	TArray<Action> MinotaurMovement;


	void Initialize() {
		TheseusPosition = TheseusInitialPosition;
		MinotaurPosition = MinotaurInitialPosition;
		Caught = false;
		Escaped = false;
		Fitness = 0.0f;
		TotalActions = 0;
		InvalidActions = 0;
		MinotaurStuckTime = 0;
	}


	void Initialize(TArray<Action> GivenDNA) {
		TheseusPosition = TheseusInitialPosition;
		MinotaurPosition = MinotaurInitialPosition;
		DNA = GivenDNA;
		Caught = false;
		Escaped = false;
		Fitness = 0.0f;
		TotalActions = 0;
		InvalidActions = 0;
		MinotaurStuckTime = 0;
		UndoActions = 0;
		LastAction = Action::Wait;
	}

	void CalculateFitness() {
		//Fitness = 1 / (1 + InvalidActions + (GoalPosition - TheseusPosition).Size());
		//Fitness = 1 / (1 + InvalidActions);

		
		Fitness = (TheseusDifferentRoomsExplored.Num() * MinotaurDifferentRoomsExplored.Num() + TotalActions + 1.0f) / (1.0f + Level[PositionToIndex(TheseusPosition)].TileToGoal*10.0f + InvalidActions + UndoActions);
		//Fitness = 1 / ( 1.0f + Level[PositionToIndex(TheseusPosition)].TileToGoal);

		if (Escaped) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Escaped");
		Fitness += 10000.0f / (TotalActions + InvalidActions);
		//Fitness *= 100.0f;
		}
		else if (Caught) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Caught");

			//Fitness = (TotalActions + TheseusDifferentRoomsExplored.Num() * MinotaurDifferentRoomsExplored.Num());
			//Fitness /= 2.f;
		}
		
	}



	

	void Update(int TimeStep) {
		if (!Caught && !Escaped) {
			MoveTheseus(TimeStep);
			MoveMinotaur();
			MoveMinotaur();
		}
	}


	void MoveTheseus(int TimeStep) {
	

		int IndexRoom = PositionToIndex(TheseusPosition);
		Room r = Level[IndexRoom];
		Action a = DNA[TimeStep];
		if (r.ValidActions.Contains(a)) {
			TheseusPosition += ActionToFVector2D(a);
			TheseusDifferentRoomsExplored.AddUnique(IndexRoom);
			
			if (a == Action::Wait) InvalidActions++;
			if (IsUndoAction(a)) UndoActions++;
			LastAction = a;
		}
		else {
			InvalidActions++;
		}
		TotalActions++;

		CheckDefeat();
		CheckVictory();

	}


	void MoveTheseusWithAction(Action a) {


		int IndexRoom = PositionToIndex(TheseusPosition);
		Room r = Level[IndexRoom];
		if (r.ValidActions.Contains(a)) {
			TheseusPosition += ActionToFVector2D(a);
			TheseusDifferentRoomsExplored.AddUnique(IndexRoom);



		}
		else {
			InvalidActions++;
		}
		TotalActions++;

		CheckDefeat();
		CheckVictory();

	}

	void MoveMinotaur() {

		float CurrentDistance = (TheseusPosition - MinotaurPosition).SizeSquared();

		int RoomIndex = PositionToIndex(MinotaurPosition);
		Room r = Level[RoomIndex];

		bool CheckH, CheckV;

		if (MinotaurPosition.X == TheseusPosition.X) {
			CheckH = false;
			CheckV = true;
		}
		else if (MinotaurPosition.Y == TheseusPosition.Y) {
			CheckH = true;
			CheckV = false;
		}
		else {
			CheckH = true;
			CheckV = true;
		}


		if (CheckH) {
			for (auto a : r.ValidActions) {
				FVector2D NewMinotaurPosition = MinotaurPosition + ActionToFVector2D(a);
				float NewDistance = (TheseusPosition - NewMinotaurPosition).SizeSquared();

				if (NewDistance < CurrentDistance && (a == Action::Left || a == Action::Right)) {
					MinotaurPosition = NewMinotaurPosition;
					MinotaurDifferentRoomsExplored.AddUnique(RoomIndex);
					MinotaurMovement.Add(a);
					
					CheckDefeat();
					return;
				}
			}
		}

		if (CheckV) {
			for (auto a : r.ValidActions) {
				FVector2D NewMinotaurPosition = MinotaurPosition + ActionToFVector2D(a);
				float NewDistance = (TheseusPosition - NewMinotaurPosition).SizeSquared();

				if (NewDistance < CurrentDistance && (a == Action::Up || a == Action::Down)) {
					MinotaurPosition = NewMinotaurPosition;
					MinotaurDifferentRoomsExplored.AddUnique(RoomIndex);
					MinotaurMovement.Add(a);
					

					CheckDefeat();
					return;
				}
			}
		}
		MinotaurMovement.Add(Action::Wait);

	}


	void CheckDefeat() {
		if (MinotaurPosition == TheseusPosition) {
			Caught = true;
		}
	}

	void CheckVictory() {
		if (GoalPosition == TheseusPosition && !Caught) {
			Escaped = true;
		}
	}

	bool IsUndoAction(Action a) {
		switch (a) {
		case Action::Left:
			return LastAction == Action::Right;
			break;
		case Action::Right:
			return LastAction == Action::Left;
			break;
		case Action::Up:
			return LastAction == Action::Down;
			break;
		case Action::Down:
			return LastAction == Action::Up;
			break;
		}
		return false;
	}
	

};



class GENETICALGORITHM_API Population
{
public:
	TArray<Agent> Agents;
	TArray<Agent> MatingPool;
	int PopulationSize;
	int Generation;
	float AverageFit;
	float MaxFit;
	FString BestDNA;

	Population() {}

	void Initialize(int AgentSize, int ActionSize) {
		Agents.SetNum(AgentSize);
		PopulationSize = AgentSize;
		Generation = 0;
		MaxFit = 0.0f;
		AverageFit = 0.0f;
		BestDNA = "N/A";
		
		for (int i = 0; i < PopulationSize; i++) {
			Agents[i].Initialize(RandomDNA(ActionSize));
		}
	}

	void Evaluate() {
		AverageFit = 0.0f;
		MaxFit = 0.0f;
		Agent BestAgent;
		for (int i = 0; i < PopulationSize; i++) {
			Agents[i].CalculateFitness();
			if (Agents[i].Fitness > MaxFit) {
				MaxFit = Agents[i].Fitness;
				BestDNA = DNAToString(Agents[i].DNA);
				BestAgent = Agents[i];
			}
			AverageFit += Agents[i].Fitness;
		}
		AverageFit /= PopulationSize;


	
		MatingPool.Empty();
		MatingPool.Add(BestAgent); //To Garantee the matingpool is not empty
		for (int i = 0; i < PopulationSize; i++) {
			//Agents[i].Fitness /= MaxFit;

			float n = Agents[i].Fitness / MaxFit * 1000;
			for (int j = 0; j < n; j++) {
				MatingPool.Add(Agents[i]);
			}
		}
	}

	void Selection() {
		TArray<Agent> NewAgents;
		NewAgents.SetNum(PopulationSize);

		for (int i = 0; i < PopulationSize; i++) {
			TArray<Action> ParentA = MatingPool[FMath::RandRange(0, MatingPool.Num() - 1)].DNA;
			TArray<Action> ParentB = MatingPool[FMath::RandRange(0, MatingPool.Num() - 1)].DNA;
			//TArray<Action> NewGenes = CrossOver(ParentA, ParentB);
			TArray<Action> NewGenes = CrossOverScramble(ParentA, ParentB);
			
			Mutation(NewGenes);

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ParentA " + FString::FromInt(NewGenes.Num()) + " and ParentB " + FString::FromInt(ParentB.Num()));


			NewAgents[i].Initialize(NewGenes);

		}

		Agents = NewAgents;
		Generation++;
	}


	void Run(int TimeStep) {
		for (int i = 0; i < PopulationSize; i++) {
			Agents[i].Update(TimeStep);
		}
	}

};





