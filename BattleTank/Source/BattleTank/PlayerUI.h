// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "PlayerUI.generated.h"

class UCanvasPanel;
class UImage;
class UButton;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()


public:
    virtual bool Initialize() override;

public:
    UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
    UCanvasPanel* Panel;
    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    UImage* AimPoint;
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UButton* Button1;
    UPROPERTY(EditDefaultsOnly)
    UTankAimingComponent* TankAimingComponent;
	
};
