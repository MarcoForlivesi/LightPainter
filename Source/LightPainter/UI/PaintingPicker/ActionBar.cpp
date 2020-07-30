// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBar.h"

#include "PaintingPicker.h"

#include "Components/Button.h"

bool UActionBar::Initialize()
{
	if (Super::Initialize() == false)
	{
		return false;
	}

	if (AddButton == nullptr)
	{
		return false;
	}

	AddButton->OnClicked.AddDynamic(this, &UActionBar::AddButtonClicked);
	
	if (DeleteButton == nullptr)
	{
		return false;
	}
	
	DeleteButton->OnClicked.AddDynamic(this, &UActionBar::DeleteButtonClicked);

	return false;
}

void UActionBar::SetParentPicker(APaintingPicker* NewParentPicker)
{
	ParentPicker = NewParentPicker;
}

void UActionBar::AddButtonClicked()
{
	if (ParentPicker == nullptr)
	{
		return;
	}

	ParentPicker->AddPainting();
}

void UActionBar::DeleteButtonClicked()
{
	if (ParentPicker == nullptr)
	{
		return;
	}

	ParentPicker->ToggleDeleteMode();
}
