#include "helper.h"

namespace FFRot {
	void Character::updateTicks(float cd) {

		int cdms = newCd(cd, sks) * 1000;
		
		ticksById[0].clear();

		for (int i = 0; i <= FFRot::t_stats[0].dur; i += cdms) {
			ticksById[0].push_back(i);
		}
	}
}


