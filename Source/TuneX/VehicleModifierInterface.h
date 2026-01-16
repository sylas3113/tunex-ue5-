// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CarPartData.h"
#include "VehicleModifierInterface.generated.h"

/**
 * Event dispatcher for vehicle modification completion
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModificationComplete, const FString&, ModificationDetails);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UVehicleModifierInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for vehicle modification communication
 * Allows UI and controllers to interact with vehicle actors
 */
class TUNEX_API IVehicleModifierInterface
{
	GENERATED_BODY()

public:
	/**
	 * Sets the front bumper to the specified bumper ID
	 * @param BumperID - Unique identifier for the bumper part
	 * @return true if the bumper was successfully changed
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	bool SetFrontBumper(FName BumperID);

	/**
	 * Sets the rear bumper to the specified bumper ID
	 * @param BumperID - Unique identifier for the bumper part
	 * @return true if the bumper was successfully changed
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	bool SetRearBumper(FName BumperID);

	/**
	 * Sets the paint/material to the specified paint ID
	 * @param PaintID - Unique identifier for the paint color
	 * @return true if the paint was successfully changed
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	bool SetPaint(FName PaintID);

	/**
	 * Gets the current front bumper configuration
	 * @return The current front bumper part data
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	FCarPart GetCurrentFrontBumper() const;

	/**
	 * Gets the current paint configuration
	 * @return The current paint color data
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	FPaintColor GetCurrentPaint() const;

	/**
	 * Cycles to the next front bumper option
	 * @return true if successfully cycled
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	bool CycleNextFrontBumper();

	/**
	 * Cycles to the next paint option
	 * @return true if successfully cycled
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Modification")
	bool CycleNextPaint();
};
