// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

struct FCollisionQueryParms;
class UBoxComponent;
class USkeletalMeshComponent;

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 TotalAmmo = 30;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 MaxAmmo = 10;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	float TimeBetweenShots = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float GunRecoil = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float CharacterRecoil = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	int32 Shots = 1;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float WeaponRange = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float ShotInaccuracy = 0;
};

UCLASS()
class PLAGUESPLATTERSOLO_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:

	void Fire(FVector Start, FVector ForwardVector, FVector RightVector, FVector UpVector, FCollisionQueryParams param);

	void InstantFire
	(int32 Shots, float ShotInaccuracy, int32 Damage, float Range,
	FVector Start, FVector ForwardVector, FVector RightVector, FVector UpVector, FCollisionQueryParams param);

	UFUNCTION()
	void SetShoot();

	UFUNCTION()
	void Reload();

	bool CanShoot();

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponData Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY()
	bool bCanShoot = true;

	FTimerHandle TimeManager;

	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
