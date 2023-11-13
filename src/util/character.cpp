#include "helper.h"
#include <math.h>

namespace FFRot {

	// tick array helpers
	
	void Character::updateTicks(int index) {
		
		clearTicks();
		fitGCDAuto(10000);

	}

	void Character::clearTicks() {
		for (int i = 0; i < skills.size(); i++)
			skills[i].ticks.clear();
	}

	void Character::clearSkills()
	{
		skills.clear();
	}
	
	void Character::pushSkillTick(int index, int ms) {
		skills.at(index).ticks.push_back({ ms, (skills.at(index).ticks.size() > 0 ? ms - skills.at(index).ticks.back().ms - newCdms(skills.at(index).skill->cd, getSpeedStatForSkill(index)) : 0)});
	}

	// skill methods

	int Character::inUsableRange(int index, int ms) { //returns the first available slot, if no adjustment needed, return initial ms
		
		if (skills.size() <= 1) return ms;  // if theres only one skill skip animation lock check
		
		int endlockdur = skills.at(index).skill->lock + ping + 500;


		int lastticktime = 0;
		int nextticktime = t_stats.at(id).dur;
		Skill* lasttickptr = (index == 0 ? skills.at(1).skill : skills.at(0).skill);
		Skill* nexttickptr = gcdTicks.back().skill;
		
		for (int i = 0; i < skills.size(); i++)
		{
			if (i != index) {
				for (auto j = skills.at(i).ticks.begin(); j < skills.at(i).ticks.end(); j++)
				{
					int timer = j->ms;
					if (timer > lastticktime && timer < ms) {
						lastticktime = timer;
						if (ms - lastticktime < skills.at(i).skill->lock + ping)
						{
							
						}
					}

				}
			}
		}
		return ms;
	}

	bool Character::isOffCd(int index, int ms) {
		int adjustedCd = newCdms(skills.at(index).skill->cd, getSpeedStatForSkill(index))-1;

		return (!skills.at(index).ticks.empty() ? ms - getLastUseByTime(index, ms) >= adjustedCd : true);
	}

	int Character::getLastUseByTime(int index, int ms) {
		int lastUsedMs = 0;
		for (auto& i : skills.at(index).ticks)
		{
			if (ms > i.ms)
			{
				lastUsedMs = i.ms;
			}
			else
			{
				break;
			}
		}
		return lastUsedMs;
	}

	GeneralTick Character::getLastUsedGCDByTime(int ms) {
		if (gcdTicks.size() > 0 && ms >= 0) {
			for (int i = gcdTicks.size()-1; i >= 0; i--) {
				if (gcdTicks.at(i).ms <= ms) {
					return gcdTicks.at(i);
				}
			}
		}
		return gcdTicks.at(0);
	}

	GeneralTick Character::getNextUsedGCDByTime(int ms) {
		if (gcdTicks.size() > 0 && ms <= t_stats.at(id).dur) {
			for (int i = 0; i < gcdTicks.size(); i++)
			{
				if (gcdTicks.at(i).ms > ms)
				{
					return gcdTicks.at(i);
				}
			}
		}
		
		return gcdTicks.back();
	}

	int Character::getLastUsedGCDIndexByTime(int ms) {
		if (gcdTicks.size() > 0 && ms >= 0) {
			for (int i = gcdTicks.size() - 1; i >= 0; i--) {
				if (gcdTicks.at(i).ms <= ms) {
					return i;
				}
			}
		}
		return 0;
	}


	int Character::getNextUsedGCDIndexByTime(int ms) {
		if (gcdTicks.size() > 0 && ms <= t_stats.at(id).dur) {
			for (int i = 0; i < gcdTicks.size(); i++)
			{
				if (gcdTicks.at(i).ms > ms)
				{
					return i;
				}
			}
		}

		return (gcdTicks.empty() ? 0 : gcdTicks.size()-1);
	}

	// misc helpers

	int Character::getSpeedStatForSkill(int index) {
		return (skills.at(index).skill->cast ? sps : sks);
	}

	// automatic skill alignment

	void Character::fitGCDAuto(int maxSearch = 10000) //trys to automatically build a gcd timeline. skill slotting priority is by small to large index in skills[]
	{
		gcdTicks.clear();
		int dur = 0;
		int tempcd = 0;
		int stat = sks; 
		Skill* skill = nullptr;
		while (dur < FFRot::t_stats.at(id).dur) {  //step through the whole duration of the timeline for this character
			for (int i = 0; i < skills.size(); i++) {//if a skill is on cd, itll be skipped, otherwise it is the next gcd and the rest are skipped
				skill = skills.at(i).skill;
				if (!isOffCd(i, dur))
				{
					continue;
				}
				else if (isOffCd(i, dur) && skills.at(i).skill->gcd)
				{
					stat = (skill->cast ? sps : sks);
					pushSkillTick(i, dur);
					break;
				}
				else 
				{
					stat = sks;
				}

			}
			tempcd = newCdms(2500, stat);

			gcdTicks.push_back({skill, dur, tempcd + dur});
			dur += tempcd;
			tempcd = 0;
		}
	}

	void Character::fitOGCDAuto(int maxSearch = 10000) 
	{
		int dur = 0;
		while (dur < FFRot::t_stats.at(id).dur) {  //step through the whole duration of the timeline for this character
			for (int i = 0; i < skills.size(); i++) {
				if (!isOffCd(i, dur))
				{
					continue;
				}
			}
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


