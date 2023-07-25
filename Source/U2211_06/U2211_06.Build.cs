using UnrealBuildTool;

public class U2211_06 : ModuleRules
{
	public U2211_06(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);


        PublicDependencyModuleNames.Add("Core");

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("InputCore");

        PublicDependencyModuleNames.Add("Niagara");
        
        PublicDependencyModuleNames.Add("AIModule");
    }
}
