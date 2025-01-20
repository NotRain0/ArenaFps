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

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

	void TurnScreenRed();
	void ChangeProgressBarFill(float amount);
};
