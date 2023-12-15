#pragma once
#include <vector>
#include "helper.h"
#include "classes.h"
#include "fmt/format.h"

namespace FFRot {
	JobClass::JobClass()
	{
		skillList = {};
		effects = {};
		statusEffects = {};

		job = Job::NONE;
	}
	JobClass::JobClass(Job j) {
		skillList = { Skill() };
		effects = { Effect() };
		statusEffects = { StatusEffect() };

		job = j;
	}
	Skill JobClass::getSkillForId(int id)
	{
		try {
			for (auto it : skillList) {
				if (it.id == id) return it;
			}
			throw std::runtime_error( fmt::format("Bad skill id: {}", id) );
		}
		catch (const std::runtime_error* e) {
			std::cout << e->what() << std::endl;
		}
	}
	std::vector<JobClass> jobClass = getUniqueJobClasses();

	std::vector<JobClass> getUniqueJobClasses() { 
		std::vector<JobClass> ret;
		if (jobClass.empty()) {
			for (int i = 0; i < 4; i = i + 1) {
				ret.push_back(JobClass(JobA[i]));
			}
			return ret;
		}
		return jobClass;
	}

}