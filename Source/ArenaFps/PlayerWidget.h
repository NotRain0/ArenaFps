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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* FireFeedback1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* FireFeedback2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* FireFeedback3;

	void TurnScreenRed();
	void DisplaySpeedOnDash();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void ChangeOverHeatProgress(float percent);

	void ChangeProgressBarFill(float amount);
};
