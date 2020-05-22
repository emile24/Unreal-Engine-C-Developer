// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerUI.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		ATankPlayerController();

	protected:
		virtual void BeginPlay() override;

	public:
		virtual void Tick(float DeltaSeconds) override;
	
	public:
		ATank* GetControlledTank() const;

	private:
		//StartThe tnak moving the barrel so that a shot would hit where
		// the crosshair intersects the world
		void AimTowardsCrosshair();

		//Return an OUT parameter, true if hit landscape
		bool GetSightRayHitLocation(FVector& HitLocation) const;

		bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;

		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


	private:
		TSubclassOf<class UUserWidget> PlayerUIClass;
		class UPlayerUI* PlayerUI;

		ATank* ControlledTank;

		UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

		UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333f;

		UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;

};
