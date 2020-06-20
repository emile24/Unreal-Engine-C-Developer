// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Tack is used to set maximum driving force and apply force to move the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

protected:

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	void DriveTrack();

private:

	UFUNCTION(BlueprintCallable, Category = "Hit")
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
private:

	// Max force per track in newton
	UPROPERTY(EditDefaultsOnly)
	float MaxTrackDrivingForce = 40000000.f; // Assume 40 tonne tank and 1g acceleration

	float CurrentThrottle = 0.f;

};
