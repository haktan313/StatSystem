


#include "Components_DamageSystem.h"


UComponents_DamageSystem::UComponents_DamageSystem()
{

	PrimaryComponentTick.bCanEverTick = true;

	bIsDead = false;
	currentHealth = 100;
	maxHealth = 100;

}

void UComponents_DamageSystem::TakeDamage(FS_DamageInfo aboutDamage)
{
	currentHealth -= aboutDamage.AmountOfDamage;


	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Taking Damage: %f"), aboutDamage.AmountOfDamage));

	if (currentHealth <= 0)
	{
		bIsDead = true;
		currentHealth = 0;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Broadcasting Death"));
		OnDeath.Broadcast(aboutDamage.DeathType);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Broadcasting Damage Response"));
		OnDamageResponse.Broadcast(aboutDamage.DamageType);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Current Health: %f"), currentHealth));
}

float UComponents_DamageSystem::Heal(float amount)
{
	currentHealth += amount;
	currentHealth = FMath::Clamp(currentHealth, 0.f, maxHealth);
	return currentHealth;
}

void UComponents_DamageSystem::DecreaseMana(float amount)
{
	currentMana -= amount;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Decreasing Mana: %f"), amount));
	
	if (currentMana <= 0)
	{
		currentMana = 0;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No Mana"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Current Mana: %f"), currentMana));
}

