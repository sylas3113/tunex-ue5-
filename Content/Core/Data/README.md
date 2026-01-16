# Core Data

This folder contains Data Assets and data structures for vehicle configuration.

## Creating a Vehicle Config Data Asset

1. Right-click in Content Browser
2. Miscellaneous → Data Asset
3. Select "VehicleConfigDataAsset"
4. Name it following the pattern: `DA_[VehicleName]_Config`
   - Example: `DA_BMW_G82_Config`

## Populating the Data Asset

### Front Bumpers Array

For each bumper variant:
- **Display Name**: User-friendly name (e.g., "M-Performance")
- **Part ID**: Unique identifier (e.g., "bmw_g82_bumper_m_performance")
- **Mesh Asset**: Reference to Static Mesh
- **Price**: Cost in game currency
- **Compatibility Tags**: Array of tags (e.g., "BMW_G82", "Front_Bumper")
- **Material Overrides**: Optional array of materials for this part
- **Sound Modifier**: Optional sound wave

### Paint Colors Array

For each paint option:
- **Display Name**: User-friendly name (e.g., "Metallic Blue")
- **Paint ID**: Unique identifier (e.g., "paint_metallic_blue")
- **Material**: Material instance to apply
- **Price**: Cost in game currency

### Default Indices

Set the default selections:
- **Default Front Bumper Index**: Typically 0 (first option)
- **Default Rear Bumper Index**: Typically 0
- **Default Paint Index**: Typically 0

## Example Configuration

```
DA_BMW_G82_Config:
  Front Bumpers:
    [0] Standard (bmw_g82_bumper_standard)
    [1] M-Performance (bmw_g82_bumper_m_performance)
    [2] Vorsteiner GT (bmw_g82_bumper_vorsteiner_gt)
  
  Paint Colors:
    [0] Metallic Blue (paint_metallic_blue)
    [1] Pearl White (paint_pearl_white)
    [2] Frozen White (paint_frozen_white)
  
  Default Indices: 0, 0, 0
```
