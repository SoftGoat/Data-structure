#include "fleet.h"

fleet::fleet(int id) : m_id(id), m_num_of_ships(1), m_num_of_pirates(0) {}

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

int fleet::get_rank() const {
    return m_num_of_pirates;
}
