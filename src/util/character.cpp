#include "helper.h"

namespace FFRot {
	void Character::updateTicks(int index) {
		int stat = (skills[index].skill->cast ? sps : sks);
		if (skills[index].skill->cd < 0.01f) return;
		//"cd milliseconds", how long the cd of a skill is based on if its gcd
		int cdms = getAdjustedCD(skills.at(index).skill);
		gcd = newCdms(2500, stat); //find out characters gcd, not to be confused with skill gcd which is a bool
		skills.at(index).ticks.clear();
		int i = 0;
		int count = 0;
		//while (i <= FFRot::t_stats.at(id).dur) {
			int lgcd = getLatestGCD(i); //find the two gcd's times that the guessed time is between
			int ngcd = getNextGCD(i);
			i = ngcd;

			int dms = 0; //find the delta ms between consectutive uses of the skill
			fitGCDAuto(10000);
			//addTick(index, i);
			//	dms = (i-skills[index].ticks[count-1].ms) - cdms;

			//skills.at(index).ticks.push_back({i, dms});


			count++;
		//}
	}

	

	int Character::getLatestGCD(int ms) {
		//int gcdms = gcd;
		//int ret = gcdms * getGCDNumber(ms);
		//return ret;
		if (gcdTicks.size() > 0) {
			for (int i = 0; i < gcdTicks.size(); i++) {
				if (gcdTicks.at(i) > ms)
				{
					return gcdTicks.at(i-1);
				}
			}
		}
		return 0;
	}

	int Character::getNextGCD(int ms) {
		//int gcdms = gcd;
		//int ret = gcdms * getGCDNumber(ms+gcdms) ;
		//return ret;
		
		if (gcdTicks.size() > 0) {

			for (int i = 0; i < gcdTicks.size(); i++)
			{
				if (gcdTicks.at(i) > ms)
				{
					return gcdTicks.at(i);
				}
			}
		}
		if (gcdTicks.size() > 1)
			return gcdTicks.at(1);
		return 0;
	}

	int Character::getGCDNumber(int ms) {
		return ms / (getLatestGCD(ms)+1);
	}

	int Character::getAdjustedCD(Skill* skill) { //returns new cd based on what kind of skill it is and that type's stat
		int stat = (skill->cast ? sps : sks);
		int newcd = (skill->gcd ? newCdms(skill->cd, stat) : skill->cd);
		return newcd;
	}

	bool Character::isOnCD(int index, int ms) { //returns whether or not the skill is on cooldown (in its own tick list)
		bool ret;
		CharSkill skill = skills.at(index);
		if (skill.ticks.size() > 0) {
			int last = skill.ticks.at(skill.ticks.size() - 1).ms;
			if (last + getAdjustedCD(skill.skill) > ms) {
				return false;
			}
		}
		else if (skill.ticks.size() == 0) {
			return false;
		}
		return true;
	}

	void Character::addTick(int index, int ms) {
		CharSkill* skill = &skills.at(index);
		if (skill->ticks.size() == 0)
			skill->ticks.push_back({ ms, 0 });
		else
			skill->ticks.push_back({ms,		(ms - skill->ticks.at(skill->ticks.size() - 1).ms) - getAdjustedCD(skill->skill)});
	}

	int Character::getGCDLength(int index) {
		int stat = (skills[index].skill->cast ? sps : sks);
		int ret= newCdms(2500, stat);
		return ret;
	}


	void Character::fitGCDAuto(int maxSearch = 10000) //trys to automatically build a gcd timeline. skill slotting priority is by small to large index in skills[]
	{
		gcdTicks.clear();
		gcdTicks.push_back(0);
		int dur = 0;
		int tempcd = 0;
		while (dur < FFRot::t_stats.at(id).dur) {  //step through the whole duration of the timeline for this character
			for (int i = 0; i < skills.size(); i++) {
				if (!isOnCD(i, dur)) {
					tempcd = getGCDLength(i); //if a skill is on cd, itll be skipped, otherwise it is the next gcd and the rest are skipped
					addTick(i, dur);
					break;
				}
			}
			if (tempcd == 0) {
				tempcd = newCdms(2500, sks);
			}

			gcdTicks.push_back(dur);
			dur += tempcd;
			tempcd = 0;
		}
	}

	Character::Character() {
		id = 0;
	}

	Character::Character(int _id) {
		id = _id;
		skills.push_back({ &skillList[0], {}});
		skills.push_back({ &skillList[1], {} });
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


