#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class E_DamageType : uint8
{
    Melee UMETA(DisplayName = "Melee"),
    Ranged UMETA(DisplayName = "Ranged"),
    Explosion UMETA(DisplayName = "Explosion")
};

UENUM(BlueprintType)
enum class E_DeathType : uint8
{
    Melee UMETA(DisplayName = "Melee"),
    Ranged UMETA(DisplayName = "Ranged"),
    Explosion UMETA(DisplayName = "Explosion")
};