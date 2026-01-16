// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleModifierInterface.h"
#include "VehicleActor.generated.h"

class UVehicleMasterComponent;

/**
 * Base vehicle actor that implements the VehicleModifierInterface
 * This is a blueprint-friendly actor that can be extended for specific vehicles
 */
UCLASS(Blueprintable)
class TUNEX_API AVehicleActor : public AActor, public IVehicleModifierInterface
{
	GENERATED_BODY()
	
public:	
	AVehicleActor();

protected:
	virtual void BeginPlay() override;

public:	
	// Main vehicle mesh (chassis)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	UStaticMeshComponent* VehicleMesh;

	// Master component for configuration management
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	UVehicleMasterComponent* VehicleMasterComponent;

	// Event dispatcher for modifications
	UPROPERTY(BlueprintAssignable, Category = "Vehicle Events")
	FOnModificationComplete OnModificationComplete;

	// IVehicleModifierInterface implementation
	virtual bool SetFrontBumper_Implementation(FName BumperID) override;
	virtual bool SetRearBumper_Implementation(FName BumperID) override;
	virtual bool SetPaint_Implementation(FName PaintID) override;
	virtual FCarPart GetCurrentFrontBumper_Implementation() const override;
	virtual FPaintColor GetCurrentPaint_Implementation() const override;
	virtual bool CycleNextFrontBumper_Implementation() override;
	virtual bool CycleNextPaint_Implementation() override;
};
