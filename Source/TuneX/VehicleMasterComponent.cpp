// Copyright TuneX Project. All Rights Reserved.

#include "VehicleMasterComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

UVehicleMasterComponent::UVehicleMasterComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    CurrentFrontBumperIndex = 0;
    CurrentRearBumperIndex = 0;
    CurrentPaintIndex = 0;

    FrontBumperSocketName = FName("FrontBumperSocket");
    RearBumperSocketName = FName("RearBumperSocket");

    FrontBumperComponent = nullptr;
    RearBumperComponent = nullptr;
    MainVehicleMesh = nullptr;
}

void UVehicleMasterComponent::BeginPlay()
{
    Super::BeginPlay();

    // Auto-find the main vehicle mesh if not set
    if (!MainVehicleMesh)
    {
        AActor* Owner = GetOwner();
        if (Owner)
        {
            // Try skeletal mesh first (for animated vehicles)
            MainVehicleMesh = Owner->FindComponentByClass<USkeletalMeshComponent>();
            
            // Fall back to static mesh
            if (!MainVehicleMesh)
            {
                MainVehicleMesh = Owner->FindComponentByClass<UStaticMeshComponent>();
            }
        }
    }

    InitializeVehicle();
}

void UVehicleMasterComponent::InitializeVehicle()
{
    if (!ValidateConfiguration())
    {
        UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Invalid configuration, skipping initialization"));
        return;
    }

    // Set default bumpers
    if (VehicleConfig->FrontBumpers.Num() > 0)
    {
        SetFrontBumperByIndex(VehicleConfig->DefaultFrontBumperIndex);
    }

    // Set default paint
    if (VehicleConfig->PaintColors.Num() > 0)
    {
        SetPaintByIndex(VehicleConfig->DefaultPaintIndex);
    }

    UE_LOG(LogTemp, Log, TEXT("VehicleMasterComponent: Vehicle initialized successfully"));
}

bool UVehicleMasterComponent::ValidateConfiguration() const
{
    if (!VehicleConfig)
    {
        UE_LOG(LogTemp, Error, TEXT("VehicleMasterComponent: No VehicleConfig assigned!"));
        return false;
    }

    if (!MainVehicleMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("VehicleMasterComponent: No MainVehicleMesh found!"));
        return false;
    }

    return true;
}

