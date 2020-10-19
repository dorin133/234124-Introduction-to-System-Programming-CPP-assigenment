#ifndef EX3_Character
#define EX3_Character
#include "Auxiliaries.h"
#include "Matrix.h"
#include <memory>

namespace mtm {
    class Character 
    {
        protected:
            int health;
            int ammo;
            int attack_range;
            int power;
            const int movement_range;   
            CharacterType unit_type;
            Team team;
            GridPoint location;
            
        public:
            const GridPoint& getLocation() const
            {
                return location;
            }

            GridPoint& setLocation()
            {
                return location;
            }

            const CharacterType& getUnitType() const
            {
                return unit_type;
            }

            const Team& getTeam() const
            {
                return team;
            }
            
            const int& getHealth() const
            {
                return health;
            }
            
            const int& getRange() const
            {
                return attack_range;
            }

            const int& getPower() const
            {
                return power;
            }
            
            const int& getMovementRange() const
            {
                return movement_range;
            }

            int& setHealth() 
            {
                return health;
            }
            /**
             * c'tor for Character.
             * @param: health, ammo, attack_range,power, movement_range, unit_type, team, x, y
             *         (x,y)- coordinate for the character       
             * 
             * return value: a Character type.
             */
            Character(int health, int ammo, int attack_range, int power, const int movement_range,
            CharacterType unit_type, Team team, int x, int y) :
            health(health), ammo(ammo), attack_range(attack_range),power(power),movement_range(movement_range),
            unit_type(unit_type), team(team), location(x,y) {}
            /**
             * isEnoughAmmo - check if the Character has enough ammo to attack
             * @param: none      
             * 
             * return value: void function (throw in case if there is'nt enough ammo)
             */
            void isEnoughAmmo() const
            {
                if(ammo <= 0)
                {
                    throw OutOfAmmo();
                }
            }
            
            /**
             * reload - add ammo to a Character (amount depends on the certain Character)
             * @param: none      
             * 
             * return value: none
             */
            virtual void reload() = 0;
             /**
             * attack - make an attack on the character in GridPoint attacked.
             * @param: a GridPoint of the attacked Character*, the game board      
             * 
             * return value: none
             */
            virtual void attack(const GridPoint& attacked, Matrix<std::shared_ptr<Character>>& board) = 0;
            /**
             * clone - create a copy of a std::shared_ptr<Character> without doing slicing 
             *          
             * @param: none    
             * 
             * return value: std::shared_ptr<Character> (a Character* pointer [sniper/medic/soldier])
             */
            virtual std::shared_ptr<Character> clone() const = 0;
            Character& operator=(const Character& other) = default;
            Character(const Character& other) = default;
            virtual ~Character() {}
    };
}
#endif //EX3_Character

