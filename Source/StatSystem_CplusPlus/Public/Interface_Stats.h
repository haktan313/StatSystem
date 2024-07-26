
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structures.h"
#include "Interface_Stats.generated.h"


UINTERFACE(MinimalAPI)
class UInterface_Stats : public UInterface
{
	GENERATED_BODY()
};


class STATSYSTEM_CPLUSPLUS_API IInterface_Stats
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	void TakeDamage(FS_DamageInfo aboutDamage);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float CurrentHealth() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float MaxHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	void DecreaseMana(float amount);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float CurrentMana() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float MaxMana() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	void HealFunction(float amount);

};
