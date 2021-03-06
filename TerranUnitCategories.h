#pragma once
#include "sc2api/sc2_api.h"
#include "sc2api/sc2_args.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"
#include "sc2utils/sc2_arg_parser.h"
#include <sc2api\sc2_unit_filters.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>

using namespace sc2;

/**
	Each class returns the data structure listed in the type definition at the
	top of the class. 
	Some example uses:
		1. Iterate over a list of Barracks units:
			for (auto unit_type : TerranUnitCategories::BARRACKS_UNITS()) { ... }
		2. Given a unit_type ut (e.g. UNIT_TYPEID::TERRAN_MARINE), get the 
		   train ability for Command centers:
			ABILITY_ID train_ability = TerranUnitTrainAbilities::BARRACKS_UNITS()[ut]
*/

class TerranUnitCategories {
	typedef std::list<UNIT_TYPEID> UnitTypeList;

public:
	static const UnitTypeList ALL_COMBAT_UNITS() {
		return { UNIT_TYPEID::TERRAN_VIKINGFIGHTER,
			UNIT_TYPEID::TERRAN_RAVEN,
			UNIT_TYPEID::TERRAN_MEDIVAC,
			UNIT_TYPEID::TERRAN_BATTLECRUISER,
			UNIT_TYPEID::TERRAN_LIBERATOR,
			UNIT_TYPEID::TERRAN_BANSHEE,
			UNIT_TYPEID::TERRAN_MARINE,
			UNIT_TYPEID::TERRAN_MARAUDER,
			UNIT_TYPEID::TERRAN_REAPER,
			UNIT_TYPEID::TERRAN_GHOST,
			UNIT_TYPEID::TERRAN_HELLION,
			UNIT_TYPEID::TERRAN_SIEGETANK,
			UNIT_TYPEID::TERRAN_CYCLONE,
			UNIT_TYPEID::TERRAN_WIDOWMINE,
			UNIT_TYPEID::TERRAN_THOR
		};
	};

	static const UnitTypeList STARPORT_UNITS() {
		return { UNIT_TYPEID::TERRAN_VIKINGFIGHTER,
			UNIT_TYPEID::TERRAN_RAVEN,
			UNIT_TYPEID::TERRAN_MEDIVAC,
			UNIT_TYPEID::TERRAN_BATTLECRUISER,
			UNIT_TYPEID::TERRAN_LIBERATOR,
			UNIT_TYPEID::TERRAN_BANSHEE
		};
	}

	static const UnitTypeList COMMANDCENTER_UNITS() {
		return { UNIT_TYPEID::TERRAN_SCV,
			UNIT_TYPEID::TERRAN_MULE
		};
	}

	static const UnitTypeList BARRACKS_UNITS() {
		return { UNIT_TYPEID::TERRAN_MARINE,
			UNIT_TYPEID::TERRAN_MARAUDER,
			UNIT_TYPEID::TERRAN_REAPER,
			UNIT_TYPEID::TERRAN_GHOST
		};
	}

	static const UnitTypeList FACTORY_UNITS() {
		return { UNIT_TYPEID::TERRAN_HELLION,
			UNIT_TYPEID::TERRAN_SIEGETANK,
			UNIT_TYPEID::TERRAN_CYCLONE,
			UNIT_TYPEID::TERRAN_WIDOWMINE,
			UNIT_TYPEID::TERRAN_THOR
		};
	}
};

class TerranBuildings {
	typedef std::list<UNIT_TYPEID> UnitTypeList;

	static const UnitTypeList ALL_BUILDINGS() {
		return {
			UNIT_TYPEID::TERRAN_COMMANDCENTER, 
			UNIT_TYPEID::TERRAN_ENGINEERINGBAY, 
			UNIT_TYPEID::TERRAN_MISSILETURRET,
			UNIT_TYPEID::TERRAN_SENSORTOWER,   
			UNIT_TYPEID::TERRAN_PLANETARYFORTRESS, 
			UNIT_TYPEID::TERRAN_REFINERY,
			UNIT_TYPEID::TERRAN_SUPPLYDEPOT, 
			UNIT_TYPEID::TERRAN_BARRACKS, 
			UNIT_TYPEID::TERRAN_BUNKER,
			UNIT_TYPEID::TERRAN_GHOSTACADEMY, 
			UNIT_TYPEID::TERRAN_FACTORY, 
			UNIT_TYPEID::TERRAN_ORBITALCOMMAND,
			UNIT_TYPEID::TERRAN_ARMORY,
			UNIT_TYPEID::TERRAN_STARPORT, 
			UNIT_TYPEID::TERRAN_FUSIONCORE
		};
	};
};

class TerranUnitTrainAbilities {
	typedef std::map<UNIT_TYPEID, ABILITY_ID> UnitTrainAbilityMap;

public:
	static const UnitTrainAbilityMap STARPORT_UNITS() {
		return { { UNIT_TYPEID::TERRAN_VIKINGFIGHTER, ABILITY_ID::TRAIN_VIKINGFIGHTER },
			{ UNIT_TYPEID::TERRAN_RAVEN, ABILITY_ID::TRAIN_RAVEN },
			{ UNIT_TYPEID::TERRAN_MEDIVAC, ABILITY_ID::TRAIN_MEDIVAC },
			{ UNIT_TYPEID::TERRAN_LIBERATOR, ABILITY_ID::TRAIN_LIBERATOR },
			{ UNIT_TYPEID::TERRAN_BANSHEE, ABILITY_ID::TRAIN_BANSHEE },
			{ UNIT_TYPEID::TERRAN_BATTLECRUISER, ABILITY_ID::TRAIN_BATTLECRUISER }
		};
	}

	static const UnitTrainAbilityMap BARRACKS_UNITS() {
		return { { UNIT_TYPEID::TERRAN_MARINE, ABILITY_ID::TRAIN_MARINE },
			{ UNIT_TYPEID::TERRAN_REAPER, ABILITY_ID::TRAIN_REAPER },
			{ UNIT_TYPEID::TERRAN_MARAUDER, ABILITY_ID::TRAIN_MARAUDER },
			{ UNIT_TYPEID::TERRAN_GHOST, ABILITY_ID::TRAIN_GHOST }
		};
	}

	static const UnitTrainAbilityMap FACTORY_UNITS() {
		return { { UNIT_TYPEID::TERRAN_HELLION, ABILITY_ID::TRAIN_HELLION },
			{ UNIT_TYPEID::TERRAN_SIEGETANK, ABILITY_ID::TRAIN_SIEGETANK },
			{ UNIT_TYPEID::TERRAN_CYCLONE, ABILITY_ID::TRAIN_CYCLONE },
			{ UNIT_TYPEID::TERRAN_WIDOWMINE, ABILITY_ID::TRAIN_WIDOWMINE },
			{ UNIT_TYPEID::TERRAN_THOR, ABILITY_ID::TRAIN_THOR }
		};
	}
};