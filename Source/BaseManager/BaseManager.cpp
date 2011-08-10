#include "BaseManager.h"
#include "Util/RelativeSide.h"

using namespace BWAPI;

bool BaseManager::constructBuilding(BWAPI::UnitType type, bool inQueue) {
	if (m_lastBuilding == 0) {
		// Create a first building in the area
		m_probe = m_controllee->removeProbe();
		RelativeSide placer(m_controllee->getNexus());
		TilePosition tile = placer.Place(type, RelativeSide::Left, 2, 0).makeValid();

		if (Broodwar->canBuildHere(m_probe, tile, type, true)) {
			return m_probe->build(tile, type);
		}

	} else {
		RelativeSide placer(m_lastBuilding);
		TilePosition tile = placer.Place(type, RelativeSide::Left, 2, 0).makeValid();

		if (Broodwar->canBuildHere(m_probe, tile, type, true)) {
			return m_probe->build(tile, type);
		}
	}

	if (Broodwar->canMake(m_probe, type) && !inQueue) {
		m_buildQueue.push(type);
		return false;
	}
	return false;
}

void BaseManager::onFrame(void) {
	if (!m_buildQueue.empty()) {
		if (constructBuilding(m_buildQueue.front())) {
			m_buildQueue.pop();
		}

	} else if (m_probe && !m_probe->isConstructing()) {
		m_controllee->addProbe(m_probe);
		m_probe = 0;
	}
}
