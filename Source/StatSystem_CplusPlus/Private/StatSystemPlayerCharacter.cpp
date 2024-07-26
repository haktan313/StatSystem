


#include "StatSystemPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetComponent.h"
#include "Widget_PlayerStats.h"
#include "Blueprint/UserWidget.h"


AStatSystemPlayerCharacter::AStatSystemPlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	DamageSystemComponent = CreateDefaultSubobject<UComponents_DamageSystem>(TEXT("DamageSystemComponent"));

	DamageSystemComponent->OnDeath.AddDynamic(this, &AStatSystemPlayerCharacter::DeathResponse);
	DamageSystemComponent->OnDamageResponse.AddDynamic(this, &AStatSystemPlayerCharacter::DamageResponse);

}

void AStatSystemPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	if (StatsWidgetClass)
	{
		UWidget_PlayerStats* widgetStats = CreateWidget<UWidget_PlayerStats>(GetWorld(), StatsWidgetClass);
		if (widgetStats)
		{
			widgetStats->AddToViewport();
			widgetStats->DamageSystemObject = this;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Character Begin Play"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("For Damage Yourself Press 'R'"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("For Heal Yourself Press 'T'"));
}



float AStatSystemPlayerCharacter::CurrentHealth_Implementation() const
{
	float currentHealth = DamageSystemComponent->currentHealth;
	return currentHealth;
}

float AStatSystemPlayerCharacter::MaxHealth_Implementation() const
{
	float maxHealth = DamageSystemComponent->maxHealth;
	return maxHealth;
}

void AStatSystemPlayerCharacter::TakeDamage_Implementation(FS_DamageInfo aboutDamage)
{
	DamageSystemComponent->TakeDamage(aboutDamage);
}

float AStatSystemPlayerCharacter::CurrentMana_Implementation() const
{
	float currentMana = DamageSystemComponent->currentMana;
	return currentMana;
}

float AStatSystemPlayerCharacter::MaxMana_Implementation() const
{
	float maxMana = DamageSystemComponent->maxMana;
	return maxMana;
}

void AStatSystemPlayerCharacter::DecreaseMana_Implementation(float amount)
{
	DamageSystemComponent->DecreaseMana(amount);
}

void AStatSystemPlayerCharacter::HealFunction_Implementation(float amount)
{
	DamageSystemComponent->Heal(amount);
}



void AStatSystemPlayerCharacter::Movement(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);

	const FVector forwardDirction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDirction, inputValue.Y);
	AddMovementInput(rightDirection, inputValue.X);
}

void AStatSystemPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(inputValue.Y);
	AddControllerYawInput(inputValue.X);
}



void AStatSystemPlayerCharacter::damageSelf()
{
	FS_DamageInfo DamageInfo;
	DamageInfo.AmountOfDamage = 10.0f;
	DamageInfo.DamageType = E_DamageType::Melee; 
	DamageInfo.DeathType = E_DeathType::Melee; 

	if (DamageSystemComponent)
	{
		IInterface_Stats::Execute_TakeDamage(this, DamageInfo);
	}
}

void AStatSystemPlayerCharacter::Heal()
{
	if(DamageSystemComponent->currentMana >= 50.f)
	{
		IInterface_Stats::Execute_HealFunction(this,25);
		IInterface_Stats::Execute_DecreaseMana(this, 50.f);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not Enough Mana"));
	}
}



void AStatSystemPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AStatSystemPlayerCharacter::Movement);
	enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AStatSystemPlayerCharacter::Look);

	enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &AStatSystemPlayerCharacter::Jump);
	enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &AStatSystemPlayerCharacter::StopJumping);

	enhancedInputComponent->BindAction(damageSelfAction, ETriggerEvent::Started, this, &AStatSystemPlayerCharacter::damageSelf);
	enhancedInputComponent->BindAction(healSelfAction, ETriggerEvent::Started, this, &AStatSystemPlayerCharacter::Heal);
}



void AStatSystemPlayerCharacter::DeathResponse(E_DeathType deathType)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Character Died"));
}

void AStatSystemPlayerCharacter::DamageResponse(E_DamageType damageType)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Character Damaged"));
}

