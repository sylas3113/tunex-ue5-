// Copyright TuneX Project. All Rights Reserved.

#include "TuningController.h"
#include "VehicleMasterComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ATuningController::ATuningController()
{
	TargetVehicle = nullptr;
	bAutoFindVehicle = true;
}

void ATuningController::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoFindVehicle && !TargetVehicle)
	{
		AutoFindVehicle();
	}
}

void ATuningController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		// Bind bumper selection keys (1, 2, 3)
		InputComponent->BindAction("BumperOption1", IE_Pressed, this, &ATuningController::HandleBumperInput1);
		InputComponent->BindAction("BumperOption2", IE_Pressed, this, &ATuningController::HandleBumperInput2);
		InputComponent->BindAction("BumperOption3", IE_Pressed, this, &ATuningController::HandleBumperInput3);

		// Bind paint selection keys (Q, W, E)
		InputComponent->BindAction("PaintOption1", IE_Pressed, this, &ATuningController::HandlePaintInputQ);
		InputComponent->BindAction("PaintOption2", IE_Pressed, this, &ATuningController::HandlePaintInputW);
		InputComponent->BindAction("PaintOption3", IE_Pressed, this, &ATuningController::HandlePaintInputE);

		UE_LOG(LogTemp, Log, TEXT("TuningController: Input bindings set up. Use 1/2/3 for bumpers, Q/W/E for paint."));
	}
}

void ATuningController::SetTargetVehicle(AActor* Vehicle)
{
	TargetVehicle = Vehicle;
	
	if (TargetVehicle)
	{
		UE_LOG(LogTemp, Log, TEXT("TuningController: Target vehicle set to %s"), *TargetVehicle->GetName());
	}
}

void ATuningController::AutoFindVehicle()
{
	if (UWorld* World = GetWorld())
	{
		// Find any actor with a VehicleMasterComponent
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (Actor && Actor->FindComponentByClass<UVehicleMasterComponent>())
			{
				SetTargetVehicle(Actor);
				UE_LOG(LogTemp, Log, TEXT("TuningController: Auto-found vehicle: %s"), *Actor->GetName());
				return;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("TuningController: No vehicle with VehicleMasterComponent found in world"));
	}
}

IVehicleModifierInterface* ATuningController::GetVehicleInterface()
{
	if (!TargetVehicle)
	{
		return nullptr;
	}

	return Cast<IVehicleModifierInterface>(TargetVehicle);
}

void ATuningController::HandleBumperInput1()
{
	SelectBumperOption1();
}

void ATuningController::HandleBumperInput2()
{
	SelectBumperOption2();
}

void ATuningController::HandleBumperInput3()
{
	SelectBumperOption3();
}

void ATuningController::HandlePaintInputQ()
{
	SelectPaintOption1();
}

void ATuningController::HandlePaintInputW()
{
	SelectPaintOption2();
}

void ATuningController::HandlePaintInputE()
{
	SelectPaintOption3();
}

void ATuningController::SelectBumperOption1()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	// Get the VehicleMasterComponent directly
	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->SetFrontBumperByIndex(0))
		{
			FCarPart CurrentBumper = VehicleComponent->GetCurrentFrontBumper();
			UE_LOG(LogTemp, Display, TEXT("✓ Bumper changed to: %s (Option 1)"), *CurrentBumper.DisplayName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: Vehicle does not have VehicleMasterComponent"));
	}
}

void ATuningController::SelectBumperOption2()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->SetFrontBumperByIndex(1))
		{
			FCarPart CurrentBumper = VehicleComponent->GetCurrentFrontBumper();
			UE_LOG(LogTemp, Display, TEXT("✓ Bumper changed to: %s (Option 2)"), *CurrentBumper.DisplayName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: Vehicle does not have VehicleMasterComponent"));
	}
}

void ATuningController::SelectBumperOption3()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->SetFrontBumperByIndex(2))
		{
			FCarPart CurrentBumper = VehicleComponent->GetCurrentFrontBumper();
			UE_LOG(LogTemp, Display, TEXT("✓ Bumper changed to: %s (Option 3)"), *CurrentBumper.DisplayName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: Vehicle does not have VehicleMasterComponent"));
	}
}

void ATuningController::SelectPaintOption1()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->SetPaintByIndex(0))
		{
			FPaintColor CurrentPaint = VehicleComponent->GetCurrentPaint();
			UE_LOG(LogTemp, Display, TEXT("✓ Paint changed to: %s (Option 1)"), *CurrentPaint.DisplayName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: Vehicle does not have VehicleMasterComponent"));
	}
}

void ATuningController::SelectPaintOption2()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->SetPaintByIndex(1))
		{
			FPaintColor CurrentPaint = VehicleComponent->GetCurrentPaint();
			UE_LOG(LogTemp, Display, TEXT("✓ Paint changed to: %s (Option 2)"), *CurrentPaint.DisplayName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: Vehicle does not have VehicleMasterComponent"));
	}
}

void ATuningController::SelectPaintOption3()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->SetPaintByIndex(2))
		{
			FPaintColor CurrentPaint = VehicleComponent->GetCurrentPaint();
			UE_LOG(LogTemp, Display, TEXT("✓ Paint changed to: %s (Option 3)"), *CurrentPaint.DisplayName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: Vehicle does not have VehicleMasterComponent"));
	}
}

void ATuningController::CycleNextBumper()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->CycleNextFrontBumper())
		{
			FCarPart CurrentBumper = VehicleComponent->GetCurrentFrontBumper();
			UE_LOG(LogTemp, Display, TEXT("✓ Bumper cycled to: %s"), *CurrentBumper.DisplayName);
		}
	}
}

void ATuningController::CycleNextPaint()
{
	if (!TargetVehicle)
	{
		UE_LOG(LogTemp, Warning, TEXT("TuningController: No target vehicle set!"));
		return;
	}

	if (UVehicleMasterComponent* VehicleComponent = TargetVehicle->FindComponentByClass<UVehicleMasterComponent>())
	{
		if (VehicleComponent->CycleNextPaint())
		{
			FPaintColor CurrentPaint = VehicleComponent->GetCurrentPaint();
			UE_LOG(LogTemp, Display, TEXT("✓ Paint cycled to: %s"), *CurrentPaint.DisplayName);
		}
	}
}
