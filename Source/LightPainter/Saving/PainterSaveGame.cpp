// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"
#include "../Stroke.h"

#include "EngineUtils.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/Guid.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();

	return NewSaveGame;
}


bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

FString UPainterSaveGame::GetState() const
{
	return State;
}

void UPainterSaveGame::SetState(FString NewState)
{
	State = NewState;
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();

	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	ClearWorld(World);

	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}

FString UPainterSaveGame::GetSlotName() const
{
	return SlotName;
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}
