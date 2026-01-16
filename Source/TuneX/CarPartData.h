// Copyright TuneX Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CarPartData.generated.h"

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
 * Structure for paint/material configuration
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

	FPaintColor()
		: PaintID(NAME_None)
		, Price(0.0f)
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
