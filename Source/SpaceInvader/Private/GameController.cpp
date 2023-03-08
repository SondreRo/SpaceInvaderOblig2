// Fill out your copyright notice in the Description page of Project Settings.

#include "GameController.h"
#include "Enemy.h"

AGameController::AGameController()
{
	PrimaryActorTick.bCanEverTick = true;

	WaveSize.Add(15);
	WaveSize.Add(20);
	WaveSize.Add(30);

	WaveDifficulty.Add(1);
	WaveDifficulty.Add(1.5);
	WaveDifficulty.Add(2);

	WaveFrequency.Add(2);
	WaveFrequency.Add(1);
	WaveFrequency.Add(0.5f);

	xPos = 64000;

	Min_yPos = -3200;
	Max_yPos = 3200;

	Min_zPos = 300;
	Max_zPos = 2700;
}

void AGameController::BeginPlay()
{
	Super::BeginPlay();

	WaveNumber = 1;
	EnemyNumbers = WaveSize[WaveNumber - 1];
}

void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;

	if (timer > WaveFrequency[WaveNumber-1] && !GameWon)
	{
		timer = 0.f;
		FVector SpawnLocation = FVector(xPos, FMath::RandRange(Min_yPos, Max_yPos), FMath::RandRange(Min_zPos, Max_zPos));

		AActor* Actor = GetWorld()->SpawnActor<AActor>(Enemy_BP, SpawnLocation, FRotator::ZeroRotator);
		AEnemy* Enemy = Cast<AEnemy>(Actor);

		Enemy->MovementSpeed *= WaveDifficulty[WaveNumber - 1];
		EnemyNumbers--;
		if (EnemyNumbers <= 0)
		{
			ChangeWave(WaveNumber + 1);
		}
	}

}

void AGameController::ChangeWave(int Wave)
{
	if (WaveSize.Num() < Wave)
	{
		GameWon = true;
		return;
	}

	WaveNumber = Wave;
	EnemyNumbers = WaveSize[Wave - 1];
}

