// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackgroundMap.generated.h"

UCLASS()
class SPACEINVADER_API ABackgroundMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroundMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVeriables)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVeriables)
		float ModelLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVeriables)
		float AmountSpawned;
};
