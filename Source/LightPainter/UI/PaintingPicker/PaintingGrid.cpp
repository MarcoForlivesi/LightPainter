// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"

#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting()
{
	if (PaintingGrid == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PaintingGrid is null"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Grid Name: %s"), *PaintingGrid->GetName());

	
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
	if (NewWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid Card Widget is null"));
		return;
	}

	USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(0));
	if (CardContainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Painting Grid child doesn't contains a SizeBox"));
		return;
	}

	CardContainer->AddChild(NewWidget);

	/*for (int i = 0; i < GetchildCount(); ++i)
	{

	}*/
}
