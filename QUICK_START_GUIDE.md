# TuneX Phase 1 - Quick Start Guide

## For Artists & Designers (Non-Programmers)

This guide will help you set up a new vehicle in TuneX without touching any C++ code.

---

## Step 1: Prepare Your Assets

Before you start, make sure you have:

### Required Assets:
- ✅ **Chassis Mesh** - Main car body (Static or Skeletal Mesh)
- ✅ **Bumper Meshes** - At least 3 bumper variants (Static Meshes)
- ✅ **Paint Materials** - At least 3 material instances

### Recommended Naming:
```
SM_BMW_G82_Chassis          # Main body
SM_BMW_G82_Bumper_Standard  # Bumper variant 1
SM_BMW_G82_Bumper_MSport    # Bumper variant 2
SM_BMW_G82_Bumper_VGT       # Bumper variant 3

MI_Paint_Blue_Metallic      # Paint material 1
MI_Paint_White_Pearl        # Paint material 2
MI_Paint_White_Frozen       # Paint material 3
```

---

## Step 2: Create the Configuration Data Asset

1. **Navigate to Content/Core/Data/**

2. **Right-click** in the Content Browser
   - Select: **Miscellaneous → Data Asset**

3. **Choose**: `VehicleConfigDataAsset`

4. **Name it**: `DA_BMW_G82_Config`
   - (Replace BMW_G82 with your vehicle name)

5. **Open the Data Asset** and fill in the following:

### Front Bumpers Section:

Click the **+** button to add 3 bumper entries:

**Bumper 0 (Standard):**
- Display Name: `Standard`
- Part ID: `bmw_g82_bumper_standard`
- Mesh Asset: Select `SM_BMW_G82_Bumper_Standard`
- Price: `0` (base option)
- Compatibility Tags: Add tag `BMW_G82`

**Bumper 1 (M-Performance):**
- Display Name: `M-Performance`
- Part ID: `bmw_g82_bumper_m_performance`
- Mesh Asset: Select `SM_BMW_G82_Bumper_MSport`
- Price: `5000`
- Compatibility Tags: Add tag `BMW_G82`

**Bumper 2 (Vorsteiner GT):**
- Display Name: `Vorsteiner GT`
- Part ID: `bmw_g82_bumper_vorsteiner_gt`
- Mesh Asset: Select `SM_BMW_G82_Bumper_VGT`
- Price: `12000`
- Compatibility Tags: Add tag `BMW_G82`

### Paint Colors Section:

Click the **+** button to add 3 paint entries:

**Paint 0 (Blue Metallic):**
- Display Name: `Blue Metallic`
- Paint ID: `paint_blue_metallic`
- Material: Select `MI_Paint_Blue_Metallic`
- Price: `0`

**Paint 1 (Pearl White):**
- Display Name: `Pearl White`
- Paint ID: `paint_white_pearl`
- Material: Select `MI_Paint_White_Pearl`
- Price: `2500`

**Paint 2 (Frozen White):**
- Display Name: `Frozen White`
- Paint ID: `paint_white_frozen`
- Material: Select `MI_Paint_White_Frozen`
- Price: `8000`

### Default Indices:
- Default Front Bumper Index: `0`
- Default Rear Bumper Index: `0`
- Default Paint Index: `0`

6. **Save** the Data Asset

---

## Step 3: Create the Vehicle Blueprint

1. **Navigate to Content/Cars/BMW_G82/**

2. **Right-click** in the Content Browser
   - Select: **Blueprint Class**

3. **Search for**: `VehicleActor`
   - Select it from the list

4. **Name it**: `BP_BMW_G82`

5. **Open the Blueprint**

### Configure the Vehicle Mesh:

1. Click on **VehicleMesh** in the Components panel
2. In Details panel:
   - **Static Mesh**: Select `SM_BMW_G82_Chassis`
   - Set **Location**: (0, 0, 0)
   - Set **Rotation**: (0, 0, 0)
   - Set **Scale**: (1, 1, 1)

### Configure the Vehicle Master Component:

1. Click on **VehicleMasterComponent** in the Components panel
2. In Details panel under **Vehicle Configuration**:
   - **Vehicle Config**: Select `DA_BMW_G82_Config`
   - **Main Vehicle Mesh**: Should auto-populate (or select VehicleMesh)

3. (Optional) Under **Vehicle Configuration → Sockets**:
   - **Front Bumper Socket Name**: `FrontBumperSocket` (default)
   - **Rear Bumper Socket Name**: `RearBumperSocket` (default)

4. **Compile** and **Save**

---

## Step 4: Set Up the Level

1. **Drag** `BP_BMW_G82` into your level

2. **Position** the vehicle where you want it

3. **World Settings**:
   - Open: **Window → World Settings**
   - Under **Game Mode**:
     - **Game Mode Override**: Select or create a Game Mode
     - **Player Controller Class**: Set to `TuningController`

4. **Save** the level

---

## Step 5: Test!

1. **Press Play** (Alt+P or the Play button)

2. **Use the following keys**:
   - `1` = Switch to Bumper Option 1 (Standard)
   - `2` = Switch to Bumper Option 2 (M-Performance)
   - `3` = Switch to Bumper Option 3 (Vorsteiner GT)
   - `Q` = Switch to Paint Option 1 (Blue Metallic)
   - `W` = Switch to Paint Option 2 (Pearl White)
   - `E` = Switch to Paint Option 3 (Frozen White)

3. **Check the Output Log**:
   - Open: **Window → Developer Tools → Output Log**
   - You should see messages like:
     ```
     ✓ Bumper changed to: M-Performance (Option 2)
     ✓ Paint changed to: Pearl White (Option 2)
     ```

---

## Troubleshooting

### "No target vehicle set!"
**Problem**: The controller can't find your vehicle.

**Solution**:
- Make sure `BP_BMW_G82` is placed in the level
- Check that the Game Mode is using `TuningController`
- Ensure `bAutoFindVehicle` is checked in the controller

---

### "Invalid front bumper index"
**Problem**: Not enough bumper options in the data asset.

**Solution**:
- Open `DA_BMW_G82_Config`
- Make sure you have at least 3 entries in the Front Bumpers array
- Save the data asset and try again

---

### "No VehicleConfig assigned!"
**Problem**: The data asset isn't linked to the vehicle.

**Solution**:
- Open `BP_BMW_G82`
- Click on `VehicleMasterComponent`
- In Details, set **Vehicle Config** to `DA_BMW_G82_Config`
- Compile and Save

---

### Bumper doesn't appear
**Problem**: The mesh isn't loading or attaching.

**Solution**:
- Check that the mesh asset is assigned in the data asset
- Make sure the mesh is a valid Static Mesh (not a Skeletal Mesh, unless you modify the code)
- Check the Output Log for errors

---

### Paint doesn't change
**Problem**: Material isn't being applied.

**Solution**:
- Check that the material is assigned in the data asset
- Make sure it's a Material or Material Instance (not a texture)
- Verify the VehicleMesh has material slots to override

---

## Advanced: Adding More Options

### Add a 4th Bumper:
1. Open `DA_BMW_G82_Config`
2. In Front Bumpers, click **+** to add a new entry
3. Fill in the details
4. Save
5. In-game, you can access it by implementing custom UI or cycling

### Add More Paint Colors:
1. Open `DA_BMW_G82_Config`
2. In Paint Colors, click **+** to add a new entry
3. Fill in the details
4. Save

### Add Socket-Based Attachment:
1. Open your chassis mesh in the Static Mesh Editor
2. Add sockets at attachment points:
   - `FrontBumperSocket` - Front bumper location
   - `RearBumperSocket` - Rear bumper location
3. Position and rotate the sockets
4. Save the mesh
5. Bumpers will now attach to these sockets automatically

---

## Tips for Best Results

✅ **Naming Conventions**: Use consistent naming for easy organization

✅ **LODs**: Create LODs for meshes to improve performance

✅ **Material Instances**: Use Material Instances instead of base materials for easy color tweaking

✅ **Pivot Points**: Make sure mesh pivot points are correct for proper alignment

✅ **Scale**: Keep consistent scale across all parts (usually 1:1)

✅ **Collision**: Disable collision on decorative parts if not needed

✅ **Testing**: Test each part individually before adding more

---

## Next Steps

Once you have the basic system working:

1. **Add More Vehicles**: Create new data assets and blueprints for other cars
2. **Add More Parts**: Extend the system with wheels, spoilers, etc.
3. **Create UI**: Build a proper menu widget for part selection
4. **Add Sounds**: Assign sound modifiers to parts (exhaust notes, etc.)
5. **Save System**: Implement configuration saving/loading

---

## Need Help?

- Check `PHASE1_IMPLEMENTATION.md` for technical details
- Check `PHASE1_SUMMARY.md` for architecture overview
- Check folder README.md files for specific guidance
- Check the Output Log for error messages

---

**You're all set! Happy tuning! 🏎️**
