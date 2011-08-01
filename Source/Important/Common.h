#pragma once

#include <BWAPI.h>

#include <list>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "Signals.h"

// Global Macro
#ifndef COMPILE_GLOBAL
  #define GLOBAL extern
#else
  #define GLOBAL
#endif


// Typedefs for standard containers for BWAPI Unit's
//   Note that BWAPI Unit's are ALWAYS pointers (don't make new ones!)
typedef std::set<BWAPI::Unit*> UnitSet;
typedef std::list<BWAPI::Unit*> UnitList;
typedef std::vector<BWAPI::Unit*> UnitVector;

typedef std::set<BWAPI::UnitType> UnitTypeSet;

// Prototype for function that allows you to find what unit types a unit builds
// Usage: buildsWhat(UnitType)
namespace BWAPI {

	UnitTypeSet const &buildsWhat(UnitType unitType);
}

class BuildingManager;

typedef boost::shared_ptr<BuildingManager> BuildingManagerPtr;
typedef std::set<BuildingManagerPtr> BuildingManagerSet;

class IBuildingManagerBehaviour;

typedef boost::shared_ptr<IBuildingManagerBehaviour> IBM_BehaviourPtr;


struct BM_BaseBehaviourFactory;

typedef std::map<BWAPI::UnitType, BM_BaseBehaviourFactory*> BM_factoryMap;

/* globals */
GLOBAL int g_frame;
GLOBAL BuildingManagerSet managers;
GLOBAL BM_factoryMap managerWatchMap;