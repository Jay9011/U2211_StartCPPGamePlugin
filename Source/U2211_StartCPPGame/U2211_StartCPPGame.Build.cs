using UnrealBuildTool;

public class U2211_StartCPPGame : ModuleRules
{
	public U2211_StartCPPGame(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
        PublicIncludePaths.Add(ModuleDirectory);

        PublicDependencyModuleNames.Add("Core");

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("InputCore");
        PrivateDependencyModuleNames.Add("Niagara");
	}
}
