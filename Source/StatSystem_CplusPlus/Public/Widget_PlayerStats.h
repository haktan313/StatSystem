

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PlayerStats.generated.h"


UCLASS()
class STATSYSTEM_CPLUSPLUS_API UWidget_PlayerStats : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	float HealthPrecent() const;
	UFUNCTION(BlueprintCallable)
	float ManaPrecent() const;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	UObject* DamageSystemObject;
};
