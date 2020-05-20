// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual bool Initialize() override;

private:
    UPROPERTY(meta = (BindWidget))
        class UCanvasPanel* Panel;
    UPROPERTY(meta = (BindWidget))
        class UImage* AimPoint;
	
};
