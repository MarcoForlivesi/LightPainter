// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
private:
	void RightTriggerPressed();
	void RightTriggerReleased();

	void PaginateRightAxisInput(float AxisValue);
	void UpdateCurentPage(int32 Offset);

	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHandControllerBase> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHandControllerBase> LeftHandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickThreshold = 0.9f;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	class AHandControllerBase* RightHandController;
	UPROPERTY()
	class AHandControllerBase* LeftHandController;

	// State
	int32 LastPaginationOffset = 0;
};
