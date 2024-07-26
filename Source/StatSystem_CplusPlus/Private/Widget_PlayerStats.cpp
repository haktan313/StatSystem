


#include "Widget_PlayerStats.h"
#include "Interface_Stats.h"

void UWidget_PlayerStats::NativeConstruct()
{
	Super::NativeConstruct();
}

float UWidget_PlayerStats::HealthPrecent() const
{
    if (DamageSystemObject && DamageSystemObject->GetClass()->ImplementsInterface(UInterface_Stats::StaticClass()))
    {
        float MaxHealth = IInterface_Stats::Execute_MaxHealth(DamageSystemObject);
        float CurrentHealth = IInterface_Stats::Execute_CurrentHealth(DamageSystemObject);
        return (CurrentHealth / MaxHealth);
    }
    return 0.0f;
}

float UWidget_PlayerStats::ManaPrecent() const
{
    if (DamageSystemObject && DamageSystemObject->GetClass()->ImplementsInterface(UInterface_Stats::StaticClass()))
    {
        float maxMana = IInterface_Stats::Execute_MaxMana(DamageSystemObject);
        float currentMana = IInterface_Stats::Execute_CurrentMana(DamageSystemObject);
        return (currentMana / maxMana);
    }
    return 0.0f;
}
