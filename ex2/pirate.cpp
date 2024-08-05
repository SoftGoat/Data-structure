#include "pirate.h"

pirate::pirate(int id) : m_id(id), m_coins(0), m_fleet(nullptr){};

int pirate::get_id() const {
    return m_id;
}

int pirate::get_coins() const {
    return m_coins;
}

int pirate::get_rank() const{
    return m_rank;
}

void pirate::set_coins(int coins) {
    m_coins = coins;
}

void pirate::add_coins(int salary) {
    m_coins += salary;
}

void pirate::set_rank(int rank){
    m_rank = rank;
}

std::shared_ptr<fleet> pirate::get_fleet() const {
    return m_fleet;
}

void pirate::set_fleet(std::shared_ptr<fleet> fleet) {
    m_fleet = fleet;
}

int pirate::get_key() const {
    return m_id;
}
