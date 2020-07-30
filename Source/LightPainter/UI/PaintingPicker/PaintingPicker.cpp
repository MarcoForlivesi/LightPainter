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

	RefreshSlots();
}

void APaintingPicker::ToggleDeleteMode()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (PaintingGridWidget == nullptr)
	{
		return;
	}

	PaintingGridWidget->ClearPaintings();
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	RefreshSlots();

	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget == nullptr)
	{
		return;
	}

	ActionBarWidget->SetParentPicker(this);
}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (PaintingGridWidget == nullptr)
	{
		return;
	}

	PaintingGridWidget->ClearPaintings();

	int32 Index = 0;
	TArray<FString> SlotNameList = UPainterSaveGameIndex::Load()->GetSlotNames();
	for (FString SlotName : SlotNameList)
	{
		PaintingGridWidget->AddPainting(Index, SlotName);
		++Index;
	}
}
