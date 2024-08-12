#include "fleet.h"

fleet::fleet(int id) : m_id(id), m_num_of_ships(1), m_num_of_pirates(0), m_is_accessible(true) {}

int fleet::get_id() const {
    return m_id;
}

int fleet::get_num_of_ships() const {
    return m_num_of_ships;
}

void fleet::increase_ship_count(){
    m_num_of_ships++;
}

int fleet::get_num_of_pirates() const {
    return m_num_of_pirates;
}

void fleet::increase_pirate_count(){
    m_num_of_pirates++;
}

int fleet::get_key() const {
    return m_id;
}

void fleet::set_id(int id){
    m_id = id;
}
void fleet::set_num_of_ships(int ships){
    m_num_of_ships = ships;
}
void fleet::set_num_of_pirates(int pirates){
    m_num_of_pirates = pirates;
}

void fleet::disable(){
    m_is_accessible = false;
}

bool fleet::is_accessible() const{
    return m_is_accessible;
}
