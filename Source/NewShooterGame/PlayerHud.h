// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class NEWSHOOTERGAME_API APlayerHud : public AHUD
{
	GENERATED_BODY()

		UPROPERTY()
		UFont* HUDFont;
	
	virtual void DrawHUD() override;

};
