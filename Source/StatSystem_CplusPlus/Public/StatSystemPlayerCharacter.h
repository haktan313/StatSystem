

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components_DamageSystem.h"
#include "Interface_Stats.h"
#include "Structures.h"
#include "StatSystemPlayerCharacter.generated.h"

UCLASS()
class STATSYSTEM_CPLUSPLUS_API AStatSystemPlayerCharacter : public ACharacter, public IInterface_Stats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* moveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* lookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* jumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* damageSelfAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* healSelfAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UComponents_DamageSystem* DamageSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> StatsWidgetClass;


public:

	AStatSystemPlayerCharacter();

protected:

	virtual void BeginPlay() override;

	virtual float CurrentHealth_Implementation() const override;

	virtual float MaxHealth_Implementation() const override;

	virtual void TakeDamage_Implementation(FS_DamageInfo aboutDamage) override;

	virtual float CurrentMana_Implementation() const override;

	virtual float MaxMana_Implementation() const override;

	virtual void DecreaseMana_Implementation(float amount) override;

	virtual void HealFunction_Implementation(float amount) override;

	void Movement(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void damageSelf();

	void Heal();

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void DeathResponse(E_DeathType deathType);

	UFUNCTION()
	void DamageResponse(E_DamageType damageType);

};
