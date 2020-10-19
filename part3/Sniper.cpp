#include "Sniper.h"
#define RELOAD_SNIPER 2
#define SNIPER_MOVEMENT_RANGE 4
#define NO_LIFE 0
#define THIRD_ATTACK 3

namespace mtm
{
    Sniper::Sniper(int health, int ammo, int attack_range, int power, Team team,  int x, int y) :
            Character(health, ammo, attack_range, power, SNIPER_MOVEMENT_RANGE,
            SNIPER, team, x, y), shots_counter(0) {}
    
    void Sniper::reload()
    {
        ammo+=RELOAD_SNIPER;
    }
    
    Sniper* Sniper::CloneImplementation() const
    {
        return new Sniper(*this);
    }

    std::shared_ptr<Character> Sniper::clone() const
    {
        return std::shared_ptr<Character>(CloneImplementation());
    }

    void Sniper::attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board)
    {
        if(GridPoint::distance(location, attacked) <= attack_range &&
           GridPoint::distance(location, attacked) >= std::ceil((double)attack_range/2))
        {
            isEnoughAmmo();
            if (board(attacked.row, attacked.col) != nullptr 
                && board(attacked.row, attacked.col)->getTeam() != team)
            {
                ammo--;
                shots_counter++;
                if(shots_counter==THIRD_ATTACK)
                {
                    shots_counter=0;
                    board(attacked.row, attacked.col)->setHealth() -= (power*2);
                }
                else
                {
                    board(attacked.row, attacked.col)->setHealth() -= (power);                   
                }
                if(board(attacked.row, attacked.col)->getHealth() <= NO_LIFE)
                {
                    board(attacked.row, attacked.col) = nullptr;
                    return;
                }
                return;
            }
            throw IllegalTarget();
        }
        throw OutOfRange();
    }
}