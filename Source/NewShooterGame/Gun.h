// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class NEWSHOOTERGAME_API AGun : public AActor
{
	GENERATED_BODY()

private:
	APawn* OwningPawn;

protected:
	
	
public:	
	USkeletalMeshComponent* getPawnSkeletalComp(FString ComponentName);
	void AttachWeaponToPawn(APawn* WeaponOwner, FString SkeletalCompName);
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	// Sets default values for this actor's properties
	AGun(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetMesh(UStaticMeshComponent weaponMesh);
	UStaticMeshComponent* GetMesh();
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
