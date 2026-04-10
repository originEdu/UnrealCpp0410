// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	//CDO(Class Default Object) 초기화로 용도가 변경된다
	//에셋 로딩하면 안됨
	//UE_LOG(LogTemp, Warning, TEXT("안녕하세요"));
	DefaultPawnClass = AMyPawn::StaticClass(); // 디폴트폰클래스 변경
	PlayerControllerClass = AMyPlayerController::StaticClass(); // 플레이어 컨트롤러 변경
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello World"));
	}
}
