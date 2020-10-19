#include "Soldier.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#define RELOAD_SOLDIER 3
#define SOLDIER_MOVEMENT_RANGE 3
#define NO_LIFE 0
namespace mtm
{
    Soldier::Soldier(int health, int ammo, int attack_range, int power, Team team,  int x, int y) :
            Character(health, ammo, attack_range, power, SOLDIER_MOVEMENT_RANGE,
            SOLDIER, team, x, y) {}

    void Soldier::reload()
    {
        ammo+=RELOAD_SOLDIER;
    }
    
    Soldier* Soldier::CloneImplementation() const
    {
        return new Soldier(*this);
    }

    std::shared_ptr<Character> Soldier::clone() const
    {
        return std::shared_ptr<Character>(CloneImplementation());
    }

    void Soldier::attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board)
    {
        if (GridPoint::distance(attacked, getLocation()) > attack_range)
        {
            throw OutOfRange();      
        }
        isEnoughAmmo();       
        if (((std::abs(attacked.col - location.col)) <= attack_range && 
            attacked.row ==  location.row) ||
           (std::abs(attacked.row - location.row) <= attack_range && 
            (attacked.col == location.col)))
        {
            ammo--;
            double temp = (double)attack_range/3;
            int surrounding_attack = std::ceil(temp);
            for(Matrix<std::shared_ptr<Character>>::iterator it = board.begin(); it != board.end(); it++)
            {
                if(*it != nullptr && (*it)->getTeam() != team)
                {
                    if(GridPoint::distance(attacked, (*it)->getLocation()) <= surrounding_attack)
                    {
                        if(attacked == (*it)->getLocation()) 
                        {
                            (*it)->setHealth() -= power;
                        }
                        else
                        {
                            int damage = std::ceil((double)power/2);
                            (*it)->setHealth() -= damage;
                        }
                        if((*it)->getHealth() <= NO_LIFE)
                        {
                            *it = nullptr;
                        }
                    }
                }               
            }
            return;
        }
        throw IllegalTarget();
    }
}