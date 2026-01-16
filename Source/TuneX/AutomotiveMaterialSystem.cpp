// Copyright TuneX Project. All Rights Reserved.

#include "AutomotiveMaterialSystem.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/MeshComponent.h"

UAutomotiveMaterialSystem::UAutomotiveMaterialSystem()
{
	// Initialize cached MPCs
	CachedLightingMPC = nullptr;
	CachedCameraMPC = nullptr;
}

void UAutomotiveMaterialSystem::UpdateMeshMaterialParameters(UMeshComponent* MeshComponent, const FAutomotiveMaterial& MaterialData, bool bForceUpdate)
{
	if (!MeshComponent || !MaterialData.BaseMaterial.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAutomotiveMaterialSystem::UpdateMeshMaterialParameters - Invalid mesh component or material"));
		return;
	}

	// Check if parameters have changed (unless forcing update)
	if (!bForceUpdate && ComponentMaterialCache.Contains(MeshComponent))
	{
		const FAutomotiveMaterial& CachedMaterial = ComponentMaterialCache[MeshComponent];
		if (CachedMaterial == MaterialData)
		{
			return; // No changes detected
		}
	}

	// Get or create dynamic material instance
	UMaterialInterface* BaseMaterial = MaterialData.BaseMaterial.Get();
	if (!BaseMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UAutomotiveMaterialSystem::UpdateMeshMaterialParameters - Base material not loaded"));
		return;
	}

	UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(MeshComponent->GetMaterial(0));
	if (!DynamicMaterial || DynamicMaterial->GetParent() != BaseMaterial)
	{
		DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		if (!DynamicMaterial)
		{
			UE_LOG(LogTemp, Error, TEXT("UAutomotiveMaterialSystem::UpdateMeshMaterialParameters - Failed to create dynamic material instance"));
			return;
		}
	}

	// Apply material parameters based on type
	switch (MaterialData.MaterialType)
	{
		case EMaterialType::MetallicPaint:
		case EMaterialType::PearlPaint:
		case EMaterialType::FrozenPaint:
		case EMaterialType::SolidPaint:
		case EMaterialType::MattePaint:
			ApplyBaseColorLayer(DynamicMaterial, MaterialData);
			ApplyClearCoatLayer(DynamicMaterial, MaterialData);
			if (MaterialData.bEnableCeramicCoating)
			{
				ApplyCeramicCoatingLayer(DynamicMaterial, MaterialData);
			}
			break;

		case EMaterialType::CarbonFiber:
			ApplyCarbonFiberParameters(DynamicMaterial, MaterialData);
			break;

		case EMaterialType::Glass:
			ApplyGlassParameters(DynamicMaterial, MaterialData);
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("UAutomotiveMaterialSystem::UpdateMeshMaterialParameters - Unknown material type: %d"), (int32)MaterialData.MaterialType);
			break;
	}

	// Cache the material data
	ComponentMaterialCache.Add(MeshComponent, MaterialData);
}

void UAutomotiveMaterialSystem::UpdateMaterialInstance(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAutomotiveMaterialSystem::UpdateMaterialInstance - Invalid material instance"));
		return;
	}

	// Apply material parameters based on type
	switch (MaterialData.MaterialType)
	{
		case EMaterialType::MetallicPaint:
		case EMaterialType::PearlPaint:
		case EMaterialType::FrozenPaint:
		case EMaterialType::SolidPaint:
		case EMaterialType::MattePaint:
			ApplyBaseColorLayer(MaterialInstance, MaterialData);
			ApplyClearCoatLayer(MaterialInstance, MaterialData);
			if (MaterialData.bEnableCeramicCoating)
			{
				ApplyCeramicCoatingLayer(MaterialInstance, MaterialData);
			}
			break;

		case EMaterialType::CarbonFiber:
			ApplyCarbonFiberParameters(MaterialInstance, MaterialData);
			break;

		case EMaterialType::Glass:
			ApplyGlassParameters(MaterialInstance, MaterialData);
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("UAutomotiveMaterialSystem::UpdateMaterialInstance - Unknown material type: %d"), (int32)MaterialData.MaterialType);
			break;
	}
}

