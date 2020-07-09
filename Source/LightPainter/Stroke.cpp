// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/SceneComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "Engine/World.h"

AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);

	JointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("JointMeshes"));
	JointMeshes->SetupAttachment(Root);
}

void AStroke::Update(FVector CursorLocation)
{
	ControlPoints.Add(CursorLocation);

	if (PreviousCursorLocation.IsNearlyZero())
	{
		PreviousCursorLocation = CursorLocation;
		FTransform NewJointTransform = GetNextJointTransform(CursorLocation);
		JointMeshes->AddInstance(NewJointTransform);

		return;
	}

	FTransform NewStrokeTransform = GetNextSegmentTransform(CursorLocation);
	FTransform NewJointTransform = GetNextJointTransform(CursorLocation);

	StrokeMeshes->AddInstance(NewStrokeTransform);
	JointMeshes->AddInstance(NewJointTransform);

	PreviousCursorLocation = CursorLocation;
}

FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState StrokeState;
	StrokeState.Class = GetClass();
	StrokeState.ControlPoints = ControlPoints;

	return StrokeState;
}

AStroke* AStroke::SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState & StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.Class);

	for (FVector ControlPoint : StrokeState.ControlPoints)
	{
		Stroke->Update(ControlPoint);
	}

	return Stroke;
}

FTransform AStroke::GetNextSegmentTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));
	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));

	return SegmentTransform;
}

FTransform AStroke::GetNextJointTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));

	return SegmentTransform;
}

FVector AStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{
	FVector LocalCursorLocation = GetTransform().InverseTransformPosition(CurrentLocation);
	return LocalCursorLocation;
}

FQuat AStroke::GetNextSegmentRotation(FVector CurrentLocation) const
{
	FVector Segment = CurrentLocation - PreviousCursorLocation;
	FVector SegmentNormal = Segment.GetSafeNormal();
	
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentNormal);
}

FVector AStroke::GetNextSegmentScale(FVector CurrentLocation) const
{
	FVector Segment = CurrentLocation - PreviousCursorLocation;
	return FVector(Segment.Size(), 1, 1);
}

