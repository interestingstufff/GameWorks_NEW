// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Guid.h"

// Custom serialization version for all packages containing Niagara asset types
struct FNiagaraCustomVersion
{
	enum Type
	{
		// Before any version changes were made in niagara
		BeforeCustomVersionWasAdded = 0,

		// Reworked vm external function binding to be more robust.
		VMExternalFunctionBindingRework,

		// Making all Niagara files reference the version number, allowing post loading recompilation if necessary.
		PostLoadCompilationEnabled,

		// Moved some runtime cost from external functions into the binding step and used variadic templates to neaten that code greatly.
		VMExternalFunctionBindingReworkPartDeux,

		// Moved per instance data needed for certain data interfaces out to it's own struct.
		DataInterfacePerInstanceRework,

		// Added shader maps and corresponding infrastructure
		NiagaraShaderMaps,

		// Combined Spawn, Update, and Event scripts into one graph.
		UpdateSpawnEventGraphCombination,

		// Reworked data layout to store float and int data separately.
		DataSetLayoutRework,

		// Reworked scripts to support emitter & system scripts
		AddedEmitterAndSystemScripts,

		// Rework of script execution contexts to allow better reuse and reduce overhead of parameter handling. 
		ScriptExecutionContextRework,

		// Removed the Niagara variable ID's making hookup impossible until next compile
		RemovalOfNiagaraVariableIDs,
		
		// System and emitter script simulations.
		SystemEmitterScriptSimulations,

		// Adding integer random to VM. TODO: The vm really needs its own versioning system that will force a recompile when changes.
		IntegerRandom,

		// Added emitter spawn attributes
		AddedEmitterSpawnAttributes,

		// cooking of shader maps and corresponding infrastructure
		NiagaraShaderMapCooking,
		NiagaraShaderMapCooking2,		// don't serialize shader maps for system scripts
		// Added script rapid iteration variables, usually top-level module parameters...
		AddedScriptRapidIterationVariables,

		// Added type to data interface infos
		AddedTypeToDataInterfaceInfos,

		// Hooked up autogenerated default values for function call nodes.
		EnabledAutogeneratedDefaultValuesForFunctionCallNodes,

		// Now curve data interfaces have look-up tables on by default.
		CurveLUTNowOnByDefault,

		// Scripts now use a guid for identification instead of an index when there are more than one with the same usage.
		ScriptsNowUseAGuidForIdentificationInsteadOfAnIndex,

		NiagaraCombinedGPUSpawnUpdate,  // don't serialize shader maps for update scripts

		DontCompileGPUWhenNotNeeded,  // don't serialize shader maps for emitters that don't run on gpu.

		LifeCycleRework,

		NowSerializingReadWriteDataSets, // We weren't serializing event data sets previously.

		TranslatorClearOutBetweenEmitters, // Forcing the internal parameter map vars to be reset between emitter calls.

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};

	// The GUID for this custom version number
	NIAGARA_API const static FGuid GUID;

private:
	FNiagaraCustomVersion() {}
};



