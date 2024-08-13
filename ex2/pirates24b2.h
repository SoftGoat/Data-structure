// 
// 234218 Data Structures 1.
// Semester: 2024B (spring).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef PIRATESA2_H_
#define PIRATESA2_H_

#include <memory>
#include "wet2util.h"
#include "DisjointSet.h" 
#include "HashTable.h"
#include "fleet.h"
#include "pirate.h"

class oceans_t {
private:
    /**
     *  @return pirate rank.
     */
    output_t<int> get_pirate_rank(int pirateId) const;
    int getPirateRank(int pirateId) const;
    std::shared_ptr<fleet> find_fleet(int fleetId);

    DisjointSet<std::shared_ptr<fleet>, int> m_fleet;
    HashTable<int, std::shared_ptr<pirate>> m_pirates;
    
public:
	// <DO-NOT-MODIFY> {

    oceans_t();

	virtual ~oceans_t();

    StatusType add_fleet(int fleetId);

    StatusType add_pirate(int pirateId, int fleetId);

    StatusType pay_pirate(int pirateId, int salary);

    output_t<int> num_ships_for_fleet(int fleetId);

    output_t<int> get_pirate_money(int pirateId);

    StatusType unite_fleets(int fleetId1, int fleetId2);

    StatusType pirate_argument(int pirateId1, int pirateId2);
	
	// } </DO-NOT-MODIFY>
};

#endif // PIRATESA2_H_
