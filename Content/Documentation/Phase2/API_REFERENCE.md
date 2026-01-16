# Phase 2: Automotive Material System API Reference

## Core Classes

### FAutomotiveMaterial
The main data structure for automotive material properties.

```cpp
// Material Type Classification
EMaterialType MaterialType; // MetallicPaint, PearlPaint, FrozenPaint, CarbonFiber, Glass

// Base Properties
FString DisplayName;
FName MaterialID;
float Price;
TSoftObjectPtr<UMaterialInterface> BaseMaterial;

// Layer 1: Primer
float PrimerRoughness; // 0.0-1.0, Default: 0.8

// Layer 2: Base Color
FLinearColor BaseColor;
float MetallicIntensity; // 0.0-1.0
float PearlShiftIntensity; // 0.0-1.0
FLinearColor PearlShiftColor;

// Layer 3: Clear Coat
float ClearCoatGlossiness; // 0.0-1.0
float ClearCoatRoughness; // 0.0-1.0
float RefractiveIndex; // 1.3-1.6

// Layer 4: Ceramic Coating
bool bEnableCeramicCoating;
float HydrophobicModifier; // 0.0-1.0
float DurabilityFactor; // 0.0-1.0

// Carbon Fiber Specific
float WeaveScale; // 0.1-2.0
float WeaveAngle; // 0.0-90.0 degrees
float ResinTintIntensity; // 0.0-1.0
float CarbonFiberGloss; // 0.0-1.0

// Glass Specific
float VisibleLightTransmission; // 0.0-100.0 %
FLinearColor GlassTintColor;
float FresnelEdgeDarkening; // 0.0-1.0
float InteriorReflection; // 0.0-1.0
```

### UAutomotiveMaterialSystem
Core manager for material operations.

#### Key Methods

```cpp
// Update mesh with material parameters
void UpdateMeshMaterialParameters(UMeshComponent* MeshComponent, const FAutomotiveMaterial& MaterialData, bool bForceUpdate = false);

// Create material instance from data
UMaterialInstance* CreateMaterialInstance(const FAutomotiveMaterial& MaterialData);

// Apply paint to mesh (legacy + advanced support)
void ApplyAdvancedPaint(UMeshComponent* MeshComponent, const FPaintColor& PaintData);

// Global lighting control
void UpdateGlobalLighting(UObject* WorldContext, const UGlobalLightingParameters& LightingParams);

// Camera settings for cinematic visualization
void UpdateCameraSettings(UObject* WorldContext, const UCameraSettings& CameraSettings);

// Validation and debugging
bool ValidateMaterialParameters(const FAutomotiveMaterial& MaterialData) const;
FString GetMaterialDebugInfo(const FAutomotiveMaterial& MaterialData) const;
```

### UVehicleMasterComponent Extensions

#### New Methods for Phase 2

```cpp
// Set advanced paint with full material properties
bool SetAdvancedPaint(const FAutomotiveMaterial& MaterialData);

// Get current automotive material
FAutomotiveMaterial GetCurrentAutomotiveMaterial() const;

// Real-time parameter updates
void UpdateMaterialParameters(const FAutomotiveMaterial& MaterialData, bool bForceUpdate = false);

// Global lighting and camera control
void UpdateGlobalLightingSettings(const UGlobalLightingParameters& LightingParams);
void UpdateCameraSettings(const UCameraSettings& CameraParams);
```

## Material Presets

### Available Presets

| Preset Name | Material Type | Description | Price |
|-------------|--------------|-------------|-------|
| `Frozen_White` | FrozenPaint | Premium pearl white with iridescence | $2,500 |
| `Metallic_Black` | MetallicPaint | Deep black with metallic flakes | $1,800 |
| `Pearl_Blue` | PearlPaint | Blue with pearl shift effect | $2,200 |
| `Ruby_Red` | MetallicPaint | Red with high reflectivity | $2,000 |
| `Carbon_Matte` | CarbonFiber | Matte finish, 45° weave | $3,500 |
| `Carbon_Gloss` | CarbonFiber | Gloss finish, 0° weave | $3,200 |
| `Glass_Clear` | Glass | Standard clear glass (85% VLT) | $800 |
| `Glass_Tinted` | Glass | 20% VLT tinted glass | $1,200 |

### Creating Custom Presets

```cpp
// Using the library functions
FAutomotiveMaterial CustomPaint = UAutomotiveMaterialLibrary::GetMaterialPreset(TEXT("Frozen_White"));

// Customize the preset
CustomPaint.DisplayName = TEXT("Custom Frozen White");
CustomPaint.Price = 3000.0f;
CustomPaint.MetallicIntensity = 1.0f; // Maximum metallic

// Create from scratch
FAutomotiveMaterial CustomMaterial = UAutomotiveMaterialLibrary::CreateDefaultAutomotiveMaterial(EMaterialType::PearlPaint);
CustomMaterial.BaseColor = FLinearColor(0.2f, 0.8f, 0.4f); // Custom green
CustomMaterial.PearlShiftColor = FLinearColor(0.3f, 0.9f, 0.5f);
```

## Integration Examples

### Data Asset Configuration

