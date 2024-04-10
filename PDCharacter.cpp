#include "Character/PDCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APDCharacter::APDCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    FPVCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    FPVCameraComponent->SetupAttachment(GetCapsuleComponent());
    FPVCameraComponent->bUsePawnControlRotation = true;

    FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharMesh"));
    FPVMesh->SetupAttachment(FPVCameraComponent);
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(RootComponent);
    Weapon = nullptr;

}

void APDCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (SphereComponent)
    {
        SphereComponent->IgnoreActorWhenMoving(this, true);
        SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPickup);
    }

    // Adding the Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(IMC, 0);
        }
    }
}

void APDCharacter::Move(const FInputActionValue& Value)
{

    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void APDCharacter::LookAround(const FInputActionValue& Value)
{
    FVector2D LookAroundVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAroundVector.X * MouseSensitivity);
        AddControllerPitchInput(LookAroundVector.Y * MouseSensitivity);
    }
}

void APDCharacter::Reload(const FInputActionValue& Value)
{
    if (Weapon)
    {
        Weapon->Reload();
    }
}

void APDCharacter::Fire(const FInputActionValue& Value)
{
    if (Weapon) {

        
        if (Weapon->CanShoot())
        {
            float PushBack = Weapon->Weapon.CharacterRecoil;
            GetCharacterMovement()->Velocity += GetFPVCameraComponent()->GetForwardVector() * (-PushBack);

            //GetRootComponent()->AddForce(GetActorForwardVector() * 200.0f);
            //SM->AddForce(GetFPVCameraComponent()->GetForwardVector() * (-1000000) * , FName(TEXT("Root")));
            UE_LOG(LogTemp, Display, TEXT("Adding force"));
        }

        FVector Start = GetFPVCameraComponent()->GetComponentLocation();
        FVector ForwardVector = GetFPVCameraComponent()->GetForwardVector();
        FVector RightVector = GetFPVCameraComponent()->GetRightVector();
        FVector UpVector = GetFPVCameraComponent()->GetUpVector();

        FCollisionQueryParams param;
        param.AddIgnoredActor(this);

        Weapon->Fire(Start, ForwardVector, RightVector, UpVector, param);
    }

}

void APDCharacter::AttachWeapon(ABaseWeapon* AttachedWeapon)
{

    if (AttachedWeapon == nullptr || bHasWeapon)
    {
        return;
    }

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

    AttachedWeapon->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("WeaponSocket")));

    bHasWeapon = true;
}

void APDCharacter::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ABaseWeapon* PickupWeapon = Cast<ABaseWeapon>(OtherActor))
    {       
        Weapon = PickupWeapon;
        AttachWeapon(Weapon);
    }
}

USkeletalMeshComponent* APDCharacter::GetMeshFPV() const
{
    return FPVMesh;
}

UCameraComponent* APDCharacter::GetFPVCameraComponent() const
{
    return FPVCameraComponent;
}



void APDCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void APDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APDCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APDCharacter::LookAround);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APDCharacter::Fire);
        EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &APDCharacter::Reload);
    }

}