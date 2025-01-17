// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENAFPS_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public : 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Crosshair_Main;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Crosshair_Side;
	
};
