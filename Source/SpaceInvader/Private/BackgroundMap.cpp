// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundMap.h"

// Sets default values
ABackgroundMap::ABackgroundMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Mesh->SetStaticMesh(MeshComponentAsset.Object);


	SetRootComponent(Mesh);

	MovementSpeed = 200;
	ModelLength = 32131;
	AmountSpawned = 4;

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

	if (GetActorLocation().X < -ModelLength)
	{
		SetActorLocation(GetActorLocation() + FVector(ModelLength * AmountSpawned, 0, 0));
	}



	FVector NewLocation = GetActorLocation() + (FVector(-MovementSpeed, 0, 0) * DeltaTime * 60);
	SetActorLocation(NewLocation);
}