UMaterialInstance* UAutomotiveMaterialSystem::CreateMaterialInstance(const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialData.BaseMaterial.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UAutomotiveMaterialSystem::CreateMaterialInstance - Base material not valid"));
		return nullptr;
	}

	UMaterialInterface* BaseMaterial = MaterialData.BaseMaterial.Get();
	UMaterialInstance* MaterialInstance = CreateDynamicMaterialInstance(BaseMaterial);
	
	if (MaterialInstance)
	{
		UpdateMaterialInstance(MaterialInstance, MaterialData);
	}

	return MaterialInstance;
}

void UAutomotiveMaterialSystem::ApplyAdvancedPaint(UMeshComponent* MeshComponent, const FPaintColor& PaintData)
{
	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAutomotiveMaterialSystem::ApplyAdvancedPaint - Invalid mesh component"));
		return;
	}

	// Handle legacy materials
	if (PaintData.bUseLegacyMaterial && PaintData.Material.IsValid())
	{
		UMaterialInterface* LegacyMaterial = PaintData.Material.Get();
		MeshComponent->SetMaterial(0, LegacyMaterial);
		return;
	}

	// Apply advanced material
	if (PaintData.AdvancedMaterial.BaseMaterial.IsValid())
	{
		UpdateMeshMaterialParameters(MeshComponent, PaintData.AdvancedMaterial, true);
	}
}

UMaterialParameterCollectionInstance* UAutomotiveMaterialSystem::GetOrCreateMPCInstance(UObject* WorldContext, UMaterialParameterCollection* MPC)
{
	if (!WorldContext || !MPC)
	{
		return nullptr;
	}

	UWorld* World = WorldContext->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	return World->GetParameterCollectionInstance(MPC);
}

void UAutomotiveMaterialSystem::UpdateGlobalLighting(UObject* WorldContext, const UGlobalLightingParameters& LightingParams)
{
	if (!WorldContext || !CachedLightingMPC)
	{
		return;
	}

	UMaterialParameterCollectionInstance* MPCInstance = GetOrCreateMPCInstance(WorldContext, CachedLightingMPC);
	if (!MPCInstance)
	{
		return;
	}

	// Update scalar parameters
	MPCInstance->SetScalarParameterValue(TEXT("GlobalLightIntensity"), LightingParams.GlobalLightIntensity);
	MPCInstance->SetScalarParameterValue(TEXT("ColorTemperature"), LightingParams.ColorTemperature);
	MPCInstance->SetScalarParameterValue(TEXT("LightDirection"), LightingParams.LightDirection);
	MPCInstance->SetScalarParameterValue(TEXT("AmbientContribution"), LightingParams.AmbientContribution);
	MPCInstance->SetScalarParameterValue(TEXT("HDRExposure"), LightingParams.HDRExposure);
}

void UAutomotiveMaterialSystem::UpdateCameraSettings(UObject* WorldContext, const UCameraSettings& CameraSettings)
{
	if (!WorldContext || !CachedCameraMPC)
	{
		return;
	}

	UMaterialParameterCollectionInstance* MPCInstance = GetOrCreateMPCInstance(WorldContext, CachedCameraMPC);
	if (!MPCInstance)
	{
		return;
	}

	// Update scalar parameters
	MPCInstance->SetScalarParameterValue(TEXT("Aperture"), CameraSettings.Aperture);
	MPCInstance->SetScalarParameterValue(TEXT("ISO"), CameraSettings.ISO);
	MPCInstance->SetScalarParameterValue(TEXT("ShutterSpeed"), CameraSettings.ShutterSpeed);
	MPCInstance->SetScalarParameterValue(TEXT("FocusDistance"), CameraSettings.FocusDistance);
	MPCInstance->SetScalarParameterValue(TEXT("BokehIntensity"), CameraSettings.BokehIntensity);
}

