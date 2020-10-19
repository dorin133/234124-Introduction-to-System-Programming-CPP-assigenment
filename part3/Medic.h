#ifndef EX3_MEDIC
#define EX3_MEDIC
#include "Character.h"


namespace mtm
{
    class Medic : public Character
    {
        private:
            /**
             * private mthod for clone method.
             */
            Medic* CloneImplementation() const;
        public:
            /**
             * c'tor for Medic.
             * @param: health, ammo, attack_range, power,team, x, y
             *         (x,y)- coordinate for the Medic       
             * 
             * return value: a Medic type.
             */
            Medic(int health, int ammo, int attack_range, int power, Team team, int x, int y);

             /**
             * reload - add ammo to a Medic in RELOAD_MEDIC=5 amount
             * @param: none      
             * 
             * return value: none
             */
            void reload() override; 

            /**
             * attack - make an attack on the Character* in GridPoint attacked
             *          as requiered in the exercise's guide for Medic      
             * 
             * @param: a GridPoint of the attacked Character*, the game board      
             * 
             * return value: none
             */    
            void attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board) override;

            /**
             * clone - make a copy(by value) of a Medic given as a
             *         std::shared_ptr<Character>(return it in the same format)
             * @param: none    
             * 
             * return value: std::shared_ptr<Character> (a Character* pointer to Medic)
             */ 
            std::shared_ptr<Character> clone() const override;
            Medic& operator=(const Medic& other) = default;
            Medic(const Medic& other) = default;
            ~Medic() override {}             
    };
}
#endif //EX3_MEDIC

            
            