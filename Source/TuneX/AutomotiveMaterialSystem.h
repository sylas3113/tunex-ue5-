// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CarPartData.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "AutomotiveMaterialSystem.generated.h"

/**
 * Global Material Parameter Collections for real-time control
 * These MPCs provide cinematic lighting and camera controls
 */
UCLASS(BlueprintType)
class TUNEX_API UGlobalLightingParameters : public UObject
{
	GENERATED_BODY()

public:
	// Light intensity multiplier (0.1-3.0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Lighting")
	float GlobalLightIntensity;

	// Color temperature in Kelvin (2700-6500)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Lighting")
	float ColorTemperature;

	// Light direction in degrees (0-360)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Lighting")
	float LightDirection;

	// Ambient light contribution (0-1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Lighting")
	float AmbientContribution;

	// HDR exposure multiplier (0.1-4.0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Lighting")
	float HDRExposure;

	UGlobalLightingParameters()
		: GlobalLightIntensity(1.0f)
		, ColorTemperature(5600.0f)
		, LightDirection(45.0f)
		, AmbientContribution(0.3f)
		, HDRExposure(1.0f)
	{
	}
};

/**
 * Camera settings for cinematic automotive visualization
 */
UCLASS(BlueprintType)
class TUNEX_API UCameraSettings : public UObject
{
	GENERATED_BODY()

public:
	// Aperture for depth of field control (1.4-22.0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float Aperture;

	// ISO sensitivity (100-3200)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float ISO;

	// Shutter speed in seconds (1/4000-1/30)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float ShutterSpeed;

	// Focus distance in centimeters (50-2000)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float FocusDistance;

	// Bokeh intensity (0-1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float BokehIntensity;

	UCameraSettings()
		: Aperture(8.0f)
		, ISO(400.0f)
		, ShutterSpeed(0.01f)
		, FocusDistance(500.0f)
		, BokehIntensity(0.5f)
	{
	}
};

/**
 * Automotive Material System Manager
 * Handles material parameter updates, real-time controls, and instance management
 */
UCLASS(BlueprintType)
class TUNEX_API UAutomotiveMaterialSystem : public UObject
{
	GENERATED_BODY()

public:
	UAutomotiveMaterialSystem();

	/**
	 * Updates material parameters on a specific mesh component
	 * @param MeshComponent - Target mesh to update
	 * @param MaterialData - Automotive material data with parameters
	 * @param bForceUpdate - Force update even if parameters haven't changed
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	void UpdateMeshMaterialParameters(UMeshComponent* MeshComponent, const FAutomotiveMaterial& MaterialData, bool bForceUpdate = false);

	/**
	 * Updates a material instance with automotive parameters
	 * @param MaterialInstance - Target material instance
	 * @param MaterialData - Automotive material data with parameters
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	void UpdateMaterialInstance(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

	/**
	 * Creates a material instance from automotive material data
	 * @param MaterialData - Base material data
	 * @return New material instance or nullptr if failed
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	UMaterialInstance* CreateMaterialInstance(const FAutomotiveMaterial& MaterialData);

	/**
	 * Applies paint color to vehicle with advanced material properties
	 * @param MeshComponent - Target mesh component
	 * @param PaintData - Paint color with advanced material properties
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	void ApplyAdvancedPaint(UMeshComponent* MeshComponent, const FPaintColor& PaintData);

	/**
	 * Gets or creates material parameter collection instance
	 * @param WorldContext - World context for MPC instance creation
	 * @param MPC - Material Parameter Collection asset
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	UMaterialParameterCollectionInstance* GetOrCreateMPCInstance(UObject* WorldContext, UMaterialParameterCollection* MPC);

	/**
	 * Updates global lighting parameters
	 * @param WorldContext - World context
	 * @param LightingParams - Global lighting parameters
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	void UpdateGlobalLighting(UObject* WorldContext, const UGlobalLightingParameters& LightingParams);

	/**
	 * Updates camera settings for cinematic visualization
	 * @param WorldContext - World context
	 * @param CameraSettings - Camera parameters
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	void UpdateCameraSettings(UObject* WorldContext, const UCameraSettings& CameraSettings);

	/**
	 * Validates automotive material parameters
	 * @param MaterialData - Material data to validate
	 * @return true if parameters are valid
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	bool ValidateMaterialParameters(const FAutomotiveMaterial& MaterialData) const;

	/**
	 * Gets debug information for material parameters
	 * @param MaterialData - Material data to analyze
	 * @return Debug information string
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Material System")
	FString GetMaterialDebugInfo(const FAutomotiveMaterial& MaterialData) const;

protected:
	/**
	 * Updates layer 1: Primer parameters
	 */
	void ApplyPrimerLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

	/**
	 * Updates layer 2: Base Color parameters
	 */
	void ApplyBaseColorLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

	/**
	 * Updates layer 3: Clear Coat parameters
	 */
	void ApplyClearCoatLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

	/**
	 * Updates layer 4: Ceramic Coating parameters
	 */
	void ApplyCeramicCoatingLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

	/**
	 * Updates carbon fiber specific parameters
	 */
	void ApplyCarbonFiberParameters(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

	/**
	 * Updates glass specific parameters
	 */
	void ApplyGlassParameters(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData);

private:
	// Cache for material parameter collections
	UPROPERTY()
	UMaterialParameterCollection* CachedLightingMPC;

	UPROPERTY()
	UMaterialParameterCollection* CachedCameraMPC;

	// Last applied material data for change detection
	FAutomotiveMaterial LastAppliedMaterial;
	TMap<UMeshComponent*, FAutomotiveMaterial> ComponentMaterialCache;
};

/**
 * Blueprint callable functions for automotive material operations
 */
UCLASS()
class TUNEX_API UAutomotiveMaterialLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Creates an automotive material with default parameters
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Materials", CallInEditor = true)
	static FAutomotiveMaterial CreateDefaultAutomotiveMaterial(EMaterialType MaterialType);

	/**
	 * Gets preset automotive materials
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Materials")
	static FAutomotiveMaterial GetMaterialPreset(FName PresetName);

	/**
	 * Converts legacy paint color to automotive material
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Materials")
	static FAutomotiveMaterial ConvertLegacyPaintToAutomotive(const FPaintColor& LegacyPaint);

	/**
	 * Validates material type compatibility
	 */
	UFUNCTION(BlueprintCallable, Category = "Automotive Materials")
	static bool IsMaterialTypeCompatible(EMaterialType MaterialType, const FString& UseCase);

	/**
	 * Gets material type display name
	 */
	UFUNCTION(BlueprintPure, Category = "Automotive Materials")
	static FString GetMaterialTypeDisplayName(EMaterialType MaterialType);
};