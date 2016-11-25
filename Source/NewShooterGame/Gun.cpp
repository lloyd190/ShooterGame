// Fill out your copyright notice in the Description page of Project Settings.

#include "NewShooterGame.h"
#include "Gun.h"


// Sets default values
AGun::AGun(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

UStaticMeshComponent * AGun::GetMesh()
{
	return Mesh;
}
USkeletalMeshComponent* AGun::getPawnSkeletalComp(FString ComponentName)
{
/*	TArray<UActorComponent*> Components;
	USkeletalMeshComponent* ArmMesh = NULL;

	if (OwningPawn)
		OwningPawn->GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		ArmMesh = Cast<USkeletalMeshComponent>(Comp);
		if (ArmMesh)
		{
			if (ArmMesh->GetName() == ComponentName)
				return ArmMesh;
		}
	}
	 */
	return NULL;
}
void AGun::AttachWeaponToPawn(APawn* WeaponOwner, FString SkeletalCompName)
{
/*	OwningPawn = WeaponOwner;
	SetOwner(WeaponOwner);

	USkeletalMeshComponent* ArmMesh = getPawnSkeletalComp(SkeletalCompName);
	if (ArmMesh) {
		AttachRootComponentTo(ArmMesh, FName(*SkeletalCompName));
	}	*/
}

// Called every frame
void AGun::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

