// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"

#include "PaintingGrid.h"
#include "../../Saving/PainterSaveGameIndex.h"
#include "../../Saving/PainterSaveGame.h"
#include "ActionBar.h"

#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::Create();

	Refresh();
}

void APaintingPicker::ToggleDeleteMode()
{
	if (GetPaintingGrid() == nullptr)
	{
		return;
	}

	GetPaintingGrid()->ClearPaintings();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, GetNumberOfPages() - 1);

	Refresh();
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();
	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget == nullptr)
	{
		return;
	}

	ActionBarWidget->SetParentPicker(this);
	Refresh();
}

void APaintingPicker::Refresh()
{
	RefreshSlots();
	RefreshDots();
}

void APaintingPicker::RefreshSlots()
{
	if (GetPaintingGrid() == nullptr)
	{
		return;
	}

	GetPaintingGrid()->ClearPaintings();

	int32 StartOffset = CurrentPage * GetPaintingGrid()->GetNumberOfSlots();
	int32 Index = 0;
	TArray<FString> SlotNameList = UPainterSaveGameIndex::Load()->GetSlotNames();
	for (int32 i = 0; i < GetPaintingGrid()->GetNumberOfSlots() && StartOffset + i < SlotNameList.Num(); ++i)
	{
		FString SlotName = SlotNameList[StartOffset + i];
		GetPaintingGrid()->AddPainting(Index, SlotName);
		++Index;
	}
}

void APaintingPicker::RefreshDots()
{
	if (GetPaintingGrid() == nullptr)
	{
		return;
	}

	GetPaintingGrid()->ClearPaginationDots();

	for (int32 i = 0; i < GetNumberOfPages(); i++)
	{
		GetPaintingGrid()->AddPaginationDot(CurrentPage == i);
	}
}

int32 APaintingPicker::GetNumberOfPages() const
{
	if (GetPaintingGrid() == nullptr)
	{
		return 0;
	}

	int32 TotalNumberOfSlots = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotPerPage = GetPaintingGrid()->GetNumberOfSlots();
	return FMath::CeilToInt((float) TotalNumberOfSlots / SlotPerPage);
}

UPaintingGrid* APaintingPicker::GetPaintingGrid() const
{
	return Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
}
