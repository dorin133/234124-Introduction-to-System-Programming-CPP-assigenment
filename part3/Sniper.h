#ifndef EX3_SNIPER
#define EX3_SNIPER
#include "Character.h"

namespace mtm
{
    class Sniper : public Character
    {
        private:
            /*
             * private method for clone method.
             */
            Sniper* CloneImplementation() const;
            int shots_counter;
        public:
            /**
             * c'tor for Sniper.
             * @param: health, ammo, attack_range, power,team, x, y
             *         (x,y)- coordinate for the Sniper       
             * 
             * return value: a Sniper type.
             */
            Sniper(int health, int ammo, int attack_range, int power, Team team, int x, int y);
            
            /**
             * reload - add ammo to a Snipper in RELOAD_SNIPER=2 amount
             * @param: none      
             * 
             * return value: none
             */
            void reload() override;
            
            /**
             * attack - make an attack on the Character* in GridPoint attacked
             *          as requiered in the exercise's guide for Sniper      
             * 
             * @param: a GridPoint of the attacked Character*, the game board      
             * 
             * return value: none
             */             
            void attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board) override;
            
            /**
             * clone - make a copy(by value) of a Sniper given as a
             *         std::shared_ptr<Character>(return it in the same format)
             * @param: none    
             * 
             * return value: std::shared_ptr<Character> (a Character* pointer to Sniper)
             */           
            std::shared_ptr<Character> clone() const override;
            Sniper& operator=(const Sniper& other) = default;
            Sniper(const Sniper& other) = default;
            ~Sniper() override {} 
    };
}
#endif //EX3_SNIPER
            