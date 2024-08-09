#include "pirates24b2.h"

oceans_t::oceans_t() : m_fleet(), m_pirates() {}

oceans_t::~oceans_t()
{
	// TODO: Your code goes here
}

output_t<int> oceans_t::get_pirate_rank(int pirateId) const
{
	return output_t<int>(getPirateRank(pirateId));
}

int oceans_t::getPirateRank(int pirateId) const{
	// We will assume that the pirate exsits.
	std::shared_ptr<pirate> pirate = m_pirates.get(pirateId);
	int fleet_rank = m_fleet.getRank(pirate->get_fleet()->get_id());
	int pirate_rank = pirate->get_rank();
	return pirate_rank + fleet_rank;
}

StatusType oceans_t::add_fleet(int fleetId)
{
	// Add fleet with this Id.
	if(fleetId <= 0){
		return StatusType::INVALID_INPUT;
	}

	std::shared_ptr<fleet> newFleet;
	try{
		newFleet = std::shared_ptr<fleet>(new fleet(fleetId));
	} catch(const std::bad_alloc& e){
		return StatusType::ALLOCATION_ERROR;
	}
	
	// Try to add the new fleet, return failure and delete the fleet if faild.
	try{
		m_fleet.makeSet(newFleet);
	} catch(const std::invalid_argument& e){
		return StatusType::FAILURE;
	}

	return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
	if(fleetId <= 0 || pirateId <= 0){
		return StatusType::INVALID_INPUT;
	}

	std::shared_ptr<pirate> newPirate;
	try{
		newPirate = std::unique_ptr<pirate>(new pirate(pirateId));
	} catch(const std::bad_alloc& e){
		return StatusType::ALLOCATION_ERROR;
	}

	if(m_pirates.contains(pirateId)){
		// There is already a pirate with pirateId.
		return StatusType::FAILURE;
	}
	std::shared_ptr<fleet> new_pirate_fleet;
	try{
		new_pirate_fleet = m_fleet.find(fleetId);
	} catch(const std::invalid_argument& e){
		// There is no fleet with id fleetID.
		printf("fleetId: %d\n", fleetId);
		return StatusType::FAILURE;
	}

	// Insert the pirate with his ID as a key.
	m_pirates.insert(newPirate->get_id(), newPirate);
	newPirate->set_fleet(new_pirate_fleet);
	newPirate->set_rank(new_pirate_fleet->get_num_of_pirates() + 1);
	new_pirate_fleet->increase_pirate_count();
	return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	if(pirateId <= 0 || salary <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!m_pirates.contains(pirateId)){
		return StatusType::FAILURE;
	}
	std::shared_ptr<pirate> our_pirate = m_pirates.get(pirateId);
	our_pirate->add_coins(salary);
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    if(fleetId <= 0){
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	
	std::shared_ptr<fleet> our_fleet;
	try{
		our_fleet = m_fleet.find(fleetId);
	} catch(const std::invalid_argument& e){
		// There is no fleet with id fleetId.
		return output_t<int>(StatusType::FAILURE);
	}

	return output_t<int>(our_fleet->get_num_of_ships());
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    if(pirateId <= 0){
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if(!m_pirates.contains(pirateId)){
		return output_t<int>(StatusType::FAILURE);
	}
	std::shared_ptr<pirate> our_pirate = m_pirates.get(pirateId);
	return output_t<int>(our_pirate->get_coins());
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
	if(fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2){
		return StatusType::INVALID_INPUT;
	}
	std::shared_ptr<fleet> fleet_1;
	std::shared_ptr<fleet> fleet_2;

	// Check if fleets exist.
	try{
		fleet_1 = m_fleet.find(fleetId1);
		fleet_2 = m_fleet.find(fleetId2);
	} catch(const std::invalid_argument &e){
		return StatusType::FAILURE;
	}
	// Check if fleets are empty.
	if(fleet_1->get_num_of_pirates() == 0 || fleet_2->get_num_of_pirates() == 0){
		return StatusType::FAILURE;
	}
	// else, unite!
	m_fleet.unite(fleetId1, fleetId2);
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    if(pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2){
		return StatusType::INVALID_INPUT;
	}

	if(!m_pirates.contains(pirateId1) || !m_pirates.contains(pirateId2)){
		return StatusType::FAILURE;
	}
	// The pirates exsists.
	std::shared_ptr<pirate> pirate_1 = m_pirates.get(pirateId1);
	std::shared_ptr<pirate> pirate_2 = m_pirates.get(pirateId2);
	// Check if are on the same fleet.
	if(pirate_1->get_fleet() != pirate_2->get_fleet()){
		return StatusType::FAILURE;
	}

	int pirate_1_rank = getPirateRank(pirateId1);
	int pirate_2_rank = getPirateRank(pirateId2);
	int rank_diff = pirate_2_rank - pirate_1_rank;
	// This way always the BIG rank pay the small rank, beautifully.
	pirate_1->add_coins(rank_diff);
	pirate_2->add_coins(-rank_diff);
    return StatusType::SUCCESS;
}