```cpp
// In your UVehicleConfigDataAsset-derived class
void SetupBMW_G82_AdvancedPaint()
{
    // Frozen White Paint
    FPaintColor FrozenWhite;
    FrozenWhite.DisplayName = TEXT("Frozen White Pearl");
    FrozenWhite.PaintID = TEXT("Frozen_White");
    FrozenWhite.Price = 2500.0f;
    FrozenWhite.bUseLegacyMaterial = false; // Use Phase 2 system
    
    FAutomotiveMaterial& FrozenWhiteMat = FrozenWhite.AdvancedMaterial;
    FrozenWhiteMat = UAutomotiveMaterialLibrary::GetMaterialPreset(TEXT("Frozen_White"));
    FrozenWhiteMat.BaseMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Instances/Paint/MI_Paint_Frozen_White.MI_Paint_Frozen_White"));
    
    PaintColors.Add(FrozenWhite);
    
    // Add other paint options...
}
```

### Blueprint Integration

```cpp
// Vehicle Blueprint Event Graph
Event BeginPlay
├─ Initialize Vehicle (UVehicleMasterComponent)
└─ Setup Cinematic Camera

Event Key Press 1 (Cycle Paint)
├─ Get Vehicle Master Component
├─ Cycle Next Paint
└─ Update Material Debug UI

Event Key Press Q (Toggle Lighting)
├─ Get Global Lighting Parameters
├─ Adjust Light Intensity
└─ Update MPC via Material System

Custom Event: Update Material Parameters
├─ Get Current Material Data
├─ Adjust Metallic Intensity
├─ Update Material System
└─ Update Debug Display
```

### Material Instance Creation

```cpp
// Runtime material instance creation
UMaterialInstance* CreateCustomMaterialInstance(UObject* WorldContext, const FAutomotiveMaterial& MaterialData)
{
    if (!MaterialData.BaseMaterial.IsValid())
    {
        return nullptr;
    }
    
    UAutomotiveMaterialSystem* MaterialSystem = GetMaterialSystem(WorldContext);
    if (!MaterialSystem)
    {
        return nullptr;
    }
    
    UMaterialInstance* MaterialInstance = MaterialSystem->CreateMaterialInstance(MaterialData);
    
    // Apply additional runtime modifications
    MaterialInstance->SetScalarParameterValue(TEXT("RuntimeGlossModifier"), 1.2f);
    
    return MaterialInstance;
}
```

## Error Handling and Validation

### Material Validation

```cpp
bool ValidateAutomotiveMaterial(const FAutomotiveMaterial& Material)
{
    // Check basic properties
    if (Material.Price < 0.0f)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid material price: %f"), Material.Price);
        return false;
    }
    
    // Validate range-based parameters
    if (Material.MetallicIntensity < 0.0f || Material.MetallicIntensity > 1.0f)
    {
        UE_LOG(LogTemp, Error, TEXT("Metallic intensity out of range: %f"), Material.MetallicIntensity);
        return false;
    }
    
    // Type-specific validation
    switch (Material.MaterialType)
    {
        case EMaterialType::CarbonFiber:
            if (Material.WeaveAngle < 0.0f || Material.WeaveAngle > 90.0f)
            {
                UE_LOG(LogTemp, Error, TEXT("Invalid carbon fiber weave angle: %f"), Material.WeaveAngle);
                return false;
            }
            break;
            
        case EMaterialType::Glass:
            if (Material.VisibleLightTransmission < 0.0f || Material.VisibleLightTransmission > 100.0f)
            {
                UE_LOG(LogTemp, Error, TEXT("Invalid glass VLT: %f"), Material.VisibleLightTransmission);
                return false;
            }
            break;
    }
    
    return true;
}
```

### Debug Information

```cpp
// Get detailed material information for debugging
FString GetMaterialDebugString(const FAutomotiveMaterial& Material)
{
    UAutomotiveMaterialSystem* System = GetMaterialSystem();
    if (System)
    {
        return System->GetMaterialDebugInfo(Material);
    }
    
    return FString::Printf(TEXT("Material: %s\nType: %s\nPrice: $%.2f"), 
        *Material.DisplayName, 
        *UAutomotiveMaterialLibrary::GetMaterialTypeDisplayName(Material.MaterialType),
        Material.Price);
}
```

## Performance Considerations

### Material Complexity Budget
- **Maximum Texture Samples**: 16 per material
- **Maximum Instructions**: 512 for mobile, 1024 for desktop
- **Maximum Texture Lookups**: 8 per material

### Optimization Tips
1. **Use Material Functions**: Reuse common calculations
2. **Leverage MPCs**: Share parameters across materials
3. **Texture Atlasing**: Combine related textures
4. **LOD for Materials**: Different complexity for distance

### Monitoring Performance
```cpp
// In material debug mode
void LogMaterialPerformance(UMaterialInterface* Material)
{
    if (!Material)
        return;
        
    // Check material stats (requires Material Editor access)
    FMaterialResource* Resource = Material->GetMaterialResource();
    if (Resource)
    {
        int32 InstructionCount = Resource->GetNumInstructions();
        int32 TextureCount = Resource->GetTextureCount();
        
        UE_LOG(LogTemp, Log, TEXT("Material %s: %d instructions, %d textures"), 
            *Material->GetName(), InstructionCount, TextureCount);
    }
}
```

This API reference provides comprehensive documentation for integrating with the Phase 2 automotive material system.