bool UAutomotiveMaterialSystem::ValidateMaterialParameters(const FAutomotiveMaterial& MaterialData) const
{
	// Validate base parameters
	if (MaterialData.Price < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid price: %f"), MaterialData.Price);
		return false;
	}

	// Validate layer parameters
	if (MaterialData.PrimerRoughness < 0.0f || MaterialData.PrimerRoughness > 1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid primer roughness: %f"), MaterialData.PrimerRoughness);
		return false;
	}

	if (MaterialData.ClearCoatGlossiness < 0.0f || MaterialData.ClearCoatGlossiness > 1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid clear coat glossiness: %f"), MaterialData.ClearCoatGlossiness);
		return false;
	}

	// Validate carbon fiber parameters
	if (MaterialData.MaterialType == EMaterialType::CarbonFiber)
	{
		if (MaterialData.WeaveScale < 0.1f || MaterialData.WeaveScale > 2.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid carbon fiber weave scale: %f"), MaterialData.WeaveScale);
			return false;
		}

		if (MaterialData.WeaveAngle < 0.0f || MaterialData.WeaveAngle > 90.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid carbon fiber weave angle: %f"), MaterialData.WeaveAngle);
			return false;
		}
	}

	// Validate glass parameters
	if (MaterialData.MaterialType == EMaterialType::Glass)
	{
		if (MaterialData.VisibleLightTransmission < 0.0f || MaterialData.VisibleLightTransmission > 100.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid glass VLT: %f"), MaterialData.VisibleLightTransmission);
			return false;
		}
	}

	return true;
}

FString UAutomotiveMaterialSystem::GetMaterialDebugInfo(const FAutomotiveMaterial& MaterialData) const
{
	FString DebugInfo;
	DebugInfo += FString::Printf(TEXT("Material Type: %s\n"), *UAutomotiveMaterialLibrary::GetMaterialTypeDisplayName(MaterialData.MaterialType));
	DebugInfo += FString::Printf(TEXT("Display Name: %s\n"), *MaterialData.DisplayName);
	DebugInfo += FString::Printf(TEXT("Price: $%.2f\n"), MaterialData.Price);
	DebugInfo += FString::Printf(TEXT("Base Color: R=%.2f, G=%.2f, B=%.2f\n"), 
		MaterialData.BaseColor.R, MaterialData.BaseColor.G, MaterialData.BaseColor.B);
	DebugInfo += FString::Printf(TEXT("Metallic Intensity: %.2f\n"), MaterialData.MetallicIntensity);
	DebugInfo += FString::Printf(TEXT("Pearl Shift Intensity: %.2f\n"), MaterialData.PearlShiftIntensity);
	DebugInfo += FString::Printf(TEXT("Clear Coat Glossiness: %.2f\n"), MaterialData.ClearCoatGlossiness);

	if (MaterialData.MaterialType == EMaterialType::CarbonFiber)
	{
		DebugInfo += FString::Printf(TEXT("Weave Scale: %.2f\n"), MaterialData.WeaveScale);
		DebugInfo += FString::Printf(TEXT("Weave Angle: %.1f degrees\n"), MaterialData.WeaveAngle);
		DebugInfo += FString::Printf(TEXT("Carbon Fiber Gloss: %.2f\n"), MaterialData.CarbonFiberGloss);
	}
	else if (MaterialData.MaterialType == EMaterialType::Glass)
	{
		DebugInfo += FString::Printf(TEXT("Visible Light Transmission: %.1f%%\n"), MaterialData.VisibleLightTransmission);
		DebugInfo += FString::Printf(TEXT("Fresnel Edge Darkening: %.2f\n"), MaterialData.FresnelEdgeDarkening);
	}

	return DebugInfo;
}

