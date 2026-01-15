using UnrealBuildTool;

public class TuneX : ModuleRules
{
	public TuneX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"RHI", 
			"RenderCore",
			"DeveloperTools"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
		});

		// Uncomment if you have Slate dependencies
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you have Niagara dependencies
		// PrivateDependencyModuleNames.AddRange(new string[] { "Niagara" });

		// Enable C++20/23 features if needed
		// bEnableExceptions = true;

		// Optimizations
		bEnableUnity = true;
	}
}
