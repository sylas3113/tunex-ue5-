# TuneX Phase 1 Implementation Guide

## Overview
This document describes the Phase 1 implementation of the TuneX automotive configurator - a modular car system with key-based cycling.

## Architecture

### C++ Classes

#### 1. **FCarPart** (Struct in CarPartData.h)
Data structure for car parts with the following fields:
- `MeshAsset`: TSoftObjectPtr to Static/Skeletal Mesh
- `DisplayName`: String for UI display
- `Price`: Float for cost
- `CompatibilityTags`: Array of FNames for compatibility checking
- `MaterialOverrides`: Array of material references
- `SoundModifier`: Optional sound wave reference
- `PartID`: Unique identifier (FName)

#### 2. **FPaintColor** (Struct in CarPartData.h)
Data structure for paint colors:
- `DisplayName`: String for UI display
- `Material`: Material to apply
- `PaintID`: Unique identifier (FName)
- `Price`: Float for cost

#### 3. **UVehicleConfigDataAsset** (CarPartData.h)
Data Asset class that stores all configuration options for a vehicle:
- `FrontBumpers`: Array of FCarPart
- `RearBumpers`: Array of FCarPart
- `SideSkirts`: Array of FCarPart
- `Spoilers`: Array of FCarPart
- `Wheels`: Array of FCarPart
- `PaintColors`: Array of FPaintColor
- Default selection indices

#### 4. **IVehicleModifierInterface** (VehicleModifierInterface.h)
Interface for vehicle modification:
- `SetFrontBumper(FName BumperID)`: Set bumper by ID
- `SetRearBumper(FName BumperID)`: Set rear bumper by ID
- `SetPaint(FName PaintID)`: Set paint by ID
- `GetCurrentFrontBumper()`: Returns current bumper data
- `GetCurrentPaint()`: Returns current paint data
- `CycleNextFrontBumper()`: Cycle to next bumper
- `CycleNextPaint()`: Cycle to next paint

#### 5. **UVehicleMasterComponent** (VehicleMasterComponent.h/cpp)
Actor Component for managing vehicle configuration:
- Manages modular attachment points
- Handles dynamic material swaps
- Provides event dispatchers for UI binding
- Vehicle-agnostic design for reusability

Key Features:
- Auto-finds main vehicle mesh on BeginPlay
- Creates/manages bumper components dynamically
- Validates configuration before applying changes
- Broadcasts events on modification (OnBumperChanged, OnPaintChanged)

#### 6. **AVehicleActor** (VehicleActor.h/cpp)
Blueprint-friendly vehicle actor:
- Implements IVehicleModifierInterface
- Contains UStaticMeshComponent for chassis
- Contains UVehicleMasterComponent for configuration
- Event dispatcher for modification completion

#### 7. **ATuningController** (TuningController.h/cpp)
Player controller for tuning input:
- Handles keyboard input (1/2/3 for bumpers, Q/W/E for paint)
- Auto-finds vehicle with VehicleMasterComponent
- Logs feedback to console
- Blueprint-friendly

### Input Mappings (Config/DefaultInput.ini)

**Bumper Selection:**
- Key `1`: BumperOption1
- Key `2`: BumperOption2
- Key `3`: BumperOption3

**Paint Selection:**
- Key `Q`: PaintOption1
- Key `W`: PaintOption2
- Key `E`: PaintOption3

## Usage Guide

### Step 1: Create a Vehicle Config Data Asset

1. In Unreal Editor, create a new Data Asset of type `VehicleConfigDataAsset`
2. Name it `DA_BMW_G82_Config` (or any vehicle name)
3. Populate the arrays:
   - **FrontBumpers**: Add 3+ variants
     - Set DisplayName (e.g., "Standard", "M-Performance", "Vorsteiner GT")
     - Set PartID (e.g., "bmw_g82_bumper_standard")
     - Assign MeshAsset (Static Mesh reference)
     - Set Price
   - **PaintColors**: Add 3+ variants
     - Set DisplayName (e.g., "Metallic Blue", "Pearl White", "Frozen White")
     - Set PaintID (e.g., "paint_metallic_blue")
     - Assign Material
     - Set Price
4. Set default indices (typically 0 for all)

### Step 2: Create a Vehicle Blueprint

