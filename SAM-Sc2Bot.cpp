#include "SAM_Sc2Bot.h"

void SAM_Sc2Bot::OnGameStart() 
{ 
	prodMngr = new ProductionManager();
	combatMngr = new CombatManager();
	bases.push_back(new Base(Observation()->GetStartLocation()));

	expansionLocations = search::CalculateExpansionLocations(Observation(), Query(), search::ExpansionParameters());
	SortExpansionLocations();
	std::cout << "Start Location (X= " << bases[0]->origin.x << " Y= " << bases[0]->origin.y << ")" <<  std::endl;

	return; 
}

void SAM_Sc2Bot::OnGameEnd() {
	std::vector<PlayerResult> res = Observation()->GetResults();

	std::cout << "Game Over" << std::endl;
	for(auto r : res){
		std::cout << r.player_id << r.result << std::endl;
	}
	
	delete prodMngr;
	delete combatMngr;
	for (auto b : bases) {
		delete b;
	}
}

void SAM_Sc2Bot::OnStep()
{
	step_count++;
	if (step_count % 1000 == 0) {
		std::cout << "STEP:" << step_count << std::endl;
	}

	// Update variables representing the game state for both managers.
	prodMngr->SetGameStateVars(Observation(), Actions(), bases, expansionLocations);
	combatMngr->SetGameStateVars(Observation(), Actions(), bases, expansionLocations);

	// Try to build any needed structures according to what resources/buildings we have now.
	prodMngr->BuildStructures();

	// When 1 marine has been trained for each possible enemy base location, send them to scout
	combatMngr->FindEnemyBase();

	// After ~3.5 minutes, start expanding into nearby resource sites
	if ((step_count % 5000) == 0) {
		AddBase();
	}

	// After ~8 minutes, begin gathering army near enemy base
	if ((step_count < 11000) && (step_count > 10500)) {
		if (step_count == 10501) {
			combatMngr->CalculateGatherLocation();
		}
		combatMngr->GatherNearEnemy();
	}
	// After ~8.25 minutes, begin attacking the main enemy base.
	if (step_count >= 11000) {
		combatMngr->AllOutAttackEnemy();
	}

	// Attack enemies close to our base but don't pursue them past a certain distance
	combatMngr->AttackEnemy();
	
}

void SAM_Sc2Bot::OnUnitIdle(const Unit* unit)
{
	// Update variables representing the game state for both managers.
	prodMngr->SetGameStateVars(Observation(), Actions(), bases, expansionLocations);
	combatMngr->SetGameStateVars(Observation(), Actions(), bases, expansionLocations);

	switch (unit->unit_type.ToType()) {
		// buildings
		case UNIT_TYPEID::TERRAN_COMMANDCENTER:
		{
			prodMngr->OnIdleCommandCenter(unit); break;
		}

		case UNIT_TYPEID::TERRAN_BARRACKS:
		{
			prodMngr->OnIdleBarracks(unit); break;
		}

		case UNIT_TYPEID::TERRAN_FACTORY:
		{
			prodMngr->OnIdleFactory(unit); break;
		}

		case UNIT_TYPEID::TERRAN_ENGINEERINGBAY:
		{
			prodMngr->OnIdleEngineeringBay(unit);  break;
		}

		case UNIT_TYPEID::TERRAN_ARMORY:
		{
			prodMngr->OnIdleArmory(unit); break;
		}

		case UNIT_TYPEID::TERRAN_ORBITALCOMMAND:
		{
			prodMngr->OnIdleOrbitalCommand(unit);  break;
		}

		// units
		case UNIT_TYPEID::TERRAN_SCV:
		{
			prodMngr->OnIdleSCV(unit); break;
		}

		case UNIT_TYPEID::TERRAN_MARINE:
		{
			combatMngr->OnIdleMarine(unit); break;
		}

		case UNIT_TYPEID::TERRAN_REAPER:
		{
			combatMngr->OnIdleReaper(unit); break;
		}

		default:
		{
			break;
		}
	}
}

void SAM_Sc2Bot::SortExpansionLocations() {
	const GameInfo& game_info = Observation()->GetGameInfo();
	Point3D tempPoint, point1, point2;
	int distance1, distance2;
	bool stillSwapping = false;

	//Add enemy start locations as possible expansion points
	for (size_t i = 0; i < game_info.enemy_start_locations.size(); i++) {
		Point3D extraLoc = Point3D(game_info.enemy_start_locations[i].x, game_info.enemy_start_locations[i].y, 0);
		expansionLocations.push_back(extraLoc);
	}

	for (size_t i = 0; i < expansionLocations.size(); i++) {
		for (size_t j = 0; j < expansionLocations.size()-i-1; j++) {
			point1 = expansionLocations[j];
			point2 = expansionLocations[j+1];
			distance1 = Distance2D(Observation()->GetStartLocation(), point1);
			distance2 = Distance2D(Observation()->GetStartLocation(), point2);

			if (distance1 > distance2) {
				//Swap them
				tempPoint = expansionLocations[j];
				expansionLocations[j] = expansionLocations[j + 1];
				expansionLocations[j + 1] = tempPoint;
				stillSwapping = true;
			}
		}
		if (!stillSwapping) {
			break;
		}
	}
}

bool SAM_Sc2Bot::AddBase() {
	
	// Expansion locations are sorted by proximity
	if (bases.size() < 3) {
		if (bases.size() < expansionLocations.size()) {
			Point2D newLocation = Point2D(expansionLocations[bases.size()-1].x, expansionLocations[bases.size()-1].y);
			bases.push_back(new Base(newLocation));
			std::cout << "Added a new base " << "X: " << newLocation.x << " Y: " << newLocation.y << std::endl;
			return true;
		}
	}
	return false;
}