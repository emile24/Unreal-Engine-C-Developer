// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Tank.h"


ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UPlayerUI> PlayerUIClassFinder(TEXT("/Game/UI/PlayerUI_BP"));
	PlayerUIClass = PlayerUIClassFinder.Class;
}

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	PlayerUI = CreateWidget<UPlayerUI>(this, PlayerUIClass);
	PlayerUI->AddToViewport();

	ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *(ControlledTank->GetName()));
	}	
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!ControlledTank) { return; }

	FVector HitLocation; // OUT pamameter
		
	// Can also use GetHitResultAtScreenPosition()
	if (GetSightRayHitLocation(HitLocation)) {
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixel coordinate
	int32 ViewPortSizeX, ViewportSizeY;
	GetViewportSize(ViewPortSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
		
	//Deproject the screen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//Line-trace along that LookDirection, and see what we hit
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	FCollisionQueryParams query = FCollisionQueryParams::DefaultQueryParam;
	query.AddIgnoredActor(ControlledTank);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, query)) {
		HitLocation = HitResult.Location;
		AActor* HitActor = HitResult.GetActor();
		return true;
	}
	HitLocation = FVector(0);
	return false;
}