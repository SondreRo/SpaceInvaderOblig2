// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


#include "PlayerShip.h"

#include "Components/SphereComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(10.f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(2, 2, 2));

	MovementSpeed = 10000;
	RotationSpeed = 1.f;
	XKillPosition = -900;

	health = 1;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	RotationSpeed = FMath::RandRange(0.5f, 1.5f);
	MovementSpeed += FMath::RandRange(0, 255);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += FVector(-1, 0, 0) * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	SetActorRotation(GetActorRotation() + FRotator(0.f, RotationSpeed, 0.f));

	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}

	if (health <= 0)
	{
		DestroyTarget();
		//Cast<APlayerShip>(OtherActor)->HitByTarget();
	}

}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APlayerShip>())
	{
		Cast<APlayerShip>(OtherActor)->HitByTarget();
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "HitPlayerShip");
		DestroyTarget();
	}
	
}

void AEnemy::DestroyTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, "DestroyEnemy");
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();

}

void AEnemy::TakeDamage()
{
	health--;
}

