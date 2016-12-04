// Fill out your copyright notice in the Description page of Project Settings.

#include "NewShooterGame.h"
#include "PlayerControlledCameraDrones.h"


// Sets default values
APlayerControlledCameraDrones::APlayerControlledCameraDrones(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	this->GetMesh()->SetSimulatePhysics(false);
	this->GetMesh()->WakeRigidBody();
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	CameraRecord = ObjectInitializer.CreateDefaultSubobject<USceneCaptureComponent2D>(this, TEXT("CameraRecord"));

	CameraRecord->AttachTo(GetRootComponent());
	Camera->AttachTo(GetRootComponent());
	Camera->SetWorldLocation(GetActorLocation());
}

// Called when the game starts or when spawned
void APlayerControlledCameraDrones::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerControlledCameraDrones::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AddMovementInput(GetActorUpVector(), 5000000000000.0f);
}

// Called to bind functionality to input
void APlayerControlledCameraDrones::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

