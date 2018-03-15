// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "BattleTank.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (GetPlayerTank())
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerPawn = GetPlayerTank();

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find PlayerTank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank is: %s"), (*PlayerPawn->GetName()));
	}

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing: %s"), (*ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));
}
  
