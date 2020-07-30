// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "HandControllerBase.h"

#include "Saving/PainterSaveGame.h"

#include "PaintingGameMode.h"

#include "Camera\CameraComponent.h"

#include "Components\SceneComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if (RightHandControllerClass != nullptr)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetHand(EControllerHand::Right);
		RightHandController->SetOwner(this);
	}

	if (LeftHandControllerClass != nullptr)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		LeftHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandController->SetHand(EControllerHand::Left);
		LeftHandController->SetOwner(this);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Pressed, this, &AVRPawn::Save);
}

void AVRPawn::RightTriggerPressed()
{
	if (RightHandController)
	{
		RightHandController->TriggerPressed();
	}
}

void AVRPawn::RightTriggerReleased()
{
	if (RightHandController)
	{
		RightHandController->TriggerReleased();
	}
}

void AVRPawn::Save()
{
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	APaintingGameMode* PaintingGameMode = Cast<APaintingGameMode>(GameMode);
	if (PaintingGameMode == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s is not a PaintingGameMode"), *GameMode->GetName());
		return;
	}
	PaintingGameMode->Save();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
