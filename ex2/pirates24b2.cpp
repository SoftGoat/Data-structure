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

std::shared_ptr<fleet> oceans_t::find_fleet(int fleetId){
	std::shared_ptr<fleet> leaf_fleet = m_fleet.find_leaf(fleetId); // This will throw an excaption if not found.
	if(!leaf_fleet->is_accessible()){
		throw std::invalid_argument("Fleet is Not Accessible");
	}
	return m_fleet.find(fleetId);
}

int oceans_t::getPirateRank(int pirateId) const{
	// We will assume that the pirate exsits.
	std::shared_ptr<pirate> pirate = m_pirates.get(pirateId);
	int fleet_rank = m_fleet.getRank(pirate->get_fleet()->get_original_id());
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
		m_fleet.makeSet(newFleet, fleetId);
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
		new_pirate_fleet = find_fleet(fleetId);
	} catch(const std::invalid_argument& e){
		// There is no fleet with id fleetID.
		return StatusType::FAILURE;
	}

	// Insert the pirate with his ID as a key.
	m_pirates.insert(newPirate->get_id(), newPirate);
	newPirate->set_fleet(new_pirate_fleet);
	newPirate->set_rank(new_pirate_fleet->get_num_of_pirates() + 1);
	new_pirate_fleet->increase_pirate_count();
	m_fleet.addAbsRank(fleetId, 1);
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
		our_fleet = find_fleet(fleetId);
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
		fleet_1 = find_fleet(fleetId1);
		fleet_2 = find_fleet(fleetId2);
	} catch(const std::invalid_argument &e){
		return StatusType::FAILURE;
	}

	int pirates_1 = fleet_1->get_num_of_pirates();
	int pirates_2 = fleet_2->get_num_of_pirates();

	// Check if fleets are empty.
	if( pirates_1 == 0 || pirates_2 == 0){
		return StatusType::FAILURE;
	}
	// else, unite!
	m_fleet.unite(fleetId1, fleetId2);

	// Change the fleet that is at the top of the Up Tree containing the fleets -
	// to be the fleet with the most pirates.
	std::shared_ptr<fleet> new_fleet = m_fleet.find(fleetId1);
	// Change the fields of the new fleet.
	new_fleet->set_num_of_ships(fleet_1->get_num_of_ships() + fleet_2->get_num_of_ships());
	new_fleet->set_num_of_pirates(pirates_1 + pirates_2);
	if(pirates_1 >= pirates_2){ // The fleet with fleetId1 should be at the top of the Up Tree.
		new_fleet->set_id(fleet_1->get_id());
		// Set the other fleet as uneccesible.
		m_fleet.find_leaf(fleetId2)->disable();
		fleet_2->disable();
	}
	else{	// The fleet with fleetId2 should be at the top of the Up Tree.
		new_fleet->set_id(fleet_2->get_id());
		m_fleet.find_leaf(fleetId1)->disable();
		fleet_1->disable();
	}
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
	std::shared_ptr<fleet> true_fleet_1;
	std::shared_ptr<fleet> true_fleet_2;
	try{
		// We will find the true fleets of the pirates, therefore we will not care if the leaf fleet is not accessible.
		true_fleet_1 = m_fleet.find(pirate_1->get_fleet()->get_id());
		true_fleet_2 = m_fleet.find(pirate_2->get_fleet()->get_id());
	} catch(const std::invalid_argument &e){
		return StatusType::FAILURE; // Fleets do not exists.
	}
	if(true_fleet_1 != true_fleet_2){ // Check if on the same fleet.
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
