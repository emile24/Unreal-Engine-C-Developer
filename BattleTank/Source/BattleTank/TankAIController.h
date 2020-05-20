// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

    protected:
        virtual void BeginPlay() override;

    public:
        virtual void Tick(float DeltaSeconds) override;
        
   private:
       ATank* GetControlledTank() const;
       ATank* GetPlayerTank() const;

       //void AimTowardsPlayer() const;

    private:
        ATank* ControlledTank;
        ATank* PlayerTank;
};
