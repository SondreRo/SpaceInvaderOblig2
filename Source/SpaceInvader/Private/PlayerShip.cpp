// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"



#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
//Input
#include <string>

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values

APlayerShip::APlayerShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Mesh->SetStaticMesh(MeshComponentAsset.Object);


	SetRootComponent(Mesh);



	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 800.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10;
	SpringArm->bEnableCameraRotationLag = true;

	

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SetActorLocation(FVector(0.f, 0.f, 100.f));

	MovementSpeed = 200;
	MaxShotTimer = 0.1f;
	ShotTimer = MaxShotTimer;

	ShotHeat = 0;
	MaxShotHeat = 100;

	limitTop = 2560;
	limitBotton = 460;
	limitRight = 2330;
	limitLeft = -2330;

	Health = 5;
	gameDone = false;

	

}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(IMCinput, 0);

		}
	}

	

}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (Health <= 0)
	{
		MovementSpeed = 0;
		gameDone = true;
		
		//Mesh->SetSimulatePhysics(true);
	}



	//MoveShip
	
	SetActorLocation(GetActorLocation() + FVector(xAxisSpeed, yAxisSpeed, zAxisSpeed));

	xAxisSpeed /= 1.03f;
	yAxisSpeed /= 1.03f;
	zAxisSpeed /= 1.03f;

	this->deltaTime = DeltaTime;

	if (GetActorLocation().Z > limitTop)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, limitTop));
		zAxisSpeed = 0;
	}
	if (GetActorLocation().Z < limitBotton)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, limitBotton));
		zAxisSpeed = 0;
	}
	if (GetActorLocation().Y > limitRight)
	{
		SetActorLocation(FVector(GetActorLocation().X, limitRight, GetActorLocation().Z));
		yAxisSpeed = 0;
	}

	if (GetActorLocation().Y < limitLeft)
	{
		SetActorLocation(FVector(GetActorLocation().X, limitLeft, GetActorLocation().Z));
		yAxisSpeed = 0;
	}

	if (ShotTimer>= 0)
	{
		ShotTimer -= deltaTime;
	}


	if (ShotHeat > 0)
	{
		ShotHeat -= 30 * DeltaTime;
	}
	else if (ShotHeat < 0)
	{
		ShotHeat = 0;
	}

	if (ShotHeat >= MaxShotHeat)
	{
		canShoot = false;
	}

	if (ShotHeat == 0 && !canShoot)
	{
		canShoot = true;
	}

	FString stringToPrint = FString::SanitizeFloat(ShotHeat);
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Orange, stringToPrint);
}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputCom->BindAction(IA_UP, ETriggerEvent::Triggered, this, &APlayerShip::UPPressed);
		
		EnhancedInputCom->BindAction(IA_Down, ETriggerEvent::Triggered, this, &APlayerShip::DownPressed);

		EnhancedInputCom->BindAction(IA_Left, ETriggerEvent::Triggered, this, &APlayerShip::LeftPressed);

		EnhancedInputCom->BindAction(IA_Right, ETriggerEvent::Triggered, this, &APlayerShip::RightPressed);

		EnhancedInputCom->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &APlayerShip::ShootPressed);

	}

	


}

void APlayerShip::UPPressed(const FInputActionValue& val)
{
	if (GetActorLocation().Z < limitTop)
	{
		
	////GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Up IS Pressed");

	//FVector CurrentPos = GetActorLocation();

	//FVector AddPos = FVector(
	//	0.f,	//X
	//	0.f,	//Y
	//	MovementSpeed	//Z
	//);
	//
	//SetActorLocation(CurrentPos + AddPos * deltaTime);

		zAxisSpeed += MovementSpeed * deltaTime;


	}
	

}

void APlayerShip::DownPressed(const FInputActionValue& val)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Up IS Pressed");
	if (GetActorLocation().Z > limitBotton)
	{
		//FVector CurrentPos = GetActorLocation();

		//FVector AddPos = FVector(
		//	0.f,	//X
		//	0.f,	//Y
		//	-MovementSpeed	//Z
		//);

		//SetActorLocation(CurrentPos + AddPos * deltaTime);

		zAxisSpeed -= MovementSpeed * deltaTime;

	}
	
	

}

void APlayerShip::LeftPressed(const FInputActionValue& val)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Up IS Pressed");
	if (GetActorLocation().Y > limitLeft)
	{
		//FVector CurrentPos = GetActorLocation();

		//FVector AddPos = FVector(
		//	0.f,	//X
		//	-MovementSpeed,	//Y
		//	0.f	//Z
		//);

		//SetActorLocation(CurrentPos + AddPos * deltaTime);

		yAxisSpeed -= MovementSpeed * deltaTime;
	}
	
	
}

void APlayerShip::RightPressed(const FInputActionValue& val)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Up IS Pressed");
	if (GetActorLocation().Y < limitRight)
	{
		
	//FVector CurrentPos = GetActorLocation();

	//FVector AddPos = FVector(
	//	0.f,	//X
	//	MovementSpeed,	//Y
	//	0.f	//Z
	//);

	//SetActorLocation(CurrentPos + AddPos * deltaTime);
		yAxisSpeed += MovementSpeed * deltaTime;
	}
	
}

void APlayerShip::ShootPressed(const FInputActionValue& val)
{
	if (ShotTimer <= 0 && canShoot && !gameDone)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Pew");

		ShotTimer = MaxShotTimer;
		ShotHeat += 5;

		
		
		if (ShotRight)
		{
			GetWorld()->SpawnActor<AActor>(
				Bullet_BP,
				GetActorLocation() + FVector(273.31489, -511.479974, -115.832915), //+ FVector(263.604652, -512.304384, -15.606176),	//GetActorLocation() + FVector(30.f,0.f,0.f),
				GetActorRotation());

			ShotRight = false;
			//TODO
			//Cast<ABullet>(Bullet_BP)->AddPlayerToBullet();
		}
		else
		{
			GetWorld()->SpawnActor<AActor>(
				Bullet_BP,
				GetActorLocation() + FVector(273.31489, 511.479974, -115.832915), //+ FVector(263.604652, -512.304384, -15.606176),	//GetActorLocation() + FVector(30.f,0.f,0.f),
				GetActorRotation());
				

			ShotRight = true;
		}
	}

	

	
	
}

void APlayerShip::HitByTarget()
{

	Health--;
	if(Health <= 0)
	{
		//TODO GAME OVER
	}

	FString stringToPrint = FString::FromInt(Health);
	GEngine->AddOnScreenDebugMessage(-2, 4.f, FColor::Green, stringToPrint);

}


