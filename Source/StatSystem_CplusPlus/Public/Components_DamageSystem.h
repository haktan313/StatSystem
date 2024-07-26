

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums.h"
#include "Structures.h"
#include "Components_DamageSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, E_DeathType, DeathType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageResponse, E_DamageType, DamageType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATSYSTEM_CPLUSPLUS_API UComponents_DamageSystem : public UActorComponent
{
	GENERATED_BODY()

public:	

	UComponents_DamageSystem();

public:	

	void TakeDamage(FS_DamageInfo aboutDamage);

	float Heal(float amount);

	void DecreaseMana(float amount);

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnDamageResponse OnDamageResponse;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float currentMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float maxMana;

	bool bIsDead;
		
};
