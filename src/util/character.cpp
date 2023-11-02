#include "helper.h"

namespace FFRot {
	void Character::updateTicks(int index) {
		//"cd milliseconds", how long the cd of a skill is based on if its gcd
		int cdms = skills[index].skill->gcd ?  skills[index].skill->cd : newCdms(skills[index].skill->cd, sks); 
		gcd = newCdms(2500, sks); //find out characters gcd, not to be confused with skill gcd which is a bool
		skills[index].ticks.clear();
		int i = 0;
		int count = index;
		do {
			int lgcd = getLatestGCD(i + cdms); //find the two gcd's times that the guessed time is between
			int ngcd = getNextGCD(i + cdms);
			if (i + cdms - lgcd < skills[index].skill->lock + 500) //delay the skill if it will clip a gcd/get clipped by a gcd
				i = lgcd + skills[index].skill->lock + 500 + ping; 
			else if (ngcd-(i+cdms) < skills[index].skill->lock +500)
				i = ngcd + skills[index].skill->lock + 500 + ping;
			else i += cdms; 

			int dms = 0; //find the delta ms between consectutive uses of the skill
			if (count>0)
				dms = (i-skills[index].ticks[count-1].ms) - cdms;

			skills[index].ticks.push_back({i, dms});
			count++;
		} while (i <= FFRot::t_stats[index].dur);
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
		skills.clear();
		skills.push_back({ &skillList[0], {}});
		skills.push_back({ &skillList[1], {} });
		for (int n = 0; n < skills.size() - 2; n++) {
			skills.pop_back();
		}
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


