// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/InputComponent.h"


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"



class ABullet;
struct FInputActionValue;
UCLASS()
class SPACEINVADER_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* ShootingSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* CantShootSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* DeathSound;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpringArm)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* Camera;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputMappingContext* IMCinput;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* IA_UP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* IA_Down;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* IA_Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* IA_Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* IA_Shoot;






	





	UFUNCTION(BlueprintCallable, Category = Functions)
		void UPPressed(const FInputActionValue& val);
		void DownPressed(const FInputActionValue& val);
		void LeftPressed(const FInputActionValue& val);
		void RightPressed(const FInputActionValue& val);

		void ShootPressed(const FInputActionValue& val);

		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<ABullet> Bullet_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxShotTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float ShotHeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool gameDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float shotsFired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool ShotRight;

	UFUNCTION(BlueprintImplementableEvent)
		void ShotFired();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxShotHeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float RollForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float PitchForce;

	void HitByTarget();
	
	

private:
	float deltaTime;

	
	float ShotTimer;
	

	
	

	float xAxisSpeed;
	float yAxisSpeed;
	float zAxisSpeed;


	float limitTop;
	float limitBotton;
	float limitRight;
	float limitLeft;



	bool canShoot;


};
