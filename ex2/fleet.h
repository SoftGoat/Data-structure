#ifndef FLEET_H
#define FLEET_H

class fleet{
    private:
    int m_id;
    int m_num_of_ships;
    int m_num_of_pirates;


    public:
    fleet(int id); 
    int get_id() const;
    int get_num_of_ships() const;
    void increase_ship_count();
    int get_num_of_pirates() const;
    void increase_pirate_count();
    int get_key() const;
};

#endif // FLEET_H
