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

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(JobClass, skillList, effects, statusEffects, job);

		Skill getSkillForId(int id);

	};
	extern std::vector<JobClass> jobClass;
	extern std::vector<JobClass> getUniqueJobClasses();


	//inline void to_json(json& j, const JobClass& p) {
	//	j = json{ p.skillList, p.effects, p.statusEffects, p.job };
	//}
	
	//inline void from_json(const json& j, JobClass& p) {
	//	try {
	//		for (auto i = j.at("skillList").begin(); i != j.at("skillList").end(); i++)
	//			p.skillList.push_back(i.value());
	//		j.at("effects").get_to(p.effects);
	//		j.at("statusEffects").get_to(p.statusEffects);
	//		j.at("job").get_to(p.job);
	//	}
	//	catch (const json::type_error& e)	{
	//		std::cout << e.what() << std::endl;
	//	}
	//
	//}

}

#endif // !CLASSES



