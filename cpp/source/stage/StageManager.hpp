/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "stages.hpp"
#include <string>
#include <map>
#include <vector>

namespace stage {

using std::string;
using std::map;
using std::vector;

class StageManager
{
public:
	Repository& repository;

	StageManager(Repository& r) : repository(r),
		stageBuildGraph(r),
		stageBindIdentifiers(r),
		stageBindNamedTypes(r),
		stageEvalTypeExprs(r),
		stageInitRootTypes(r),
		stageConfigureCalls(r),
		stageFindCallCandidates(r),
		stageCalcPossibleTypes(r),
		stageCalcRequiredTypes(r),
		stageCalcActualTypes(r),
		stageNarrowCallCandidates(r),
		stageSelectCallCandidate(r)
	{
		stageIndices["BuildGraph"] = stages.size();
		stagesByName["BuildGraph"] = &stageBuildGraph;
		stages.push_back(&stageBuildGraph);
		stageIndices["BindIdentifiers"] = stages.size();
		stagesByName["BindIdentifiers"] = &stageBindIdentifiers;
		stages.push_back(&stageBindIdentifiers);
		stageIndices["BindNamedTypes"] = stages.size();
		stagesByName["BindNamedTypes"] = &stageBindNamedTypes;
		stages.push_back(&stageBindNamedTypes);
		stageIndices["EvalTypeExprs"] = stages.size();
		stagesByName["EvalTypeExprs"] = &stageEvalTypeExprs;
		stages.push_back(&stageEvalTypeExprs);
		stageIndices["InitRootTypes"] = stages.size();
		stagesByName["InitRootTypes"] = &stageInitRootTypes;
		stages.push_back(&stageInitRootTypes);
		stageIndices["ConfigureCalls"] = stages.size();
		stagesByName["ConfigureCalls"] = &stageConfigureCalls;
		stages.push_back(&stageConfigureCalls);
		stageIndices["FindCallCandidates"] = stages.size();
		stagesByName["FindCallCandidates"] = &stageFindCallCandidates;
		stages.push_back(&stageFindCallCandidates);
		stageIndices["CalcPossibleTypes"] = stages.size();
		stagesByName["CalcPossibleTypes"] = &stageCalcPossibleTypes;
		stages.push_back(&stageCalcPossibleTypes);
		stageIndices["CalcRequiredTypes"] = stages.size();
		stagesByName["CalcRequiredTypes"] = &stageCalcRequiredTypes;
		stages.push_back(&stageCalcRequiredTypes);
		stageIndices["CalcActualTypes"] = stages.size();
		stagesByName["CalcActualTypes"] = &stageCalcActualTypes;
		stages.push_back(&stageCalcActualTypes);
		stageIndices["NarrowCallCandidates"] = stages.size();
		stagesByName["NarrowCallCandidates"] = &stageNarrowCallCandidates;
		stages.push_back(&stageNarrowCallCandidates);
		stageIndices["SelectCallCandidate"] = stages.size();
		stagesByName["SelectCallCandidate"] = &stageSelectCallCandidate;
		stages.push_back(&stageSelectCallCandidate);
	}

	typedef vector<Stage*> Stages;
	typedef map<string, int> StageIndices;
	typedef map<string, Stage*> StagesByName;
	Stages stages;
	StageIndices stageIndices;
	StagesByName stagesByName;

protected:
	BuildGraph stageBuildGraph;
	BindIdentifiers stageBindIdentifiers;
	BindNamedTypes stageBindNamedTypes;
	EvalTypeExprs stageEvalTypeExprs;
	InitRootTypes stageInitRootTypes;
	ConfigureCalls stageConfigureCalls;
	FindCallCandidates stageFindCallCandidates;
	CalcPossibleTypes stageCalcPossibleTypes;
	CalcRequiredTypes stageCalcRequiredTypes;
	CalcActualTypes stageCalcActualTypes;
	NarrowCallCandidates stageNarrowCallCandidates;
	SelectCallCandidate stageSelectCallCandidate;
};

} // namespace stage
