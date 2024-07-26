#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Structures.generated.h"

USTRUCT(BlueprintType)
struct FS_DamageInfo
{
    GENERATED_BODY()

    FS_DamageInfo()
        : AmountOfDamage(0), DamageType(E_DamageType::Melee), DeathType(E_DeathType::Melee)
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmountOfDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    E_DamageType DamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    E_DeathType DeathType;
};