1. Create a new Blueprint based on `AVehicleActor` class
2. Name it `BP_BMW_G82` (or your vehicle name)
3. In the Blueprint:
   - Set the VehicleMesh to your chassis mesh
   - In VehicleMasterComponent properties:
     - Assign your `DA_BMW_G82_Config` data asset
     - Set socket names if using custom sockets (optional)
4. Place the vehicle in your level

### Step 3: Set Up the Player Controller

1. Create a Game Mode Blueprint
2. Set the Player Controller Class to `TuningController` (or create a BP based on it)
3. Alternatively, use the existing controller and it will auto-find the vehicle

### Step 4: Test in Play Mode

**Controls:**
- Press `1`, `2`, `3` to cycle through bumper options
- Press `Q`, `W`, `E` to cycle through paint options
- Check the Output Log for confirmation messages

**Expected Output:**
```
✓ Bumper changed to: Standard (Option 1)
✓ Bumper changed to: M-Performance (Option 2)
✓ Paint changed to: Metallic Blue (Option 1)
```

## Folder Structure

```
/Content/
  /Cars/
    /BMW_G82/                    # Vehicle-specific assets
      /Meshes/                   # Chassis and part meshes
      /Materials/                # Vehicle materials
      BP_BMW_G82.uasset         # Vehicle Blueprint
  /Core/
    /Systems/                    # Core systems (exposed from C++)
      BPC_VehicleMaster         # Vehicle Master Component
      I_VehicleModifier         # Interface Blueprint
    /Data/                       # Data structures
      DA_BMW_G82_Config         # BMW G82 configuration
  /UI/
    /Widgets/                    # Future WBP_TuningMenu
```

## Extension Points for Phase 2

The architecture is designed to be extensible:

1. **Material System**: The paint system uses TSoftObjectPtr, making it easy to swap to Substrate materials
2. **Socket System**: Socket names are configurable for any vehicle
3. **Event Dispatchers**: All modifications broadcast events for UI binding
4. **Component-Based**: Additional components can be added (wheels, spoilers, etc.)
5. **Interface-Based**: The interface can be extended for new modification types

## Debugging

### Common Issues

**"No target vehicle set!"**
- Solution: Ensure a vehicle with VehicleMasterComponent is in the level
- Check that bAutoFindVehicle is true in TuningController

**"Invalid front bumper index"**
- Solution: Ensure the Data Asset has at least 3 bumper entries
- Check that the index exists in the array

**"No VehicleConfig assigned!"**
- Solution: Assign the DA_BMW_G82_Config to the VehicleMasterComponent

**"No MainVehicleMesh found!"**
- Solution: Ensure the vehicle actor has a UStaticMeshComponent or USkeletalMeshComponent

### Console Commands

Enable verbose logging:
```
Log LogTemp Verbose
```

## Performance Considerations

- Meshes and materials use TSoftObjectPtr for lazy loading
- Components are created once and reused
- No tick functions enabled (performance-friendly)
- Async asset loading available (currently using synchronous for simplicity)

## Blueprint Extensibility

All C++ classes are marked with appropriate specifiers:
- `BlueprintType` for use in Blueprints
- `BlueprintCallable` for functions
- `BlueprintReadWrite` for properties
- `BlueprintAssignable` for events

You can extend any class in Blueprint and override behavior as needed.

## Testing Checklist

✓ Press '1' → cycles to bumper option 1
✓ Press '2' → cycles to bumper option 2
✓ Press '3' → cycles to bumper option 3
✓ Press 'Q' → cycles to paint color 1
✓ Press 'W' → cycles to paint color 2
✓ Press 'E' → cycles to paint color 3
✓ Vehicle mesh updates in real-time
✓ Console logs confirm each swap
✓ No crashes on invalid data access
✓ Auto-finding vehicle works
✓ Event dispatchers fire correctly

## Next Steps

For Phase 2, you can:
1. Implement Substrate materials for advanced rendering
2. Add socket-based attachment visualization
3. Create WBP_TuningMenu UI widget
4. Add wheel/spoiler/side skirt support
5. Implement sound system integration
6. Add save/load configuration
7. Network replication for multiplayer

---

**Note**: This is a foundation phase focusing on modular architecture and clean code design. Visual perfection and advanced features will come in subsequent phases.