void UAutomotiveMaterialSystem::ApplyPrimerLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		return;
	}

	// Apply primer roughness parameter
	MaterialInstance->SetScalarParameterValue(TEXT("PrimerRoughness"), MaterialData.PrimerRoughness);
}

void UAutomotiveMaterialSystem::ApplyBaseColorLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		return;
	}

	// Apply base color parameters
	MaterialInstance->SetVectorParameterValue(TEXT("BaseColor"), MaterialData.BaseColor);
	MaterialInstance->SetScalarParameterValue(TEXT("MetallicIntensity"), MaterialData.MetallicIntensity);
	MaterialInstance->SetScalarParameterValue(TEXT("PearlShiftIntensity"), MaterialData.PearlShiftIntensity);
	MaterialInstance->SetVectorParameterValue(TEXT("PearlShiftColor"), MaterialData.PearlShiftColor);
}

void UAutomotiveMaterialSystem::ApplyClearCoatLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		return;
	}

	// Apply clear coat parameters
	MaterialInstance->SetScalarParameterValue(TEXT("ClearCoatGlossiness"), MaterialData.ClearCoatGlossiness);
	MaterialInstance->SetScalarParameterValue(TEXT("ClearCoatRoughness"), MaterialData.ClearCoatRoughness);
	MaterialInstance->SetScalarParameterValue(TEXT("RefractiveIndex"), MaterialData.RefractiveIndex);
}

void UAutomotiveMaterialSystem::ApplyCeramicCoatingLayer(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		return;
	}

	// Apply ceramic coating parameters
	MaterialInstance->SetScalarParameterValue(TEXT("HydrophobicModifier"), MaterialData.HydrophobicModifier);
	MaterialInstance->SetScalarParameterValue(TEXT("DurabilityFactor"), MaterialData.DurabilityFactor);
}

void UAutomotiveMaterialSystem::ApplyCarbonFiberParameters(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		return;
	}

	// Apply carbon fiber specific parameters
	MaterialInstance->SetScalarParameterValue(TEXT("WeaveScale"), MaterialData.WeaveScale);
	MaterialInstance->SetScalarParameterValue(TEXT("WeaveAngle"), MaterialData.WeaveAngle);
	MaterialInstance->SetScalarParameterValue(TEXT("ResinTintIntensity"), MaterialData.ResinTintIntensity);
	MaterialInstance->SetScalarParameterValue(TEXT("CarbonFiberGloss"), MaterialData.CarbonFiberGloss);
}

void UAutomotiveMaterialSystem::ApplyGlassParameters(UMaterialInstance* MaterialInstance, const FAutomotiveMaterial& MaterialData)
{
	if (!MaterialInstance)
	{
		return;
	}

	// Apply glass specific parameters
	MaterialInstance->SetScalarParameterValue(TEXT("VisibleLightTransmission"), MaterialData.VisibleLightTransmission);
	MaterialInstance->SetVectorParameterValue(TEXT("GlassTintColor"), MaterialData.GlassTintColor);
	MaterialInstance->SetScalarParameterValue(TEXT("FresnelEdgeDarkening"), MaterialData.FresnelEdgeDarkening);
	MaterialInstance->SetScalarParameterValue(TEXT("InteriorReflection"), MaterialData.InteriorReflection);
}

