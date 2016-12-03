// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gun.h"
#include <iostream>
#include "GameFramework/Character.h"
#include "FirstPlayer.generated.h"

UCLASS()
class NEWSHOOTERGAME_API AFirstPlayer : public ACharacter
{																							  
	GENERATED_BODY()

private:
	bool SinglePersonCamera = false;
	FVector2D MouseInput;
	bool CameraOffline = false;
	bool IsDead = false;
	UPROPERTY(EditAnywhere, category = "Health")
		float CurrentHealth;
	UPROPERTY(EditAnywhere, category = "Health")
		float InitialHealth;	

public:
	UFUNCTION(BlueprintPure, category = "HUD")
		bool getShowCameras();
	
	UPROPERTY(EditAnywhere, Category = "Gun")
		TSubclassOf<AGun> WeaponClass;
	// Gets the starting amount of health
	void EquipWeapon();
	UFUNCTION(BlueprintPure, category = "Health")
		float GetInitialHealth();

	UFUNCTION(BlueprintPure, category = "Dead")
		bool GetIsDead();
	//gets the current health
	UFUNCTION(BlueprintPure, category = "Health")
		float getCurrentHealth();
	//changes the health, can be both negative and positive
	UFUNCTION(BlueprintCallable, category = "Health")
		void UpdateCurrentHealth(float val);
	// Sets default values for this character's properties
	AFirstPlayer(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float val);
	void MoveRight(float val);
	void PitchCamera(float val);
	void YawCamera(float val);
	void JumpEnd();
	void Jump();
	void CameraMovement();
	void CameraSwitch();
	void ShowCameras();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, category = "HUD")
		void HUDUpdateHp();

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check")
		bool IsInAir = false;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;
	USpringArmComponent* FirstPersonCameraSpringArm;
	UCameraComponent* FirstPersonCamera;
};
