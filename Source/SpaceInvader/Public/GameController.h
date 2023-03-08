// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameController.generated.h"

class AEnemy;

UCLASS()
class SPACEINVADER_API AGameController : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<int> WaveSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<int> WaveDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<float> WaveFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float xPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Min_yPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Max_yPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Min_zPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Max_zPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "My Variables")
	int WaveNumber;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<AEnemy> Enemy_BP;
private:
	int EnemyNumbers;
	float timer;
	bool GameWon;

	void ChangeWave(int Wave);
};
