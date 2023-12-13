#pragma once
#include <vector>
#include "helper.h"
#include "classes.h"

namespace FFRot {
	JobClass::JobClass(Job j) {
		skillList = { Skill() };
		effects = { Effect() };
		statusEffects = { StatusEffect() };

		job = j;
	}
	std::vector<JobClass> jobClass = {};
	std::vector<JobClass> getUniqueJobClasses() { 
		std::vector<JobClass> ret;
		if (jobClass.empty()) {
			for (int i = 0; i < int(Job::WHM); i = i + 1) {
				ret.push_back(JobClass(Job(i)));
			}
			return ret;
		}
		return jobClass;
	}

}