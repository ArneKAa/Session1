// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(CollisionComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::SetShoot()
{
	bCanShoot = true;
}

void ABaseWeapon::Reload()
{

}

bool ABaseWeapon::CanShoot()
{
	if (bCanShoot)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void ABaseWeapon::InstantFire(int32 Shots, float ShotInaccuracy, int32 Damage, float Range,
	FVector Start, FVector ForwardVector, FVector RightVector, FVector UpVector, FCollisionQueryParams param)
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
	for (int i = 0; i < Shots; i++)
	{
		FHitResult OutHit;
		FVector ShotVector = RightVector * FMath::RandRange(-ShotInaccuracy, ShotInaccuracy) +	
		UpVector * FMath::RandRange(-ShotInaccuracy, ShotInaccuracy) + ForwardVector;

		FVector End = ((ShotVector) * Range) + Start;

		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_PhysicsBody, param))
		{
			DrawDebugLine(GetWorld(), Start, OutHit.ImpactPoint, FColor::Red, true);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *OutHit.ToString());
			DrawDebugPoint(GetWorld(), OutHit.ImpactPoint, 20, FColor::Green, true);
		}
	}
}

void ABaseWeapon::Fire(FVector Start, FVector ForwardVector, FVector RightVector, FVector UpVector, FCollisionQueryParams param)
{
	if (bCanShoot)
	{
		bCanShoot = false;
		GetWorldTimerManager().SetTimer(TimeManager, this, &ABaseWeapon::SetShoot, Weapon.TimeBetweenShots, false);
		InstantFire(Weapon.Shots, Weapon.ShotInaccuracy, 1, Weapon.WeaponRange, Start, ForwardVector, RightVector, UpVector, param);
	}
}




