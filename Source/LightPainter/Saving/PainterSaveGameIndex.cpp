 // Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGameIndex.h"
#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"

const FString UPainterSaveGameIndex::SLOT_NAME = "PaintingIndex";

UPainterSaveGameIndex * UPainterSaveGameIndex::Load()
{
	UPainterSaveGameIndex* Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SLOT_NAME, 0));
	if (Index == false)
	{
		Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		Index->Save();
	}
	return Index;
}

bool UPainterSaveGameIndex::Save()
{
	bool success = UGameplayStatics::SaveGameToSlot(this, SLOT_NAME, 0);
	return success;
}

void UPainterSaveGameIndex::AddSaveGame(UPainterSaveGame* SaveGame)
{
	SlotNames.Add(SaveGame->GetSlotName());
}

TArray<FString> UPainterSaveGameIndex::GetSlotNames() const
{
	return SlotNames;
}