bool UVehicleMasterComponent::SetFrontBumperByID(FName BumperID)
{
    if (!VehicleConfig)
    {
        return false;
    }

    for (int32 i = 0; i < VehicleConfig->FrontBumpers.Num(); ++i)
    {
        if (VehicleConfig->FrontBumpers[i].PartID == BumperID)
        {
            return SetFrontBumperByIndex(i);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Front bumper ID '%s' not found"), *BumperID.ToString());
    return false;
}

bool UVehicleMasterComponent::SetFrontBumperByIndex(int32 Index)
{
    if (!VehicleConfig || !VehicleConfig->FrontBumpers.IsValidIndex(Index))
    {
        UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Invalid front bumper index %d"), Index);
        return false;
    }

    CurrentFrontBumperIndex = Index;
    const FCarPart& BumperData = VehicleConfig->FrontBumpers[Index];

    // Create or get the bumper component
    if (!FrontBumperComponent)
    {
        FrontBumperComponent = GetOrCreateBumperComponent(FName("FrontBumper"));
    }

    // Apply the mesh
    ApplyBumperMesh(FrontBumperComponent, BumperData);

    // Broadcast the change event
    OnBumperChanged.Broadcast(BumperData.PartID, BumperData.DisplayName);

    UE_LOG(LogTemp, Log, TEXT("VehicleMasterComponent: Front bumper changed to '%s'"), *BumperData.DisplayName);

    return true;
}

bool UVehicleMasterComponent::SetPaintByID(FName PaintID)
{
    if (!VehicleConfig)
    {
        return false;
    }

    for (int32 i = 0; i < VehicleConfig->PaintColors.Num(); ++i)
    {
        if (VehicleConfig->PaintColors[i].PaintID == PaintID)
        {
            return SetPaintByIndex(i);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Paint ID '%s' not found"), *PaintID.ToString());
    return false;
}

bool UVehicleMasterComponent::SetPaintByIndex(int32 Index)
{
    if (!VehicleConfig || !VehicleConfig->PaintColors.IsValidIndex(Index))
    {
        UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Invalid paint index %d"), Index);
        return false;
    }

    CurrentPaintIndex = Index;
    const FPaintColor& PaintData = VehicleConfig->PaintColors[Index];

    // Apply the material
    ApplyPaintMaterial(PaintData);

    // Broadcast the change event
    OnPaintChanged.Broadcast(PaintData.PaintID, PaintData.DisplayName);

    UE_LOG(LogTemp, Log, TEXT("VehicleMasterComponent: Paint changed to '%s'"), *PaintData.DisplayName);

    return true;
}

bool UVehicleMasterComponent::CycleNextFrontBumper()
{
    if (!VehicleConfig || VehicleConfig->FrontBumpers.Num() == 0)
    {
        return false;
    }

    int32 NextIndex = (CurrentFrontBumperIndex + 1) % VehicleConfig->FrontBumpers.Num();
    return SetFrontBumperByIndex(NextIndex);
}

bool UVehicleMasterComponent::CycleNextPaint()
{
    if (!VehicleConfig || VehicleConfig->PaintColors.Num() == 0)
    {
        return false;
    }

    int32 NextIndex = (CurrentPaintIndex + 1) % VehicleConfig->PaintColors.Num();
    return SetPaintByIndex(NextIndex);
}

FCarPart UVehicleMasterComponent::GetCurrentFrontBumper() const
{
    if (VehicleConfig && VehicleConfig->FrontBumpers.IsValidIndex(CurrentFrontBumperIndex))
    {
        return VehicleConfig->FrontBumpers[CurrentFrontBumperIndex];
    }
    return FCarPart();
}

FPaintColor UVehicleMasterComponent::GetCurrentPaint() const
{
    if (VehicleConfig && VehicleConfig->PaintColors.IsValidIndex(CurrentPaintIndex))
    {
        return VehicleConfig->PaintColors[CurrentPaintIndex];
    }
    return FPaintColor();
}

void UVehicleMasterComponent::ApplyBumperMesh(UStaticMeshComponent* BumperComponent, const FCarPart& PartData)
{
    if (!BumperComponent)
    {
        return;
    }

    // Load the mesh asset
    if (PartData.MeshAsset.IsValid())
    {
        UObject* LoadedAsset = PartData.MeshAsset.Get();
        if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(LoadedAsset))
        {
            BumperComponent->SetStaticMesh(StaticMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Mesh asset is not a StaticMesh"));
        }
    }
    else if (!PartData.MeshAsset.IsNull())
    {
        // Load asynchronously
        PartData.MeshAsset.LoadSynchronous();
        UObject* LoadedAsset = PartData.MeshAsset.Get();
        if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(LoadedAsset))
        {
            BumperComponent->SetStaticMesh(StaticMesh);
        }
    }

    // Apply material overrides if any
    if (PartData.MaterialOverrides.Num() > 0)
    {
        for (int32 i = 0; i < PartData.MaterialOverrides.Num(); ++i)
        {
            if (PartData.MaterialOverrides[i].IsValid())
            {
                UMaterialInterface* Material = PartData.MaterialOverrides[i].Get();
                BumperComponent->SetMaterial(i, Material);
            }
            else if (!PartData.MaterialOverrides[i].IsNull())
            {
                // Load synchronously
                UMaterialInterface* Material = PartData.MaterialOverrides[i].LoadSynchronous();
                if (Material)
                {
                    BumperComponent->SetMaterial(i, Material);
                }
            }
        }
    }

    BumperComponent->SetVisibility(true);
}

void UVehicleMasterComponent::ApplyPaintMaterial(const FPaintColor& PaintData)
{
    if (!MainVehicleMesh)
    {
        return;
    }

    // Load the material
    UMaterialInterface* Material = nullptr;
    if (PaintData.Material.IsValid())
    {
        Material = PaintData.Material.Get();
    }
    else if (!PaintData.Material.IsNull())
    {
        Material = PaintData.Material.LoadSynchronous();
    }

    if (Material)
    {
        // Apply to all material slots (typically paint affects the body)
        // For more control, you might want to specify which slots to affect
        int32 NumMaterials = MainVehicleMesh->GetNumMaterials();
        for (int32 i = 0; i < NumMaterials; ++i)
        {
            MainVehicleMesh->SetMaterial(i, Material);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("VehicleMasterComponent: Failed to load paint material"));
    }
}

UStaticMeshComponent* UVehicleMasterComponent::GetOrCreateBumperComponent(FName ComponentName)
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return nullptr;
    }

    // Try to find existing component
    UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(
        Owner->GetDefaultSubobjectByName(ComponentName)
    );

    if (!Component)
    {
        // Create new component
        Component = NewObject<UStaticMeshComponent>(Owner, UStaticMeshComponent::StaticClass(), ComponentName);
        if (Component)
        {
            Component->RegisterComponent();
            Component->AttachToComponent(MainVehicleMesh, FAttachmentTransformRules::KeepRelativeTransform);
            Component->SetRelativeLocation(FVector::ZeroVector);
            Component->SetRelativeRotation(FRotator::ZeroRotator);
        }
    }

    return Component;
}
