# Core Systems

This folder contains core Blueprint Classes exposed from C++ that are vehicle-agnostic.

## Contents

- **BPC_VehicleMaster**: Blueprint Component for Vehicle Master (based on UVehicleMasterComponent)
- **I_VehicleModifier**: Interface Blueprint (based on IVehicleModifierInterface)

## Usage

These are exposed from C++ and can be used directly or extended in Blueprint.

### Creating a Vehicle Master Component Blueprint

While you can use the C++ component directly, you can also create a Blueprint Component:

1. Right-click in Content Browser
2. Blueprint Class → Search for "VehicleMasterComponent"
3. Name it "BPC_VehicleMaster"
4. Add additional Blueprint logic as needed

### Using the Interface

The interface is automatically available in Blueprint. To implement it:

1. Open your vehicle Blueprint
2. Class Settings → Implemented Interfaces
3. Add "VehicleModifierInterface"
4. Implement the interface functions
