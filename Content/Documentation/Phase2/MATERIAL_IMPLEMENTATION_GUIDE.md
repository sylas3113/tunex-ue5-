# PHASE 2: AUTOMOTIVE MATERIAL SYSTEM IMPLEMENTATION GUIDE

## Overview
This guide provides detailed instructions for implementing the Master Automotive Material system using UE5 Substrate workflow for TuneX Phase 2.

## 📁 Directory Structure Created
```
Content/
├── Materials/
│   ├── Master/                    # Master materials (M_Master_*)
│   ├── Instances/                 # Material instances
│   │   ├── Paint/               # Paint material instances
│   │   ├── CarbonFiber/         # Carbon fiber instances  
│   │   └── Glass/               # Glass material instances
│   ├── Functions/                # Material functions (MF_*)
│   ├── Collections/             # Material parameter collections
│   ├── Paint/                   # Paint-specific assets
│   ├── CarbonFiber/            # Carbon fiber assets
│   └── Glass/                  # Glass assets
├── Presets/                     # Material parameter presets
└── Documentation/Phase2/        # This documentation
```

## 🏗️ MASTER MATERIALS CREATION

### 1. M_Master_Automotive_Paint Material

**Material Settings:**
- Material Domain: Surface
- Shading Model: Substrate
- Blend Mode: Opaque
- Two Sided: False
- Use Emissive for Static Lighting: False
- Mask Clip Value: 0.333

**Material Graph Structure:**

**Layer 1: Primer**
- Node: Scalar Parameter "PrimerRoughness" (Default: 0.8)
- Connect to: Base Color → Roughness

**Layer 2: Base Color**
- Node: Vector Parameter "BaseColor" (Default: White)
- Node: Scalar Parameter "MetallicIntensity" (Default: 0.5, Range: 0-1)
- Node: Scalar Parameter "PearlShiftIntensity" (Default: 0.0, Range: 0-1)
- Node: Vector Parameter "PearlShiftColor" (Default: Silver)

**Base Color Graph Logic:**
```
BaseColor → Multiply by (1 + PearlShiftIntensity * Fresnel(PearlShiftColor))
MetallicIntensity → Multiply by Fresnel(0.04) for realistic metallic response
```

**Layer 3: Clear Coat**
- Node: Scalar Parameter "ClearCoatGlossiness" (Default: 0.9, Range: 0-1)
- Node: Scalar Parameter "ClearCoatRoughness" (Default: 0.1, Range: 0-1)
- Node: Scalar Parameter "RefractiveIndex" (Default: 1.5, Range: 1.3-1.6)

**Layer 4: Ceramic Coating**
- Node: Scalar Parameter "HydrophobicModifier" (Default: 0.7, Range: 0-1)
- Node: Scalar Parameter "DurabilityFactor" (Default: 0.8, Range: 0-1)

**Output Connections:**
- Base Color: Layer 2 output
- Metallic: MetallicIntensity
- Specular: 0.5 (physically accurate)
- Roughness: Layer 3 ClearCoatRoughness
- Clear Coat: ClearCoatGlossiness
- Clear Coat Roughness: Layer 3 output

### 2. M_Master_CarbonFiber Material

**Material Settings:**
- Material Domain: Surface
- Shading Model: Substrate
- Blend Mode: Opaque
- Use Parallax Occlusion Mapping: True

**Material Graph Structure:**

**Weave Texture Setup:**
- Texture Object: 4K Carbon Fiber Weave (T_CarbonFiber_Weave_4K)
- Normal Map: T_CarbonFiber_Normal_4K
- Parallax Occlusion Mapping: Height Map from weave texture

**Parameters:**
- Scalar Parameter "WeaveScale" (Default: 1.0, Range: 0.1-2.0)
- Scalar Parameter "WeaveAngle" (Default: 45.0, Range: 0-90)
- Scalar Parameter "ResinTintIntensity" (Default: 0.3, Range: 0-1)
- Scalar Parameter "CarbonFiberGloss" (Default: 0.6, Range: 0-1)

**Graph Logic:**
```
Weave Texture → Rotate UV by WeaveAngle → Scale by WeaveScale
Normal Map → World Space Normal for realistic reflections
ResinTint → Lerp(White, Black, ResinTintIntensity)
Gloss/Matte → CarbonFiberGloss
```

### 3. M_Master_Glass Material

**Material Settings:**
- Material Domain: Surface
- Shading Model: Substrate
- Blend Mode: Translucent
- Refraction Mode: Pixel Normal Offset
- Use Emissive for Static Lighting: False

