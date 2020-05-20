// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing %s"), *(ControlledTank->GetName()));
	}

	PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find the player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerTank) {
		//TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready

	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("No PlayerController found"));
		return nullptr;
	}
	
	return Cast<ATank>(PlayerController->GetPawn());	
}
