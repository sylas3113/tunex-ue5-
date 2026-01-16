// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CarPartData.generated.h"

/**
 * Material type enumeration for automotive materials
 */
UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	MetallicPaint		UMETA(DisplayName = "Metallic Paint"),
	PearlPaint			UMETA(DisplayName = "Pearl Paint"),
	FrozenPaint			UMETA(DisplayName = "Frozen Paint"),
	CarbonFiber			UMETA(DisplayName = "Carbon Fiber"),
	Glass				UMETA(DisplayName = "Glass with Ceramic Tint"),
	SolidPaint			UMETA(DisplayName = "Solid Paint"),
	MattePaint			UMETA(DisplayName = "Matte Paint")
};

/**
 * Structure for advanced automotive material configuration
 */
USTRUCT(BlueprintType)
struct FAutomotiveMaterial
{
	GENERATED_BODY()

	// Material type classification
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Automotive Material")
	TEnumAsByte<EMaterialType> MaterialType;

	// Base material instance (for material instances)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Automotive Material")
	TSoftObjectPtr<UMaterialInterface> BaseMaterial;

	// Display name shown in UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Automotive Material")
	FString DisplayName;

	// Unique identifier for this material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Automotive Material")
	FName MaterialID;

	// Price for this material option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Automotive Material")
	float Price;

	// Layer 1: Primer settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primer Layer")
	float PrimerRoughness; // Default: 0.8

	// Layer 2: Base Color settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Color Layer")
	FLinearColor BaseColor; // RGB color input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Color Layer")
	float MetallicIntensity; // Metallic flake control (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Color Layer")
	float PearlShiftIntensity; // Pearl shift effect (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Color Layer")
	FLinearColor PearlShiftColor; // RGB shift based on viewing angle

	// Layer 3: Clear Coat settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clear Coat Layer")
	float ClearCoatGlossiness; // Glossiness slider (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clear Coat Layer")
	float ClearCoatRoughness; // Roughness override

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clear Coat Layer")
	float RefractiveIndex; // Physically accurate IOR (1.3-1.6)

	// Layer 4: Ceramic Coating settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ceramic Coating Layer")
	bool bEnableCeramicCoating; // Optional refraction layer for depth

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ceramic Coating Layer")
	float HydrophobicModifier; // Hydrophobic property modifier (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ceramic Coating Layer")
	float DurabilityFactor; // Durability visualization parameter (0-1)

	// Carbon Fiber specific settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbon Fiber")
	float WeaveScale; // Weave scale adjustment (0.1-2.0)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbon Fiber")
	float WeaveAngle; // Direction control (0°, 45°, 90°)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbon Fiber")
	float ResinTintIntensity; // Resin tint parameter (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carbon Fiber")
	float CarbonFiberGloss; // Gloss/Matte slider (0-1)

	// Glass specific settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glass")
	float VisibleLightTransmission; // VLT % slider: 0-100%

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glass")
	FLinearColor GlassTintColor; // Optional color tint

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glass")
	float FresnelEdgeDarkening; // Fresnel-based edge darkening (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glass")
	float InteriorReflection; // Interior reflection parameter (0-1)

	FAutomotiveMaterial()
		: MaterialType(EMaterialType::MetallicPaint)
		, MaterialID(NAME_None)
		, Price(0.0f)
		, PrimerRoughness(0.8f)
		, BaseColor(FLinearColor::White)
		, MetallicIntensity(0.5f)
		, PearlShiftIntensity(0.0f)
		, PearlShiftColor(FLinearColor::Silver)
		, ClearCoatGlossiness(0.9f)
		, ClearCoatRoughness(0.1f)
		, RefractiveIndex(1.5f)
		, bEnableCeramicCoating(false)
		, HydrophobicModifier(0.7f)
		, DurabilityFactor(0.8f)
		, WeaveScale(1.0f)
		, WeaveAngle(0.0f)
		, ResinTintIntensity(0.3f)
		, CarbonFiberGloss(0.6f)
		, VisibleLightTransmission(70.0f)
		, GlassTintColor(FLinearColor::White)
		, FresnelEdgeDarkening(0.3f)
		, InteriorReflection(0.5f)
	{
	}
};

/**
 * Structure that defines a single car part with all its metadata
 * Used for bumpers, lights, wheels, interior components, etc.
 */
USTRUCT(BlueprintType)
struct FCarPart
{
	GENERATED_BODY()

	// The mesh asset (can be either Static or Skeletal Mesh)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	TSoftObjectPtr<UObject> MeshAsset;

	// Display name shown in UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	FString DisplayName;

	// Price in game currency
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	float Price;

	// Tags used for compatibility checking (e.g., "BMW_G82", "Front_Bumper")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	TArray<FName> CompatibilityTags;

	// Optional material overrides for this part
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	TArray<TSoftObjectPtr<UMaterialInterface>> MaterialOverrides;

	// Optional sound modifier (e.g., exhaust note changes)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	TSoftObjectPtr<USoundWave> SoundModifier;

	// Unique identifier for this part
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Part")
	FName PartID;

	FCarPart()
		: Price(0.0f)
		, PartID(NAME_None)
	{
	}
};

/**
 * Structure for paint/material configuration (legacy support)
 */
USTRUCT(BlueprintType)
struct FPaintColor
{
	GENERATED_BODY()

	// Display name of the paint color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
	FString DisplayName;

	// Material to apply for this paint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
	TSoftObjectPtr<UMaterialInterface> Material;

	// Unique identifier for this paint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
	FName PaintID;

	// Price for this paint option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
	float Price;

	// Extended automotive material properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Automotive Material")
	FAutomotiveMaterial AdvancedMaterial;

	// Legacy compatibility flag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
	bool bUseLegacyMaterial;

	FPaintColor()
		: PaintID(NAME_None)
		, Price(0.0f)
		, bUseLegacyMaterial(true)
	{
	}
};

/**
 * Data Asset that stores vehicle configuration options
 * Contains all available parts and paint colors for a specific vehicle
 */
UCLASS(BlueprintType)
class TUNEX_API UVehicleConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Available front bumpers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts|Bumpers")
	TArray<FCarPart> FrontBumpers;

	// Available rear bumpers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts|Bumpers")
	TArray<FCarPart> RearBumpers;

	// Available side skirts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts|Body")
	TArray<FCarPart> SideSkirts;

	// Available spoilers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts|Aero")
	TArray<FCarPart> Spoilers;

	// Available wheels
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts|Wheels")
	TArray<FCarPart> Wheels;

	// Available paint colors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
	TArray<FPaintColor> PaintColors;

	// Default selections (indices)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultFrontBumperIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultRearBumperIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	int32 DefaultPaintIndex;

	UVehicleConfigDataAsset()
		: DefaultFrontBumperIndex(0)
		, DefaultRearBumperIndex(0)
		, DefaultPaintIndex(0)
	{
	}
};