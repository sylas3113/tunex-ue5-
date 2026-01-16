// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarPartData.h"
#include "AutomotiveMaterialSystem.h"
#include "VehicleMasterComponent.generated.h"

/**
 * Event dispatchers for component modifications
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBumperChanged, FName, BumperID, const FString&, DisplayName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPaintChanged, FName, PaintID, const FString&, DisplayName);

/**
 * Master component for managing vehicle configuration
 * Handles modular attachment points, dynamic material swaps, and part management
 * This component is vehicle-agnostic and can be used for any car model
 */
UCLASS(ClassGroup=(TuneX), meta=(BlueprintSpawnableComponent))
class TUNEX_API UVehicleMasterComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UVehicleMasterComponent();

protected:
    virtual void BeginPlay() override;

public:    
    // Event dispatchers for UI binding
    UPROPERTY(BlueprintAssignable, Category = "Vehicle Events")
    FOnBumperChanged OnBumperChanged;

    UPROPERTY(BlueprintAssignable, Category = "Vehicle Events")
    FOnPaintChanged OnPaintChanged;

    // Reference to the vehicle configuration data asset
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Configuration")
    UVehicleConfigDataAsset* VehicleConfig;

    // Current selection indices
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle State")
    int32 CurrentFrontBumperIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle State")
    int32 CurrentRearBumperIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle State")
    int32 CurrentPaintIndex;

    // Socket names for attachment points
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Configuration|Sockets")
    FName FrontBumperSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Configuration|Sockets")
    FName RearBumperSocketName;

    // Reference to the main vehicle mesh component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Configuration")
    UMeshComponent* MainVehicleMesh;

    // Currently attached part components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle State")
    UStaticMeshComponent* FrontBumperComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle State")
    UStaticMeshComponent* RearBumperComponent;

    /**
     * Initializes the vehicle with default configuration
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    void InitializeVehicle();

    /**
     * Sets the front bumper by part ID
     * @param BumperID - Unique identifier for the bumper
     * @return true if successful
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    bool SetFrontBumperByID(FName BumperID);

    /**
     * Sets the front bumper by index
     * @param Index - Index in the FrontBumpers array
     * @return true if successful
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    bool SetFrontBumperByIndex(int32 Index);

    /**
     * Sets the paint/material by paint ID
     * @param PaintID - Unique identifier for the paint
     * @return true if successful
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    bool SetPaintByID(FName PaintID);

    /**
     * Sets the paint/material by index
     * @param Index - Index in the PaintColors array
     * @return true if successful
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    bool SetPaintByIndex(int32 Index);

    /**
     * Cycles to the next front bumper option
     * @return true if successful
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    bool CycleNextFrontBumper();

    /**
     * Cycles to the next paint option
     * @return true if successful
     */
    UFUNCTION(BlueprintCallable, Category = "Vehicle Modification")
    bool CycleNextPaint();

    /**
     * Gets the current front bumper data
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Vehicle Modification")
    FCarPart GetCurrentFrontBumper() const;

    /**
     * Gets the current paint data
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Vehicle Modification")
    FPaintColor GetCurrentPaint() const;

private:
    /**
     * Validates the vehicle configuration data
     * @return true if configuration is valid
     */
    bool ValidateConfiguration() const;

    /**
     * Applies the bumper mesh to the component
     * @param BumperComponent - The component to modify
     * @param PartData - The part data containing mesh information
     */
    void ApplyBumperMesh(UStaticMeshComponent* BumperComponent, const FCarPart& PartData);

    /**
     * Applies the paint material to the main vehicle mesh
     * @param PaintData - The paint data containing material information
     */
    void ApplyPaintMaterial(const FPaintColor& PaintData);

    /**
     * Creates or gets a bumper component
     * @param ComponentName - Name for the component
     * @return The static mesh component
     */
    UStaticMeshComponent* GetOrCreateBumperComponent(FName ComponentName);
};
