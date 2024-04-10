#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"   
#include "PDCharacter.generated.h"

class ABaseWeapon;
class UInputMappingContext;
class UCameraComponent;
struct FInputActionValue;
class UInputComponent;
class UInputAction;
class USphereComponent;

UCLASS()
class PLAGUESPLATTERSOLO_API APDCharacter : public ACharacter  
{
    GENERATED_BODY()

public:
    APDCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /*
     * Components
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCameraComponent* FPVCameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMeshComponent* FPVMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent* SphereComponent;

    /*
     * Input Mapping Context and Actions
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* IMC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* FireAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* ReloadAction;

    void Reload(const FInputActionValue& Value);

    void Fire(const FInputActionValue& Value);

    void Move(const FInputActionValue& Value);

    void LookAround(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Sensitivity")
    float MouseSensitivity = 0.5f;

    /*
     * Weapon
     */
    UFUNCTION(BlueprintCallable, Category = "Overlap")
    void AttachWeapon(ABaseWeapon* AttachedWeapon);

    UFUNCTION(BlueprintCallable, Category = "Overlap")
    void OnPickup
    (UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult);


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    bool bHasWeapon = false;

    UPROPERTY(BlueprintReadOnly)
    int AmmoCount = 30;

    UPROPERTY(BlueprintReadOnly)
    int TotalAmmoCount = 90;

    UPROPERTY(BlueprintReadOnly)
    ABaseWeapon* Weapon;

    USkeletalMeshComponent* GetMeshFPV() const;

    UCameraComponent* GetFPVCameraComponent() const;


protected:
    virtual void BeginPlay() override;
};