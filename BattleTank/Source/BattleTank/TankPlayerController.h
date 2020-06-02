// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerUI.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player control the tank
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		ATankPlayerController();

	protected:
		virtual void BeginPlay() override;

		UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	public:
		virtual void Tick(float DeltaSeconds) override;
	
	public:

	private:
		//StartThe tnak moving the barrel so that a shot would hit where
		// the crosshair intersects the world
		void AimTowardsCrosshair();

		//Return an OUT parameter, true if hit landscape
		bool GetSightRayHitLocation(FVector& HitLocation) const;

		bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;

		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


	private:

		UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

		UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333f;

		UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;

};
