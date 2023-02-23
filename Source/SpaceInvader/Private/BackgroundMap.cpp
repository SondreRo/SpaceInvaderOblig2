// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundMap.h"

// Sets default values
ABackgroundMap::ABackgroundMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABackgroundMap::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABackgroundMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("HEllP"));

}

