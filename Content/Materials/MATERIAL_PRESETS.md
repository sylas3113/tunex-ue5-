# Automotive Material Presets for Phase 2

This file contains the parameter values for all 8 required material instances. Use these values when creating the material instances in Unreal Engine Editor.

## Paint Material Instances

### MI_Paint_Frozen_White
**Parent Material:** M_Master_Automotive_Paint
**Material Type:** FrozenPaint
**Base Color:** RGB(0.98, 0.98, 0.98)
**Metallic Intensity:** 0.95
**Pearl Shift Intensity:** 0.9
**Pearl Shift Color:** RGB(0.9, 0.95, 1.0)
**Clear Coat Glossiness:** 0.98
**Clear Coat Roughness:** 0.05
**Price:** $2,500

### MI_Paint_Metallic_Black
**Parent Material:** M_Master_Automotive_Paint
**Material Type:** MetallicPaint
**Base Color:** RGB(0.05, 0.05, 0.05)
**Metallic Intensity:** 0.8
**Clear Coat Glossiness:** 0.85
**Clear Coat Roughness:** 0.15
**Price:** $1,800

### MI_Paint_Pearl_Blue
**Parent Material:** M_Master_Automotive_Paint
**Material Type:** PearlPaint
**Base Color:** RGB(0.1, 0.2, 0.6)
**Metallic Intensity:** 0.7
**Pearl Shift Intensity:** 0.8
**Pearl Shift Color:** RGB(0.3, 0.4, 0.8)
**Clear Coat Glossiness:** 0.92
**Price:** $2,200

### MI_Paint_Ruby_Red
**Parent Material:** M_Master_Automotive_Paint
**Material Type:** MetallicPaint
**Base Color:** RGB(0.8, 0.1, 0.1)
**Metallic Intensity:** 0.9
**Clear Coat Glossiness:** 0.9
**Price:** $2,000

## Carbon Fiber Material Instances

### MI_CarbonFiber_Matte
**Parent Material:** M_Master_CarbonFiber
**Material Type:** CarbonFiber
**Weave Scale:** 1.0
**Weave Angle:** 45.0 degrees
**Resin Tint Intensity:** 0.2
**Carbon Fiber Gloss:** 0.3
**Price:** $3,500

### MI_CarbonFiber_Gloss
**Parent Material:** M_Master_CarbonFiber
**Material Type:** CarbonFiber
**Weave Scale:** 1.0
**Weave Angle:** 0.0 degrees
**Resin Tint Intensity:** 0.4
**Carbon Fiber Gloss:** 0.8
**Price:** $3,200

## Glass Material Instances

### MI_Glass_Standard
**Parent Material:** M_Master_Glass
**Material Type:** Glass
**Visible Light Transmission:** 85.0%
**Glass Tint Color:** RGB(1.0, 1.0, 1.0)
**Fresnel Edge Darkening:** 0.2
**Interior Reflection:** 0.5
**Price:** $800

### MI_Glass_Tinted_20
**Parent Material:** M_Master_Glass
**Material Type:** Glass
**Visible Light Transmission:** 20.0%
**Glass Tint Color:** RGB(0.1, 0.1, 0.1)
**Fresnel Edge Darkening:** 0.4
**Interior Reflection:** 0.6
**Price:** $1,200

## Material Parameter Collections

### MPC_LightingEnvironment
**Scalar Parameters:**
- GlobalLightIntensity: 1.2
- ColorTemperature: 5600.0
- LightDirection: 45.0
- AmbientContribution: 0.3
- HDRExposure: 1.1

### MPC_CameraSettings
**Scalar Parameters:**
- Aperture: 5.6
- ISO: 200.0
- ShutterSpeed: 0.01
- FocusDistance: 500.0
- BokehIntensity: 0.3

## Texture Requirements

### Required Textures
- **T_CarbonFiber_Weave_4K** (4K carbon fiber weave texture)
- **T_CarbonFiber_Normal_4K** (4K normal map for carbon fiber)
- **T_Paint_Flake_2K** (2K metallic flake texture for paint)
- **T_Paint_Pearl_2K** (2K pearl shift texture)

### Texture Settings
- **Compression:** TC Default
- **sRGB:** True (for color textures), False (for normal/height maps)
- **Alpha:** No Alpha
- **Mip Gen Settings:** From Texture Group
- **LOD Group:** World

## Material Editor Settings

### Common Settings for All Master Materials
- **Material Domain:** Surface
- **Shading Model:** Substrate
- **Use Emissive for Static Lighting:** False
- **Two Sided:** False

### Paint Material Specific
- **Blend Mode:** Opaque
- **Mask Clip Value:** 0.333

### Carbon Fiber Material Specific
- **Blend Mode:** Opaque
- **Use Parallax Occlusion Mapping:** True

### Glass Material Specific
- **Blend Mode:** Translucent
- **Refraction Mode:** Pixel Normal Offset
- **Shading Model:** Default Lit (for glass)

## Performance Settings

### Texture Streaming
- **Streaming Distance Multiplier:** 1.0
- **Never Stream:** False
- **LOD Bias:** 0

### Material Complexity
- **Mobile:** Unlit materials only when possible
- **Desktop:** Full Substrate complexity allowed
- **Console:** Optimize texture sampling

This preset file provides all necessary values for creating the Phase 2 automotive material system in Unreal Engine Editor.