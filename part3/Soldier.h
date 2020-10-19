#ifndef EX3_SOLDIER
#define EX3_SOLDIER
#include "Character.h"

namespace mtm
{
    class Soldier : public Character
    {
        private:
            /**
             * private method for clone method.
             */
            Soldier* CloneImplementation() const;
        public:
            /**
             * c'tor for Soldier.
             * @param: health, ammo, attack_range, power,team, x, y
             *         (x,y)- coordinate for the Soldier       
             * 
             * return value: a Soldier type.
             */
            Soldier(int health, int ammo, int attack_range, int power, Team team, int x, int y);
            /**
             * reload - add ammo to a Soldier in RELOAD_SOLDIER=3 amount
             * @param: none      
             * 
             * return value: none
             */
            void reload() override; 
            ~Soldier() override {} 
            /**
             * clone - make a copy(by value) of a Soldier given as a
             *         std::shared_ptr<Character>(return it in the same format)
             * @param: none    
             * 
             * return value: std::shared_ptr<Character> (a Character* pointer to Soldier)
             */
            std::shared_ptr<Character> clone() const override;
            Soldier& operator=(const Soldier& other) = default;
            Soldier(const Soldier& other) = default;
            /**
             * attack - make an attack on the Character* in GridPoint attacked
             *          as requiered in the exercise's guide      
             * 
             * @param: a GridPoint of the attacked Character*, the game board      
             * 
             * return value: none
             */
            void attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board) override;
    };
}
#endif //EX3_SOLDIER
