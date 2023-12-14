#pragma once
#include <vector>
#include "helper.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

#ifndef CLASSES
#define CLASSES



namespace FFRot {
	class JobClass
	{
	public:
		JobClass();
		JobClass(Job j);
		std::vector<Skill> skillList;
		std::vector<Effect> effects;
		std::vector<StatusEffect> statusEffects;

		Job job;

	};
	extern std::vector<JobClass> jobClass;
	extern std::vector<JobClass> getUniqueJobClasses();


	inline void to_json(json& j, const JobClass& p) {
		j = json{ p.skillList, p.effects, p.statusEffects, p.job };
	}

	inline void from_json(const json& j, JobClass& p) {
		try {
			j[0].at("skillList").get_to(p.skillList);
			j[0].at("effects").get_to(p.effects);
			j[0].at("statusEffects").get_to(p.statusEffects);
			p.job = Job(j[0]["job"]);
		}
		catch (const json::type_error& e)	{
			std::cout << e.what() << std::endl;
		}

	}

}

#endif // !CLASSES



