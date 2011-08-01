#pragma once
#include "Important\Common.h"
#include "IBuildingManagerBehaviour.h"
#include "Util\Debug.h"

using BWAPI::Unit;

class NexusBehaviour : public IBuildingManagerBehaviour, private Debug {
public:
	NexusBehaviour(Unit &nexus);

	virtual void postBuild(BWAPI::Unit *unit);
	virtual bool shouldBuild(BWAPI::UnitType type);
	virtual BWAPI::UnitType setBuildType(void);

	void setShouldBuild(bool newFlag) {m_shouldBuild = newFlag;}

	void onFriendlyUnitDestroy(BWAPI::Unit *unit) {removeProbeFromGatherers(unit);}
	void onNeutralUnitDestroy(BWAPI::Unit *unit) {m_gas.remove(unit);
												m_minerals.remove(unit);}

private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

	void findMinerals(void);

    bool addMiner(Unit *probe);
    bool addGasser(Unit *probe);

	bool addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList);
	bool removeProbeFromGatherers(BWAPI::Unit *probe);

	const static int s_mineralDistance;

	Unit &m_nexus;

	UnitList m_gas;
	UnitList m_minerals;

	UnitSet m_minGatherers;
	UnitSet m_gasGatherers;

	bool m_shouldBuild;

	// Not implemented to disallow assignment
	// and default construction
	NexusBehaviour(void);
	NexusBehaviour(NexusBehaviour &rhs);
	NexusBehaviour &operator=(NexusBehaviour &rhs);
};


// Current problems: queues like a bitch
// also, possibly related to queueing is it doesn't always successfully execute the postBuild