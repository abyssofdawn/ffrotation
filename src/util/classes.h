#pragma once
#include <vector>
#include "helper.h"

#ifndef CLASSES
#define CLASSES



namespace FFRot {
	class JobClass
	{
	public:

		JobClass(Job j);
		std::vector<Skill> skillList;
		std::vector<Effect> effects;
		std::vector<StatusEffect> statusEffects;

		Job job;


		NLOHMANN_DEFINE_TYPE_INTRUSIVE(JobClass, skillList, effects, statusEffects, job);

	};
	extern std::vector<JobClass> jobClass;
	extern std::vector<JobClass> getUniqueJobClasses();

}

#endif // !CLASSES



