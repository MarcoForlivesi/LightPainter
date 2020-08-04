// Fill out your copyright notice in the Description page of Project Settings.


#include "PaginationDot.h"
#include "Components/Image.h"

void UPaginationDot::SetActive(bool Active)
{
	DotImage->SetOpacity(Active ? 1.0f : DisabledOpacity);
}
