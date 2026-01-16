// Copyright TuneX Project. All Rights Reserved.

#include "VehicleActor.h"
#include "VehicleMasterComponent.h"
#include "Components/StaticMeshComponent.h"

AVehicleActor::AVehicleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the root mesh component
	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	RootComponent = VehicleMesh;

	// Create the master component
	VehicleMasterComponent = CreateDefaultSubobject<UVehicleMasterComponent>(TEXT("VehicleMasterComponent"));
}

void AVehicleActor::BeginPlay()
{
	Super::BeginPlay();

	// Set the main vehicle mesh reference
	if (VehicleMasterComponent)
	{
		VehicleMasterComponent->MainVehicleMesh = VehicleMesh;

		// Bind to modification events
		VehicleMasterComponent->OnBumperChanged.AddDynamic(this, 
			[this](FName BumperID, const FString& DisplayName)
			{
				OnModificationComplete.Broadcast(FString::Printf(TEXT("Bumper: %s"), *DisplayName));
			}
		);

		VehicleMasterComponent->OnPaintChanged.AddDynamic(this,
			[this](FName PaintID, const FString& DisplayName)
			{
				OnModificationComplete.Broadcast(FString::Printf(TEXT("Paint: %s"), *DisplayName));
			}
		);
	}
}

bool AVehicleActor::SetFrontBumper_Implementation(FName BumperID)
{
	if (VehicleMasterComponent)
	{
		return VehicleMasterComponent->SetFrontBumperByID(BumperID);
	}
	return false;
}

bool AVehicleActor::SetRearBumper_Implementation(FName BumperID)
{
	// Rear bumper not implemented in Phase 1, but interface is ready
	UE_LOG(LogTemp, Warning, TEXT("VehicleActor: Rear bumper modification not yet implemented"));
	return false;
}

bool AVehicleActor::SetPaint_Implementation(FName PaintID)
{
	if (VehicleMasterComponent)
	{
		return VehicleMasterComponent->SetPaintByID(PaintID);
	}
	return false;
}

FCarPart AVehicleActor::GetCurrentFrontBumper_Implementation() const
{
	if (VehicleMasterComponent)
	{
		return VehicleMasterComponent->GetCurrentFrontBumper();
	}
	return FCarPart();
}

FPaintColor AVehicleActor::GetCurrentPaint_Implementation() const
{
	if (VehicleMasterComponent)
	{
		return VehicleMasterComponent->GetCurrentPaint();
	}
	return FPaintColor();
}

bool AVehicleActor::CycleNextFrontBumper_Implementation()
{
	if (VehicleMasterComponent)
	{
		return VehicleMasterComponent->CycleNextFrontBumper();
	}
	return false;
}

bool AVehicleActor::CycleNextPaint_Implementation()
{
	if (VehicleMasterComponent)
	{
		return VehicleMasterComponent->CycleNextPaint();
	}
	return false;
}
