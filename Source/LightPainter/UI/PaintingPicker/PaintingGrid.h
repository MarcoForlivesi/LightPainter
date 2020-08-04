// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Layout/Margin.h"

#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString PaintingName);

	void ClearPaintings();
	void ClearPaginationDots();

	int32 GetNumberOfSlots() const;

	void AddPaginationDot(bool Active);
protected:
	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	class UUniformGridPanel* PaintingGrid;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	class UHorizontalBox* PaginationDotsContainer;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPaintingGridCard> GridCardClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPaginationDot> PaginationDotClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationDotPadding = 8.0f;
};
