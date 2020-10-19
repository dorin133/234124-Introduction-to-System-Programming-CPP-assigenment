#ifndef EX3_Game
#define EX3_Game

#include "Exceptions.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"

namespace mtm
{
    class Game
    {
        private:
            /**
             * verifyLegalCell - check if the given point is at a legal coordinate on the game's board
             *                   (throw IllegalCell() in case not)
             * @param: height, width       
             * 
             * return value: none
             */
            void verifyLegalCell(const GridPoint& coordinates) const;
            
            /**
             * isEmptyCell - check if the given coordinate is an empty cell on the game's board
             *                   (throw CellEmpty in case not)
             * @param: height, width       
             * 
             * return value: none
             */ 
            void isEmptyCell(const GridPoint& coordinates) const;

            Matrix<std::shared_ptr<Character>> board;
        public:
             /**
             * c'tor for Game.
             * @param: height, width       
             * 
             * return value: a new empty Game 
             */
            explicit Game(int height, int width); 
            
            /**
             * d'tor for Game.
             */
            ~Game() {};

            /**
             * c'ctor for Game - create a copy of an existing game
             * @param: the game we want to make a copy of       
             * 
             * return value: a new Game that's identical to the game given as a param
             *               the new game does'nt point to the same adress for each coordinate 
             *               but rather to a copy of it 
             */
            Game(const Game& other_game); 

            /**
             * operator= for Game - change an existing game to be equal to the game 
             *                      given as a param
             * @param: the game we want to make a copy of       
             * 
             * return value: a new Game that's identical to the game given as a param
             *               the new game does'nt point to the same adress for each coordinate 
             *               but rather to a copy of it 
             */
            Game& operator=(const Game& other);

            /**
             * addCharacter - add a the given character in the GridPoint location given 
             *                to the game   
             * 
             * @param: a GridPoint of the new Character*, a shared_ptr to the character     
             * 
             * return value: none
             */   
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

            /**
             * makeCharacter - make a new character based on the given params
             * 
             * @param: type(soldier/medic/sniper), team(cpp/python), health, ammo, range, power     
             * 
             * return value: a shared_ptr<Character> pointer to the new Character
             */
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
                                                            units_t ammo, units_t range, units_t power);

            /**
             * move - move a character on the game's board from the source coordinate given to the 
             *        destination coordinate given
             * 
             * @param: source coordinate, destination coordinate as a GridPoint type  
             * 
             * return value: none
             */                                                 
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

            /**
             * attack - make an attack on the Character* in the destination coordinate
             *          as requiered in the exercise's guide for the character 
             *          in the source coordinate     
             * 
             * @param: source coordinate, destination coordinate as a GridPoint type     
             * 
             * return value: none
             */
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

             /**
             * reload - add ammo to a Character in the given coordinate of RELOAD_MEDIC=5 amount
             * @param: none      
             * 
             * return value: none
             */
            void reload(const GridPoint & coordinates);

            /**
             * operator<< - print the game board
             * @param: std::ostream, the game needed to be print     
             * 
             * return value: an ostream form representing the board's state
             */
            friend std::ostream& operator<<(std::ostream& os, const Game& game);

             /**
             * isOver - determine if the game is over. if over, return true and update Team*
             *          winningTeam to the winning team's identity if Team* winningTeam != NULL
             * @param: pointer of enum Team (may be NULL)   
             * 
             * return value: true/false if the game is over. 
             */
            bool isOver(Team* winningTeam=NULL) const;
   };
}   
#endif //EX3_Game