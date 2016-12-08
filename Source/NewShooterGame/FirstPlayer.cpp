// Fill out your copyright notice in the Description page of Project Settings.

#include "NewShooterGame.h"
#include "FirstPlayer.h"


bool AFirstPlayer::getShowCameras()
{
	return CameraOffline;
}

void AFirstPlayer::EquipWeapon()
{

/*	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoCollisionFail = true;
	FRotator setRotation = GetActorRotation();
	AGun* SpawnedGun = GetWorld()->SpawnActor<AGun>(WeaponClass, this->GetActorLocation(), setRotation, SpawnInfo);
	if (SpawnedGun) {
		SpawnedGun->AttachWeaponToPawn(this, "Gun");
	} */
}

float AFirstPlayer::GetInitialHealth()
{
	return InitialHealth;
}

bool AFirstPlayer::GetIsDead()
{
	return IsDead;
}



float AFirstPlayer::getCurrentHealth()
{
	return CurrentHealth;
}

void AFirstPlayer::UpdateCurrentHealth(float val)
{
	if (CurrentHealth+val <= 0.0f) {
		IsDead = true;
		CurrentHealth = 0.0f;
		HUDUpdateHp();
		OurCameraSpringArm->bUsePawnControlRotation = true;
	}
	else if(CurrentHealth+val > 0.0f) {
		IsDead = false;
		CurrentHealth += val;
		HUDUpdateHp();
		
	}
	GetMesh()->SetSimulatePhysics(IsDead);
	GetCapsuleComponent()->SetSimulatePhysics(IsDead);
	
}

// Sets default values
AFirstPlayer::AFirstPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{	

 	// Basic camera
	PrimaryActorTick.bCanEverTick = true;
	OurCameraSpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this,TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(GetRootComponent());
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.50f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this,TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//FirstPerson Camera
	FirstPersonCameraSpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("FirstPersonCameraSpringArm"));
	FirstPersonCameraSpringArm->SetupAttachment(GetRootComponent());
	FirstPersonCameraSpringArm->SetRelativeLocationAndRotation(FVector(1.0f, 0.0f, 55.0f), FRotator(0.0f, 0.0f, 0.0f));
	FirstPersonCameraSpringArm->TargetArmLength = -50.f;
	FirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(FirstPersonCameraSpringArm, USpringArmComponent::SocketName);

	InitialHealth = 100.f;
	CurrentHealth = InitialHealth;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	EquipWeapon();

}

// Called when the game starts or when spawned
void AFirstPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AFirstPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraMovement();
}

// Called to bind functionality to input
void AFirstPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
		Super::SetupPlayerInputComponent(InputComponent);

		InputComponent->BindAxis("MoveForward", this, &AFirstPlayer::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AFirstPlayer::MoveRight);
		InputComponent->BindAxis("CameraPitch", this, &AFirstPlayer::PitchCamera);
		InputComponent->BindAxis("CameraYaw", this, &AFirstPlayer::YawCamera);
		InputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPlayer::Jump);
		InputComponent->BindAction("Jump", IE_Released, this, &AFirstPlayer::JumpEnd);
		InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AFirstPlayer::CameraSwitch);
		InputComponent->BindAction("TurnOnCameras", IE_Pressed, this, &AFirstPlayer::ShowCameras);
}

void AFirstPlayer::MoveForward(float val)
{ 

	  if ((Controller != NULL) && (val != 0.0f) && GetMovementComponent()->IsMovingOnGround() && !IsDead)
	{
		AddMovementInput(GetActorForwardVector(), val);
	}
}

void AFirstPlayer::MoveRight(float val)
{
	if ((Controller != NULL) && (val != 0.0f) && GetMovementComponent()->IsMovingOnGround() && !IsDead) {
		AddMovementInput(GetActorRightVector(), val);
	}
}

void AFirstPlayer::PitchCamera(float val)
{
	MouseInput.Y = val;

}

void AFirstPlayer::YawCamera(float val)
{
	MouseInput.X = val;
}

void AFirstPlayer::JumpEnd()
{
	IsInAir = false;
}

void AFirstPlayer::Jump()
{
	if (GetMovementComponent()->IsMovingOnGround() && !IsDead) {
		LaunchCharacter(FVector(0, 0, 1) * 500, false, false);
		IsInAir = true;

			UpdateCurrentHealth(-50.0f);
		
	}
}

void AFirstPlayer::CameraMovement()
{
	if (!IsDead) {
		FRotator newYaw = GetActorRotation();
		newYaw.Yaw += MouseInput.X * GetWorld()->DeltaTimeSeconds * 300;
		SetActorRotation(newYaw);

		if (!SinglePersonCamera) {
			FRotator newPitch = OurCameraSpringArm->GetComponentRotation();
			newPitch.Pitch = FMath::Clamp(newPitch.Pitch + MouseInput.Y * GetWorld()->DeltaTimeSeconds * 300, -80.f, 0.f);
			OurCameraSpringArm->SetWorldRotation(newPitch);
		}
		else {
			FRotator newPitch = FirstPersonCamera->GetComponentRotation();
			newPitch.Pitch = FMath::Clamp(newPitch.Pitch + MouseInput.Y * GetWorld()->DeltaTimeSeconds * 300, -80.f, 80.f);
			FirstPersonCamera->SetWorldRotation(newPitch);
		}
	}
}

void AFirstPlayer::CameraSwitch()
{
	if (!IsDead) {
		if (!SinglePersonCamera) {
			OurCamera->Deactivate();
			FirstPersonCamera->Activate();
			SinglePersonCamera = true;
		}
		else {
			FirstPersonCamera->Deactivate();
			OurCamera->Activate();
			SinglePersonCamera = false;
		}
	}
}
/*ACHTUNG FOR TESTING PURPOSES HAS TO BE REMOVED LATER AND SET IN THE DRONE CLASS*/
void AFirstPlayer::ShowCameras()
{
	if (CameraOffline) {
		CameraOffline = false;
	}
	else {
		CameraOffline = true;
	}
}


