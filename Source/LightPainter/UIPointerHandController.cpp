// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetInteractionComponent.h"

#include "UIPointerHandController.h"

AUIPointerHandController::AUIPointerHandController()
{
	Pointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Pointer"));
	Pointer->SetupAttachment(GetRootComponent());
}