**Material Graph Structure:**

**Physically Accurate Refraction:**
- Scalar Parameter "VisibleLightTransmission" (Default: 70.0, Range: 0-100)
- Vector Parameter "GlassTintColor" (Default: White)
- Scalar Parameter "FresnelEdgeDarkening" (Default: 0.3, Range: 0-1)
- Scalar Parameter "InteriorReflection" (Default: 0.5, Range: 0-1)

**IOR Calculation:**
```
Standard Automotive Glass IOR = 1.52
Transmission = VisibleLightTransmission / 100.0
Tint = GlassTintColor * Transmission
```

**Fresnel Edge Darkening:**
```
Edge Darkening = Fresnel(EdgeDarkeningFactor)
Final Color = Tint * (1 - Edge Darkening)
```

## 🎨 MATERIAL INSTANCES CREATION

### Paint Material Instances

**1. MI_Paint_Frozen_White**
- Parent: M_Master_Automotive_Paint
- Base Color: RGB(0.98, 0.98, 0.98)
- Metallic Intensity: 0.95
- Pearl Shift Intensity: 0.9
- Pearl Shift Color: RGB(0.9, 0.95, 1.0)
- Clear Coat Glossiness: 0.98
- Price: $2,500

**2. MI_Paint_Metallic_Black**
- Parent: M_Master_Automotive_Paint
- Base Color: RGB(0.05, 0.05, 0.05)
- Metallic Intensity: 0.8
- Clear Coat Glossiness: 0.85
- Price: $1,800

**3. MI_Paint_Pearl_Blue**
- Parent: M_Master_Automotive_Paint
- Base Color: RGB(0.1, 0.2, 0.6)
- Metallic Intensity: 0.7
- Pearl Shift Intensity: 0.8
- Pearl Shift Color: RGB(0.3, 0.4, 0.8)
- Price: $2,200

**4. MI_Paint_Ruby_Red**
- Parent: M_Master_Automotive_Paint
- Base Color: RGB(0.8, 0.1, 0.1)
- Metallic Intensity: 0.9
- Clear Coat Glossiness: 0.9
- Price: $2,000

### Carbon Fiber Material Instances

**5. MI_CarbonFiber_Matte**
- Parent: M_Master_CarbonFiber
- Weave Angle: 45°
- Carbon Fiber Gloss: 0.3
- Resin Tint Intensity: 0.2
- Price: $3,500

**6. MI_CarbonFiber_Gloss**
- Parent: M_Master_CarbonFiber
- Weave Angle: 0°
- Carbon Fiber Gloss: 0.8
- Resin Tint Intensity: 0.4
- Price: $3,200

### Glass Material Instances

**7. MI_Glass_Standard**
- Parent: M_Master_Glass
- Visible Light Transmission: 85%
- Fresnel Edge Darkening: 0.2
- Price: $800

**8. MI_Glass_Tinted_20**
- Parent: M_Master_Glass
- Visible Light Transmission: 20%
- Glass Tint Color: RGB(0.1, 0.1, 0.1)
- Fresnel Edge Darkening: 0.4
- Price: $1,200

## 🔧 MATERIAL PARAMETER COLLECTIONS

### MPC_LightingEnvironment
**Scalar Parameters:**
- GlobalLightIntensity (Default: 1.0, Range: 0.1-3.0)
- ColorTemperature (Default: 5600, Range: 2700-6500)
- LightDirection (Default: 45, Range: 0-360)
- AmbientContribution (Default: 0.3, Range: 0-1)
- HDRExposure (Default: 1.0, Range: 0.1-4.0)

### MPC_CameraSettings
**Scalar Parameters:**
- Aperture (Default: 8.0, Range: 1.4-22.0)
- ISO (Default: 400, Range: 100-3200)
- ShutterSpeed (Default: 0.01, Range: 0.00025-0.033)
- FocusDistance (Default: 500, Range: 50-2000)
- BokehIntensity (Default: 0.5, Range: 0-1)

## 📚 MATERIAL FUNCTIONS

### MF_PaintLayer
**Input Parameters:**
- BaseColor (Vector3)
- MetallicIntensity (Scalar)
- PearlShiftIntensity (Scalar)
- PearlShiftColor (Vector3)

**Output:**
- Final Base Color (Vector3)
- Metallic (Scalar)

### MF_ClearCoat
**Input Parameters:**
- Glossiness (Scalar)
- Roughness (Scalar)
- RefractiveIndex (Scalar)

