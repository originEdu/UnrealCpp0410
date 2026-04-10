// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "MyStaticMeshComponent.h"

#include "MyRocket.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(42.0f, 32.0f, 16.0f));


	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	//한번만 하면되니깐 static으로
	//리소스매니저에 알아서 붙여준다
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	LeftPropeller = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("LeftPropeller"));
	LeftPropeller->SetupAttachment(Body);

	RightPropeller = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("RightPropeller"));
	RightPropeller->SetupAttachment(Body);

	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		LeftPropeller->SetStaticMesh(SM_Propeller.Object);
		RightPropeller->SetStaticMesh(SM_Propeller.Object);
	}*/
	LeftPropeller->SetRelativeLocation(FVector(37.0f, 21.0f, 1.0f));
	RightPropeller->SetRelativeLocation(FVector(37.0f, -21.0f, 1.0f));

	LeftArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrow"));
	LeftArrow->SetupAttachment(Body);
	LeftArrow->SetRelativeLocation(FVector(47.0f, -21.0f, -12.0f));

	RightArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrow"));
	RightArrow->SetupAttachment(Body);
	RightArrow->SetRelativeLocation(FVector(47.0f, 21.0f, -12.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->TargetArmLength = 120.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 30.0f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->MaxSpeed = MoveSpeed;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//전방이동 시키기
	AddMovementInput(GetActorForwardVector(), BoostValue);

	//프로펠러 회전
	//LeftPropeller->AddLocalRotation(FRotator(0,0,7200.f*DeltaTime));
	//RightPropeller->AddLocalRotation(FRotator(0, 0, 7200.f * DeltaTime));

	//함수화
	//RotatePorpller(LeftPropeller);
	//RotatePorpller(RightPropeller);
}

//프로펠러 회전 함수
void AMyPawn::RotatePorpller(UStaticMeshComponent* propeller)
{
	propeller->AddLocalRotation(FRotator(0, 0, PropellerRotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyPawn::Fire);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Pressed, this, &AMyPawn::Boost);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Released, this, &AMyPawn::UnBoost);
}


void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(RotationSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0, 0));
}

void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0, 0, RotationSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}


void AMyPawn::Fire()
{
	const FTransform WorldTransform = LeftArrow->GetComponentTransform();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AMyRocket>(AMyRocket::StaticClass(), WorldTransform, SpawnParams);
}

void AMyPawn::Boost()
{
	BoostValue = 1.0f;
}

void AMyPawn::UnBoost()
{
	BoostValue = 0.5f;
}
