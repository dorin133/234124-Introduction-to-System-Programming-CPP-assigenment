#include "Medic.h"
#define RELOAD_MEDIC 5
#define MEDIC_MOVEMENT_RANGE 5
#define NO_LIFE 0 

namespace mtm
{
    Medic::Medic(int health, int ammo, int attack_range, int power, Team team,  int x, int y) :
            Character(health, ammo, attack_range, power, MEDIC_MOVEMENT_RANGE,
            MEDIC, team, x, y) {}

    void Medic::reload()
    {
        ammo+=RELOAD_MEDIC;
    }
    
    Medic* Medic::CloneImplementation() const
    {
        return new Medic(*this);
    }

    std::shared_ptr<Character> Medic::clone() const
    {
       return std::shared_ptr<Character>(CloneImplementation());
    }

    void Medic::attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board)
    {
        if(GridPoint::distance(location, attacked) <= attack_range)
        {              
            if(board(attacked.row, attacked.col) == nullptr || 
                location == attacked)
            {
                isEnoughAmmo();
                throw IllegalTarget();
            }
            if (board(attacked.row, attacked.col)->getTeam() != team)
            {
                isEnoughAmmo();
                ammo--;
                board(attacked.row, attacked.col)->setHealth() -= power;
                if(board(attacked.row, attacked.col)->getHealth() <= NO_LIFE)
                {
                    board(attacked.row, attacked.col) = nullptr;
                }
            }
            else
            {
                board(attacked.row, attacked.col)->setHealth() += power;
            }
            return;
        }
        throw OutOfRange();
    }
}