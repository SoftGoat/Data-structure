#include <memory>
#include "fleet.h"

class pirate{
    private:
    int m_id;
    int m_coins;
    int m_rank;
    std::shared_ptr<fleet> m_fleet;

    public:
    pirate(int id);
    int get_id() const;
    int get_coins() const;
    int get_rank() const;
    void set_coins(int coins);
    void add_coins(int salary);
    void set_rank(int rank);
    std::shared_ptr<fleet> get_fleet() const;
    void set_fleet(std::shared_ptr<fleet> fleet);

};