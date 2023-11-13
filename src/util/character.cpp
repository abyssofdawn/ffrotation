#include "helper.h"
#include <math.h>

namespace FFRot {
	void Character::updateTicks(int index) {
		
		clearTicks();
		fitGCDAuto(10000);

	}

	void Character::clearTicks() {
		for (int i = 0; i < skills.size(); i++)
			skills[i].ticks.clear();
	}
	

	GCDTick Character::getLatestGCD(int ms) {

		if (gcdTicks.size() > 1) {
			for (int i = 0; i < gcdTicks.size(); i++) {
				if (gcdTicks.at(i).tick.ms + gcdTicks.at(i).tick.delay > ms)
				{
					return gcdTicks.at(i-1);
				}
			}
		}
		return { nullptr, {0,0} };
	}

	int Character::getNextGCD(int ms) {
		//int gcdms = gcd;
		//int ret = gcdms * getGCDNumber(ms+gcdms) ;
		//return ret;
		
		if (gcdTicks.size() > 0) {

			for (int i = 0; i < gcdTicks.size(); i++)
			{
				if (gcdTicks.at(i).tick.ms < ms)
				{
					return gcdTicks.at(i).tick.delay+gcdTicks.at(i).tick.ms;
				}
			}
		}
		if (gcdTicks.size() > 1)
			return gcdTicks.at(1).tick.ms;
		return 0;
	}

	void Character::fitOGCD(int index, int ms) { //trys to fit all ogcd skills to be used on cooldown

	}

	int Character::getLastUsedAtTime(int index, int ms) { //gets last used time for a specific skill at a specific time
		Tick* ret = &skills.at(index).ticks.at(0);
		int pms = ret->ms;
		for (int i = 0; i < skills.at(index).ticks.size(); i++) {
			if (ms > pms)
			{
				ret = &skills.at(index).ticks.at(i);
			} 
			pms = skills.at(index).ticks.at(i).ms;
		}
		return ret->ms;
	}

	int Character::getLastUsed(int index) {
		if(skills.at(index).ticks.size()>0)
			return skills.at(index).ticks.at(skills.at(index).ticks.size() - 1).ms;
		return 0;
	}

	int Character::getGCDNumber(int ms) {
		return 0;
	}

	int Character::getAdjustedCD(Skill* skill) { //returns new cd based on what kind of skill it is and that type's stat
		int stat = (skill->cast ? sps : sks);
		int newcd = (skill->gcd ? newCdms(skill->cd, stat) : skill->cd);
		return newcd;
	}

	bool Character::isOnCD(int index, int ms) { //returns whether or not the skill is on cooldown (in its own tick list)
		bool ret;
		CharSkill skill = skills.at(index);
		int last = getLastUsed(index);
		int delta = ms - last;
		if (delta < getAdjustedCD(skill.skill) && skills.at(index).ticks.size()>0) {
			return true;
		}
		return false;
	}

	int Character::getLastTickDelta(int index, int ms) {
		if (skills.at(index).ticks.empty()) return 0;

		int last = skills.at(index).ticks.at(skills.at(index).ticks.size() - 1).ms;

		int ret = ms - last;
		return ret;

	}

	void Character::addTick(int index, int ms) {
		CharSkill* skill = &skills.at(index);
		if (skill->ticks.size() == 0)
			skill->ticks.push_back({ ms, 0 });
		else
			skill->ticks.push_back({ms,		(ms - skill->ticks.at(skill->ticks.size() - 1).ms)-getAdjustedCD(skill->skill)});
	}

	int Character::getGCDLength(int index) {
		int stat = (skills[index].skill->cast ? sps : sks);
		int ret= newCdms(2500, stat);
		return ret;
	}


	void Character::fitGCDAuto(int maxSearch = 10000) //trys to automatically build a gcd timeline. skill slotting priority is by small to large index in skills[]
	{
		gcdTicks.clear();
		int dur = 0;
		int tempcd = 0;
		int stat = sks; 
		Skill* skill = nullptr;
		while (dur < FFRot::t_stats.at(id).dur) {  //step through the whole duration of the timeline for this character
			for (int i = 0; i < skills.size(); i++) {//if a skill is on cd, itll be skipped, otherwise it is the next gcd and the rest are skipped
				if (isOnCD(i, dur))
				{
					continue;
				}
				else if (!isOnCD(i, dur) && skills.at(i).skill->gcd)
				{
					skill = skills.at(i).skill;
					stat = (skill->cast ? sps : sks);
					addTick(i, dur);
					break;
				}
				else 
				{
					stat = sks;
				}

			}
			tempcd = newCdms(2500, stat);

			gcdTicks.push_back({skill, { dur, tempcd } });
			dur += tempcd;
			tempcd = 0;
		}
	}

	void Character::makeSkills() {
		for (auto& it : skillList) {
			skills.push_back({ &it, {} });
		}
	}


	Character::Character() {
		id = 0;
	}

	Character::Character(int _id) {
		id = _id;
		makeSkills();
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


