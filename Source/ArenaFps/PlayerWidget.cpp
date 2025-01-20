// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
///
//
void UPlayerWidget::TurnScreenRed()
{
	RedScreen->SetOpacity(1.0f);

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
        if (RedScreen)
        {
            RedScreen->SetOpacity(0.0f);
        }
        }, 0.2f, false);
}

void UPlayerWidget::ChangeProgressBarFill(float amount)
{
    ProgressBar->SetPercent(amount);
}