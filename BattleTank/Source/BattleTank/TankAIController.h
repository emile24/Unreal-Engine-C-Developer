// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declaration

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

        // How close can the AI Tank get
        float AcceptanceRadius = 3000.f;

};