**Output:**
- Clear Coat (Scalar)
- Clear Coat Roughness (Scalar)

### MF_CeramicCoating
**Input Parameters:**
- HydrophobicModifier (Scalar)
- DurabilityFactor (Scalar)

**Output:**
- Hydrophobic Factor (Scalar)
- Durability Factor (Scalar)

### MF_CarbonFiber
**Input Parameters:**
- WeaveScale (Scalar)
- WeaveAngle (Scalar)
- ResinTintIntensity (Scalar)
- Gloss (Scalar)

**Output:**
- Base Color (Vector3)
- Roughness (Scalar)
- Normal (Vector3)

### MF_Glass
**Input Parameters:**
- VisibleLightTransmission (Scalar)
- GlassTintColor (Vector3)
- FresnelEdgeDarkening (Scalar)
- InteriorReflection (Scalar)

**Output:**
- Transmission (Scalar)
- Tint (Vector3)
- Refraction (Vector3)

## 🔌 INTEGRATION WITH PHASE 1

### Data Asset Updates
Update your DA_BMW_G82_Config (or similar) to include advanced materials:

```cpp
// In your Data Asset
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paint")
TArray<FPaintColor> PaintColors;

// Each PaintColor now includes:
FPaintColor::bUseLegacyMaterial = false; // Use new system
FPaintColor::AdvancedMaterial = FAutomotiveMaterial{...}; // Full material data
```

### Blueprint Integration
The UVehicleMasterComponent now supports both legacy and advanced materials:

```cpp
// Legacy material (Phase 1 compatible)
PaintData.bUseLegacyMaterial = true;
PaintData.Material = LegacyMaterialAsset;

// Advanced material (Phase 2)
PaintData.bUseLegacyMaterial = false;
PaintData.AdvancedMaterial = AdvancedMaterialData;
```

## 🧪 TESTING PROCEDURES

### 1. Material Compilation Test
- Open each master material in Material Editor
- Verify no compilation errors
- Check Material Stats for performance impact
- Ensure Substrate workflow is active

### 2. Material Instance Test
- Create all 8 material instances
- Verify parameters display correctly in Details panel
- Test parameter ranges with extreme values
- Check real-time updates in viewport

### 3. Integration Test
- Create test vehicle with UVehicleMasterComponent
- Cycle through all paint options using SetPaintByIndex()
- Verify SetAdvancedPaint() works correctly
- Test keyboard controls (1/2/3, Q/W/E)

### 4. Visual Quality Test
- Setup studio lighting environment
- Test metallic flake response to light direction
- Verify pearl shift effect changes with viewing angle
- Check carbon fiber weave parallax mapping
- Test glass refraction and VLT adjustment

### 5. Performance Test
- Monitor GPU time in Stat Unit
- Check material complexity in Material Editor
- Verify no overdraw issues with translucent materials
- Test 4K texture performance impact

## 🎯 SUCCESS CRITERIA

✅ All 3 master materials compile without errors
✅ All 8 material instances display correct properties
✅ Frozen White paint shows proper iridescence
✅ Metallic flakes respond to light direction
✅ Carbon fiber shows weave parallax effect
✅ Glass VLT slider adjusts smoothly 0-100%
✅ Material parameter changes update in real-time
✅ No material compilation warnings
✅ Performance remains optimal (60 FPS target)
✅ Legacy Phase 1 materials still work

## 🚀 NEXT STEPS

After implementing the materials:

1. **Create Material Test Level** with 4 spheres showcasing each material type
2. **Add on-screen debug UI** for real-time parameter adjustment
3. **Implement livery customization** system using parameter presets
4. **Add wear/dirt layer system** for future enhancement
5. **Optimize textures** for 4K close-up detail shots

## 📖 TECHNICAL NOTES

### UE5 Substrate Workflow
- Always use Substrate shading model for new materials
- Leverage Substrate's built-in clear coat support
- Use physically-based parameters (IOR, roughness, metallic)
- Follow Disney PBR model for realistic results

### Performance Optimization
- Keep texture samples minimal (max 16 per material)
- Use material functions for reusable logic
- Optimize UV usage for texture efficiency
- Consider material complexity budget

### Texture Requirements
- **Paint Flakes**: 2K resolution minimum, 4K preferred
- **Carbon Fiber Weave**: 4K required for close-up detail
- **Normal Maps**: Use high-quality tangent space normals
- **Height Maps**: 16-bit precision for parallax mapping

This implementation guide provides the complete roadmap for Phase 2 automotive material system creation in UE5.