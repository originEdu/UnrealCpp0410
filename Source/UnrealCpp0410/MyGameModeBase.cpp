// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

AMyGameModeBase::AMyGameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("안녕하세요"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello World"));
	}
	
}
