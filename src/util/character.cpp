#include "helper.h"

namespace FFRot {
	void Character::updateTicks(float cd) {
		int cdms = skills[0].skill->gcd ?  skills[0].skill->cd : newCdms(skills[0].skill->cd, sks);
		//int acd = (skills[0].skill->gcd ? newCdms(skills[0].skill->cd, sks) : skills[0].skill->cd);
		gcd = newCdms(2500, sks);
		skills[0].ticks.clear();
		int i = 0;
		int count = 0;
		do {
			int lgcd = getLatestGCD(i + cdms);
			int ngcd = getNextGCD(i + cdms);
			if (i + cdms - lgcd < skills[0].skill->lock + 500)
				i = lgcd + skills[0].skill->lock + 500 + ping;
			else if (ngcd-(i+cdms) < skills[0].skill->lock +500)
				i = ngcd + skills[0].skill->lock + 500 + ping;
			else i += cdms;

			int dms = 0;
			if (count>0)
				dms = (i-skills[0].ticks[count-1].ms) - cdms;




			skills[0].ticks.push_back({i, dms});
			count++;
		} while (i <= FFRot::t_stats[0].dur);
	}

	int Character::getLatestGCD(int ms) {
		int gcdms = gcd;
		int ret = gcdms * getGCDNumber(ms);
		return ret;
	}

	int Character::getNextGCD(int ms) {
		int gcdms = gcd;
		int ret = gcdms * getGCDNumber(ms+gcdms) ;
		return ret;
	}

	int Character::getGCDNumber(int ms) {
		return ms / gcd;
	}

	Character::Character() {
		skills.push_back({ &skillList[0], {}});
		isSksAffected = true; //this is temporary until skills are properly added
		str = 0;
		crit = 0;
		det = 0;
		sks = 0;
		sps = 0;
		wis = 0;
		_int = 0;
		dh = 0;
		gcd = newCdms(2500, sks);
		pie = 0;
		ten = 0;
		hp = 0;
		vit = 0;
		ping = 80; 
		cjob = Job::PLD;
	}
}


