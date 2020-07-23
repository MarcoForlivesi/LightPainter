// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"

#include "PaintingGridCard.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (PaintingGrid == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PaintingGrid is null"));
		return;
	}
	
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (NewWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPaintingGridCard Widget is null"));
		return;
	}

	NewWidget->SetPaintingName(PaintingName);

	USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex));
	if (CardContainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Painting Grid child doesn't contains a SizeBox"));
		return;
	}

	CardContainer->AddChild(NewWidget);
}
