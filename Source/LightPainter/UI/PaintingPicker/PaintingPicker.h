// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintingPicker.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintingPicker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintingPicker();

	void AddPainting();
	void ToggleDeleteMode();

	void UpdateCurrentPage(int32 Offset);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void Refresh();
	void RefreshSlots();
	void RefreshDots();
	int32 GetNumberOfPages() const;
	class UPaintingGrid* GetPaintingGrid() const;
	
	// Components
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* PaintingGrid;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* ActionBar;

	// State
	UPROPERTY(EditAnywhere)
	int32 CurrentPage = 0;
};