FAutomotiveMaterial UAutomotiveMaterialLibrary::CreateDefaultAutomotiveMaterial(EMaterialType MaterialType)
{
	FAutomotiveMaterial Material;
	Material.MaterialType = MaterialType;
	Material.MaterialID = FName(*FString::Printf(TEXT("Default_%s"), *UAutomotiveMaterialLibrary::GetMaterialTypeDisplayName(MaterialType).Replace(TEXT(" "), TEXT(""))));
	
	switch (MaterialType)
	{
		case EMaterialType::MetallicPaint:
			Material.DisplayName = TEXT("Default Metallic Paint");
			Material.BaseColor = FLinearColor(0.8f, 0.8f, 0.8f);
			Material.MetallicIntensity = 0.8f;
			Material.ClearCoatGlossiness = 0.9f;
			break;

		case EMaterialType::PearlPaint:
			Material.DisplayName = TEXT("Default Pearl Paint");
			Material.BaseColor = FLinearColor(0.9f, 0.9f, 0.9f);
			Material.MetallicIntensity = 0.6f;
			Material.PearlShiftIntensity = 0.7f;
			Material.ClearCoatGlossiness = 0.95f;
			break;

		case EMaterialType::FrozenPaint:
			Material.DisplayName = TEXT("Default Frozen Paint");
			Material.BaseColor = FLinearColor(0.95f, 0.95f, 0.95f);
			Material.MetallicIntensity = 0.9f;
			Material.PearlShiftIntensity = 0.8f;
			Material.ClearCoatGlossiness = 0.98f;
			break;

		case EMaterialType::CarbonFiber:
			Material.DisplayName = TEXT("Default Carbon Fiber");
			Material.WeaveScale = 1.0f;
			Material.WeaveAngle = 45.0f;
			Material.CarbonFiberGloss = 0.6f;
			break;

		case EMaterialType::Glass:
			Material.DisplayName = TEXT("Default Glass");
			Material.VisibleLightTransmission = 70.0f;
			Material.GlassTintColor = FLinearColor::White;
			break;

		default:
			Material.DisplayName = TEXT("Default Paint");
			break;
	}

	return Material;
}

FAutomotiveMaterial UAutomotiveMaterialLibrary::GetMaterialPreset(FName PresetName)
{
	FAutomotiveMaterial Material;

	if (PresetName == TEXT("Frozen_White"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::FrozenPaint);
		Material.MaterialID = TEXT("Frozen_White");
		Material.DisplayName = TEXT("Frozen White Pearl");
		Material.BaseColor = FLinearColor(0.98f, 0.98f, 0.98f);
		Material.MetallicIntensity = 0.95f;
		Material.PearlShiftIntensity = 0.9f;
		Material.PearlShiftColor = FLinearColor(0.9f, 0.95f, 1.0f);
		Material.Price = 2500.0f;
	}
	else if (PresetName == TEXT("Metallic_Black"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::MetallicPaint);
		Material.MaterialID = TEXT("Metallic_Black");
		Material.DisplayName = TEXT("Metallic Black");
		Material.BaseColor = FLinearColor(0.05f, 0.05f, 0.05f);
		Material.MetallicIntensity = 0.8f;
		Material.ClearCoatGlossiness = 0.85f;
		Material.Price = 1800.0f;
	}
	else if (PresetName == TEXT("Pearl_Blue"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::PearlPaint);
		Material.MaterialID = TEXT("Pearl_Blue");
		Material.DisplayName = TEXT("Pearl Blue");
		Material.BaseColor = FLinearColor(0.1f, 0.2f, 0.6f);
		Material.MetallicIntensity = 0.7f;
		Material.PearlShiftIntensity = 0.8f;
		Material.PearlShiftColor = FLinearColor(0.3f, 0.4f, 0.8f);
		Material.Price = 2200.0f;
	}
	else if (PresetName == TEXT("Ruby_Red"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::MetallicPaint);
		Material.MaterialID = TEXT("Ruby_Red");
		Material.DisplayName = TEXT("Ruby Red Metallic");
		Material.BaseColor = FLinearColor(0.8f, 0.1f, 0.1f);
		Material.MetallicIntensity = 0.9f;
		Material.ClearCoatGlossiness = 0.9f;
		Material.Price = 2000.0f;
	}
	else if (PresetName == TEXT("Carbon_Matte"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::CarbonFiber);
		Material.MaterialID = TEXT("Carbon_Matte");
		Material.DisplayName = TEXT("Carbon Fiber Matte");
		Material.WeaveAngle = 45.0f;
		Material.CarbonFiberGloss = 0.3f;
		Material.ResinTintIntensity = 0.2f;
		Material.Price = 3500.0f;
	}
	else if (PresetName == TEXT("Carbon_Gloss"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::CarbonFiber);
		Material.MaterialID = TEXT("Carbon_Gloss");
		Material.DisplayName = TEXT("Carbon Fiber Gloss");
		Material.WeaveAngle = 0.0f;
		Material.CarbonFiberGloss = 0.8f;
		Material.ResinTintIntensity = 0.4f;
		Material.Price = 3200.0f;
	}
	else if (PresetName == TEXT("Glass_Clear"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::Glass);
		Material.MaterialID = TEXT("Glass_Clear");
		Material.DisplayName = TEXT("Clear Glass");
		Material.VisibleLightTransmission = 85.0f;
		Material.FresnelEdgeDarkening = 0.2f;
		Material.Price = 800.0f;
	}
	else if (PresetName == TEXT("Glass_Tinted"))
	{
		Material = CreateDefaultAutomotiveMaterial(EMaterialType::Glass);
		Material.MaterialID = TEXT("Glass_Tinted");
		Material.DisplayName = TEXT("20% Tinted Glass");
		Material.VisibleLightTransmission = 20.0f;
		Material.GlassTintColor = FLinearColor(0.1f, 0.1f, 0.1f);
		Material.FresnelEdgeDarkening = 0.4f;
		Material.Price = 1200.0f;
	}

	return Material;
}

