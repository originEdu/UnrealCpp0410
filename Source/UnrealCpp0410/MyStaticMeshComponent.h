// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MyStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP0410_API UMyStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UMyStaticMeshComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
