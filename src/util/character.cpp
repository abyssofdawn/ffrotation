#include "helper.h"
#include <math.h>

namespace FFRot {

	// tick array helpers

	void Character::updateTicks(int index) {
		bool autofill = false;
		if (autofill)
		{
			clearTicks();
			fitGCDAuto(10000);
			fitOGCDAuto(10000);
		}
		else
		{

		}

	}
	void Character::clearTicks() {
		for (int i = 0; i < skills.size(); i++)
			skills[i].ticks.clear();
		generalTicks.clear();
		gcdTicks.clear();
	}
	void Character::makeSkills() {
		for (auto& it : skillList) {
			skills.push_back({ &it, {} });
		}
	}
	void Character::clearSkills()
	{
		skills.clear();
	}
	void Character::pushSkillTick(int index, int ms) {
		skills.at(index).ticks.push_back({ ms, (skills.at(index).ticks.size() > 0 ? ms - skills.at(index).ticks.back().ms - newCdms(skills.at(index).skill->cd, getSpeedStatForSkill(index)) : 0) });
	}
	// skill methods

	int Character::inUsableRange(int index, int ms) { //returns the first available slot, if no adjustment needed, return initial ms

		if (index < 1) return ms;  // if theres only one skill skip animation lock check

		int endlockdur = getAnimationLockForSkill(index);
		int startlockdur = 0;
		CharSkill skill = skills.at(index);
		int check = ms;

		if (skill.ticks.empty()) {
			if(skills.at(index-1).ticks.size() > 0)
			{
				check = skills.at(index - 1).ticks.front().ms + getAnimationLockForSkill(index - 1);
				if (!skills.at(index - 1).skill->gcd) check += 100;
			}
		}

		int lasttickindex = getLastUsedGeneralIndexByTime(check);
		int lastticktime = generalTicks.at(lasttickindex).ms;
		int nextticktime = t_stats.at(id).dur;
		GeneralTick prev = {};
		GeneralTick i;
		if (generalTicks.size() > 1)
		{
			for (int j = lasttickindex + 1; j < generalTicks.size(); j++)
			{
				i = generalTicks.at(j);
				prev = generalTicks.at(j - 1);
				if (prev.skill != skill.skill) {
					//if (isOffCd(index, prev.ms))
					//{
					bool shift = false;
					bool shift2 = false;
					lastticktime = prev.ms;
					//ms = (skill.ticks.empty() ? ms : skill.ticks.back().ms);
					startlockdur = getAnimationLockForSkill(prev.skill);
					if (ms - lastticktime < startlockdur)
					{
						ms = lastticktime + startlockdur;
					}
					//endlockdur = getAnimationLockForSkill(skill.skill);
					nextticktime = i.ms;
					if (nextticktime - ms <= endlockdur) {
						ms = nextticktime + getAnimationLockForSkill(i.skill);
						shift2 = true;
					}
					if (!shift2) return ms;
					//}

				}
			}
		}
		else if (skill.ticks.size() == 0)
		{
			return getAnimationLockForSkill(generalTicks.at(0).skill) + generalTicks.at(0).ms;
		}
		return ms;
	}
	bool Character::isOffCd(int index, int ms) {
		int adjustedCd = newCdms(skills.at(index).skill->cd, getSpeedStatForSkill(index)) - 1;

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
			for (int i = gcdTicks.size() - 1; i >= 0; i--) {
				if (gcdTicks.at(i).ms <= ms) {
					return gcdTicks.at(i);
				}
			}
		}
		return gcdTicks.at(0);
	}
	int Character::getLastUsedGeneralIndexByTime(int ms) {
		if (!generalTicks.empty() && ms >= 0) {
			for (int i = generalTicks.size() - 1; i >= 0; i--) {
				if (generalTicks.at(i).ms <= ms) {
					return i;
				}
			}
		}
		return 0;
	}
	int Character::getNextUsedGeneralIndexByTime(int ms) {
		if (!generalTicks.empty() && ms <= t_stats.at(id).dur) {
			for (int i = 0; i < generalTicks.size(); i++) {
				if (generalTicks.at(i).ms > ms) {
					return i;
				}
			}

		}
		return generalTicks.size();
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

		return gcdTicks.front();
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

		return (gcdTicks.empty() ? 0 : gcdTicks.size() - 1);
	}
	int Character::getLatestUsedOGCDIndex() {
		if (skills.size() > 0) {
			for (int i = skills.size() - 1; i >= 0; i--) {
				if (!skills.at(i).skill->gcd && !skills.at(i).ticks.empty()) {
					return i;
				}
			}
		}
		return 0;
	}
	int Character::getLatestGeneralUseForIndex(int index) {
		int max = 0;
		int ret = 0;

		for (int i = 0; i < index; i++) {
			if (skills.at(i).ticks.size() > 0 && skills.at(i).ticks.at(0).ms > max)
			{
				max = skills.at(i).ticks.at(0).ms;
				ret = i;
			}
		}

		Skill* skill = skills.at(ret).skill;
		for (int i = 0; i < generalTicks.size(); i++) {
			if (skill == generalTicks.at(i).skill) return i;
		}

		return 0;
	}

	// misc helpers

	int Character::getSpeedStatForSkill(int index) {
		return (skills.at(index).skill->gcd ? (skills.at(index).skill->cast ? sps : sks ) : 400);
	}
	int Character::getSpeedStatForSkill(Skill* skill) {
		return (skill->gcd ? (skill->cast ? sps : sks) : 400);
	}
	int Character::getAnimationLockForSkill(int index) {
		CharSkill skill = skills.at(index);
		return skill.skill->lock + (skill.skill->gcd ? 100 : 500) + ping;
	}
	int Character::getAnimationLockForSkill(Skill* skill) {
		return skill->lock + (skill->gcd ? 100 : 500) + ping;
	}

	// automatic skill alignment

	void Character::fitGCDAuto(int maxSearch = 10000) //trys to automatically build a gcd timeline. skill slotting priority is by small to large index in skills[]
	{
		int dur = 0; //when the skill occurs
		int tempcd = 0; //step length. increments the dur every loop so it can escape the while loop
		int stat = sks; //stat # to be used in speed up calculation
		int gcdLength = 0; //how long the gcd will be rolling after a skill
		Skill* skill = nullptr;
		while (dur < t_stats.at(id).dur) {  //step through the whole duration of the timeline for this character
			for (int i = 0; i < skills.size(); i++) {//if a skill is on cd, itll be skipped, otherwise it is the next gcd and the rest are skipped
				skill = skills.at(i).skill;
				if (!isOffCd(i, dur)) //if still cooling down skip it
				{
					continue;
				}
			/*	if skill is not cooling down(aka it CAN be executed) and the skill is a gcd, get gcd recast from previous gcd.
				if 
				if the previous gcd time plus its gcd recast has the skill still off cooldown, set dur to that time (ms+recast) to "click" it into place asap
			*/	
				else if (isOffCd(i, dur) && skill->gcd) 
				{
					stat = getSpeedStatForSkill(skill);
					GeneralTick last = getLastUsedGCDByTime(dur);
					int lastSkill = getLastUseByTime(i, dur);
					int recast = newCdms(last.skill->recast, stat);
					int earliest = std::min(isOffCd(i, recast + last.ms) ? recast + last.ms : INT64_MAX, isOffCd(i, lastSkill+newCdms( skill->cd, stat)) ? lastSkill + newCdms(skill->cd, stat) : INT64_MAX );
					if (earliest < dur) {

						dur = earliest;

						pushSkillTick(i, dur);
						gcdLength = recast;
						break;

					}
				}
				else 
				{
					stat = sks;
				}

			}
			tempcd = gcdLength;

			gcdTicks.push_back({skill, dur, tempcd + dur});
			int index = getNextUsedGeneralIndexByTime(dur);
			generalTicks.insert(generalTicks.begin() + index, { skill, dur, tempcd});
			dur += tempcd;
			tempcd = 0;
		}
	}
	void Character::fitOGCDAuto(int maxSearch = 10000) 
	{
		int dur = 0;
		int temp = 0;
		for (int i = 0; i < skills.size(); i++) {
			int in = getLatestGeneralUseForIndex(i);
			dur = generalTicks.at(in).ms + getAnimationLockForSkill(generalTicks.at(in).skill);
			temp = dur;
			if (!skills.at(i).skill->gcd)
			{
				
				do {
					int t = inUsableRange(i, dur);
					int d = t - dur;

					int index = getNextUsedGeneralIndexByTime(t);
					generalTicks.insert(generalTicks.begin() + index, { skills.at(i).skill, t, skills.at(i).skill->recast});

					pushSkillTick(i, t);
					dur = t + skills.at(i).skill->cd;
				} while (dur <= t_stats.at(id).dur);

			}

			//temp += getAnimationLockForSkill(i);
		}
	}

	//constructors and stuff

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
	Character& Character::instance()
	{
		return *this;
	}
}


