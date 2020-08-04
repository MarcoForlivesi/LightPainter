// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"

#include "PaintingGridCard.h"
#include "PaginationDot.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"


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
		UE_LOG(LogTemp, Warning, TEXT("GridCardClass Widget is null"));
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

void UPaintingGrid::ClearPaintings()
{
	for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); ++i)
	{
		USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(i));

		if (CardContainer == nullptr)
		{
			continue;
		}

		CardContainer->ClearChildren();
	}
}

void UPaintingGrid::ClearPaginationDots()
{
	if (PaginationDotsContainer == nullptr)
	{
		return;
	}

	PaginationDotsContainer->ClearChildren();
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid->GetChildrenCount();
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	UPaginationDot* DotWidget = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (DotWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PaginationDotClass Widget is null"));
		return;
	}
	DotWidget->SetActive(Active);

	UHorizontalBoxSlot* DotSlot = PaginationDotsContainer->AddChildToHorizontalBox(DotWidget);
	DotSlot->SetPadding(FMargin(PaginationDotPadding));
}
