# BMW G82 Vehicle Assets

This folder contains all assets specific to the BMW G82 M4.

## Folder Structure

```
BMW_G82/
  ├── Meshes/              # All mesh assets
  │   ├── Chassis/         # Main vehicle body
  │   ├── Bumpers/         # Front and rear bumpers
  │   ├── Wheels/          # Wheel variants
  │   └── Aero/            # Aerodynamic parts (spoilers, splitters)
  ├── Materials/           # Vehicle-specific materials
  │   ├── Paint/           # Paint materials
  │   ├── Chrome/          # Chrome and metal finishes
  │   └── Glass/           # Window and light materials
  ├── Textures/            # Texture assets
  └── BP_BMW_G82.uasset    # Main vehicle Blueprint
```

## Creating the Vehicle Blueprint

1. Right-click in this folder
2. Blueprint Class → Search for "VehicleActor"
3. Name it "BP_BMW_G82"

### Setting up BP_BMW_G82

1. Open the Blueprint
2. Select the **VehicleMesh** component
   - Assign the chassis mesh (e.g., SM_BMW_G82_Chassis)
3. Select the **VehicleMasterComponent**
   - Assign the Data Asset: `DA_BMW_G82_Config`
   - (Optional) Configure socket names if using custom sockets
4. Compile and Save

## Asset Naming Conventions

### Meshes
- Chassis: `SM_BMW_G82_Chassis`
- Bumpers: `SM_BMW_G82_Bumper_[Variant]`
  - Example: `SM_BMW_G82_Bumper_Standard`
  - Example: `SM_BMW_G82_Bumper_MPerformance`
- Wheels: `SM_BMW_G82_Wheel_[Size]_[Style]`
  - Example: `SM_BMW_G82_Wheel_19_Standard`

### Materials
- Paint: `M_BMW_G82_Paint_[Color]`
  - Example: `M_BMW_G82_Paint_MetallicBlue`
- Material Instances: `MI_BMW_G82_Paint_[Color]`

## Testing

1. Place BP_BMW_G82 in your level
2. Ensure your Game Mode uses the TuningController
3. Play and use keys 1/2/3 for bumpers, Q/W/E for paint

## Notes

- All meshes should be optimized for real-time rendering
- Use LODs for better performance
- Material instances are preferred over base materials for easy tweaking