FAutomotiveMaterial UAutomotiveMaterialLibrary::ConvertLegacyPaintToAutomotive(const FPaintColor& LegacyPaint)
{
	FAutomotiveMaterial Material = CreateDefaultAutomotiveMaterial(EMaterialType::SolidPaint);
	
	// Copy basic properties
	Material.DisplayName = LegacyPaint.DisplayName;
	Material.MaterialID = LegacyPaint.PaintID;
	Material.Price = LegacyPaint.Price;
	Material.BaseMaterial = LegacyPaint.Material;
	
	// For legacy materials, set as solid paint with neutral parameters
	Material.MaterialType = EMaterialType::SolidPaint;
	Material.MetallicIntensity = 0.1f;
	Material.ClearCoatGlossiness = 0.7f;
	
	return Material;
}

bool UAutomotiveMaterialLibrary::IsMaterialTypeCompatible(EMaterialType MaterialType, const FString& UseCase)
{
	if (UseCase == TEXT("exterior_body"))
	{
		return MaterialType == EMaterialType::MetallicPaint || 
			   MaterialType == EMaterialType::PearlPaint || 
			   MaterialType == EMaterialType::FrozenPaint ||
			   MaterialType == EMaterialType::SolidPaint ||
			   MaterialType == EMaterialType::MattePaint;
	}
	else if (UseCase == TEXT("aero_parts"))
	{
		return MaterialType == EMaterialType::CarbonFiber ||
			   MaterialType == EMaterialType::MetallicPaint ||
			   MaterialType == EMaterialType::SolidPaint;
	}
	else if (UseCase == TEXT("windows"))
	{
		return MaterialType == EMaterialType::Glass;
	}
	
	return false;
}

FString UAutomotiveMaterialLibrary::GetMaterialTypeDisplayName(EMaterialType MaterialType)
{
	switch (MaterialType)
	{
		case EMaterialType::MetallicPaint:
			return TEXT("Metallic Paint");
		case EMaterialType::PearlPaint:
			return TEXT("Pearl Paint");
		case EMaterialType::FrozenPaint:
			return TEXT("Frozen Paint");
		case EMaterialType::CarbonFiber:
			return TEXT("Carbon Fiber");
		case EMaterialType::Glass:
			return TEXT("Glass with Ceramic Tint");
		case EMaterialType::SolidPaint:
			return TEXT("Solid Paint");
		case EMaterialType::MattePaint:
			return TEXT("Matte Paint");
		default:
			return TEXT("Unknown Material");
	}
}