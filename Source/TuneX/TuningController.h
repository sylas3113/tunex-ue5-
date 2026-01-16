// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VehicleModifierInterface.h"
#include "TuningController.generated.h"

/**
 * Player controller specialized for vehicle tuning
 * Handles keyboard input for cycling through vehicle options
 */
UCLASS()
class TUNEX_API ATuningController : public APlayerController
{
	GENERATED_BODY()

public:
	ATuningController();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

public:
	// Reference to the vehicle being tuned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tuning")
	AActor* TargetVehicle;

	// Auto-find vehicle on begin play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tuning")
	bool bAutoFindVehicle;

	/**
	 * Sets the target vehicle for tuning
	 * @param Vehicle - The vehicle actor to tune
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SetTargetVehicle(AActor* Vehicle);

	/**
	 * Cycles to bumper option 1
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SelectBumperOption1();

	/**
	 * Cycles to bumper option 2
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SelectBumperOption2();

	/**
	 * Cycles to bumper option 3
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SelectBumperOption3();

	/**
	 * Cycles to paint option 1
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SelectPaintOption1();

	/**
	 * Cycles to paint option 2
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SelectPaintOption2();

	/**
	 * Cycles to paint option 3
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void SelectPaintOption3();

	/**
	 * Cycles to the next bumper
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void CycleNextBumper();

	/**
	 * Cycles to the next paint
	 */
	UFUNCTION(BlueprintCallable, Category = "Tuning")
	void CycleNextPaint();

private:
	/**
	 * Gets the vehicle modifier interface from the target vehicle
	 */
	IVehicleModifierInterface* GetVehicleInterface();

	/**
	 * Auto-finds the first vehicle in the world that implements the interface
	 */
	void AutoFindVehicle();

	// Input handler functions
	void HandleBumperInput1();
	void HandleBumperInput2();
	void HandleBumperInput3();
	void HandlePaintInputQ();
	void HandlePaintInputW();
	void HandlePaintInputE();
};
