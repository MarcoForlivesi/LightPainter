// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionBar.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UActionBar : public UUserWidget
{
	GENERATED_BODY()
public:
	bool Initialize() override;

	void SetParentPicker(class APaintingPicker* NewParentPicker);
protected:
	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	class UButton* AddButton;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	class UButton* DeleteButton;
private:
	UFUNCTION()
	void AddButtonClicked();
	UFUNCTION()
	void DeleteButtonClicked();

	UPROPERTY()
	APaintingPicker* ParentPicker;
};
