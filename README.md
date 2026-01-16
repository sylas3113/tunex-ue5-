# TuneX - Car Tuning Application

Build, tune, and customize your car like a pro. This app is your all-in-one platform for car tuning, performance upgrades, and visual modifications. Whether you're into street builds, track setups, stance culture, or daily performance, you can plan, track, and optimize every detail of your car in one place.

## Project Overview

TuneX is a production-grade Unreal Engine 5.3+ C++ application designed for car enthusiasts and professionals to visualize, plan, and customize vehicle builds with photorealistic quality.

### Engine Requirements
- **Unreal Engine 5.3+**
- **Platform**: Windows PC (Desktop / Maximum Quality)
- **Target**: High-end PC with GPU ray tracing support

### Key Features Enabled
- ✅ Nanite virtualized geometry
- ✅ Lumen global illumination with hardware ray tracing
- ✅ Hardware ray tracing support
- ✅ DLSS/FSR compatibility
- ✅ Blueprint-friendly C++ architecture

## Project Structure

```
TuneX/
├── Source/
│   └── TuneX/              # C++ game module
│       ├── TuneX.Build.cs  # Build configuration
│       ├── TuneX.h         # Module header
│       └── TuneX.cpp       # Module implementation
├── Content/
│   ├── Cars/               # Car definitions and variants
│   ├── Parts/              # Modular car parts
│   ├── Materials/          # Paint, metallic, carbon fiber, etc.
│   ├── Sounds/             # Engine, exhaust, audio systems
│   ├── UI/                 # Interface elements
│   ├── Systems/            # Core gameplay systems
│   ├── Data/               # Data tables, configs
│   └── Environments/       # Photo mode scenes, garages, studios
├── Config/
│   ├── DefaultEngine.ini   # Engine and renderer settings
│   └── DefaultGame.ini     # Game and user settings
├── TuneX.uproject          # UE5 project file
├── .gitignore              # UE5-specific ignore rules
└── .gitattributes          # Git LFS configuration
```

## Getting Started

### Prerequisites
1. Install Unreal Engine 5.3 or newer from Epic Games Launcher
2. Ensure your PC meets high-end requirements:
   - NVIDIA RTX 20-series or newer (or equivalent AMD GPU)
   - 16GB+ RAM recommended
   - SSD for optimal performance

### Opening the Project
1. Clone this repository
2. Double-click `TuneX.uproject` or right-click and select "Generate Visual Studio project files"
3. Open in Unreal Engine 5.3+
4. The project will automatically generate necessary binaries on first launch

### Building
```bash
# Generate project files (if needed)
"C:\Program Files\Epic Games\UE_5.3\Engine\Build\BatchFiles\Build.bat" TuneX Win64 Development

# Or use Unreal Editor: File > Refresh Visual Studio Project
```

### Quick Start for Phase 1 Vehicle System
1. **Create a vehicle configuration**: See `QUICK_START_GUIDE.md`
2. **Test key bindings**: 1/2/3 for bumpers, Q/W/E for paint
3. **Extend in Blueprint**: All C++ classes are Blueprint-friendly

**Controls** (in Play mode):
- `1`, `2`, `3` - Cycle bumper options
- `Q`, `W`, `E` - Cycle paint options

## Development

### C++ Module Structure
The project uses a clean module structure optimized for Blueprint integration:
- **TuneX module**: Main game module with core functionality
- **Blueprint-friendly**: All major classes marked with BlueprintType/Blueprintable
- **Performance-optimized**: C++ with exposed properties for Blueprint manipulation

### Rendering Settings
The project is configured for maximum visual quality:
- **Nanite**: Enabled for high-fidelity geometry
- **Lumen**: Hardware ray tracing enabled for realistic lighting
- **Anti-aliasing**: TAA/TSR (Temporal Super Resolution)
- **Screen percentage**: Configurable for DLSS/FSR integration

### Git Workflow
- Binary assets (*.uasset, *.umap) are tracked via Git LFS
- Build artifacts are excluded via .gitignore
- Use feature branches for new functionality
- Follow conventional commit messages

## Roadmap

### Phase 1: Foundation & Modular Car System ✅
- [x] UE5 5.3+ project setup
- [x] Rendering configuration (Nanite, Lumen, Ray Tracing)
- [x] Production folder structure
- [x] Version control with Git LFS
- [x] **Modular car data system** (BPC_Vehicle_Master, ST_CarPart)
- [x] **Part compatibility system** (FCarPart with CompatibilityTags)
- [x] **Car variant definitions** (UVehicleConfigDataAsset)
- [x] **Key-based cycling system** (BP_TuningController)
- [x] **Interface-driven communication** (I_VehicleModifier)

📖 **See**: `PHASE1_SUMMARY.md` and `QUICK_START_GUIDE.md`

### Phase 2: Substrate Materials & Advanced Rendering (Next)
- [ ] Substrate material system integration
- [ ] Advanced paint system (metallic, pearl, matte finishes)
- [ ] Dynamic lighting response
- [ ] Material parameter animations

### Phase 3: Core Systems
- [ ] Tuning interface
- [ ] Performance calculation
- [ ] Visual customization
- [ ] Save/load functionality

### Phase 4: Environments & Audio
- [ ] Photorealistic garage environments
- [ ] Engine sound system
- [ ] Audio reverb zones
- [ ] Photo mode

## Contributing

This project follows standard Unreal Engine development practices:
- Use C++ for performance-critical systems
- Expose gameplay logic to Blueprints for rapid iteration
- Maintain clean, modular architecture
- Follow Epic's coding standards

## License

[To be determined]

## Credits

Built with Unreal Engine 5.3+
