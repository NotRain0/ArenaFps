// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
class UImage;
class UProgressBar;
class UTextBlock;

UCLASS()
class ARENAFPS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public : 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Crosshair_Main;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Crosshair_Side;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* RedScreen;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SpeedVisual;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* OverHeatProgress;

	void TurnScreenRed();
	void DisplaySpeedOnDash();

	void ChangeProgressBarFill(float amount);
};
