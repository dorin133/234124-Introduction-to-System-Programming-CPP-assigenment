#include "Game.h"
#define NO_LOCATION -1

namespace mtm
{

    
    void Game::verifyLegalCell(const GridPoint& coordinates) const
    {
        if (coordinates.row >= board.height() || coordinates.col >= board.width() ||
            (coordinates.row < 0 || coordinates.col < 0))
        {
            throw IllegalCell(); 
        }
    }

    void Game::isEmptyCell(const GridPoint& coordinates) const
    {
        if (board(coordinates.row, coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }
    }

    Game::Game(int height, int width)  try : board(Dimensions(height, width), nullptr) {}
    catch(Matrix<std::shared_ptr<Character>>::IllegalInitialization& e)
        {
            throw IllegalArgument();
        }

    Game::Game(const Game& other_game) : board(Dimensions(other_game.board.height(), 
                                            other_game.board.width()), nullptr) 
    {  
        Matrix<std::shared_ptr<Character>>::iterator it = board.begin(); 
        for(Matrix<std::shared_ptr<Character>>::const_iterator other_it = other_game.board.begin(); 
        other_it != other_game.board.end(); it++, other_it++)
        {
            if(*other_it != nullptr)
            {
                *it = (*other_it)->clone();
            }
        }
    }

    
    Game& Game::operator=(const Game& other)
    {
        if (this == &other)
        {
            return *this;
        }
        Matrix<std::shared_ptr<Character>> temp_board(Dimensions(other.board.height(),
                                                          other.board.width()), nullptr);    
        Matrix<std::shared_ptr<Character>>::iterator it_temp = temp_board.begin();
        for (Matrix<std::shared_ptr<Character>>::const_iterator it_other = other.board.begin();
            it_other != other.board.end(); it_temp++, it_other++)
        {
            if(*it_other != nullptr)
            {
                *it_temp = (*it_other)->clone();
            }
        }       
        board = temp_board;
        return *this;
    }
    
    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        verifyLegalCell(coordinates);
        if(board(coordinates.row, coordinates.col) != nullptr)
        {
            throw CellOccupied();
        }
        character->setLocation() = coordinates;
        board(coordinates.row, coordinates.col) = character;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                        int health, int ammo, int range, int power)
    {
        if(health <= 0 || ammo < 0 || range < 0 || power < 0)
        {
            throw IllegalArgument();
        }
        if(type == SOLDIER)
        {
            std::shared_ptr<Character> character(new Soldier(health, ammo, range, power, team,
                                                                 NO_LOCATION, NO_LOCATION));
            return character;
        }
        if(type == MEDIC)
        {
            std::shared_ptr<Character> character(new Medic(health, ammo, range, power, team,
                                                                 NO_LOCATION, NO_LOCATION));
            return character;
        }
        std::shared_ptr<Character> character(new Sniper(health, ammo, range, power, team, 
                                                              NO_LOCATION, NO_LOCATION));
        return character;
    }

    
    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        verifyLegalCell(src_coordinates);
        verifyLegalCell(dst_coordinates);
        isEmptyCell(src_coordinates);
        if (GridPoint::distance(src_coordinates, dst_coordinates) >
            board(src_coordinates.row, src_coordinates.col)->getMovementRange())
            {
                throw MoveTooFar();
            }
        if (board(dst_coordinates.row, dst_coordinates.col) != nullptr)
        {
            throw CellOccupied();
        }
        //moving the character from source to the destination.
        board(dst_coordinates.row, dst_coordinates.col) = board(src_coordinates.row, src_coordinates.col);
        //update coordinates
        board(dst_coordinates.row, dst_coordinates.col)->setLocation() = dst_coordinates;
        //make the source coordinate empty
        board(src_coordinates.row, src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        verifyLegalCell(src_coordinates);
        verifyLegalCell(dst_coordinates);
        isEmptyCell(src_coordinates);
        board(src_coordinates.row, src_coordinates.col)->attack(dst_coordinates, board);
    }
 
    void Game::reload(const GridPoint & coordinates)
    {
        verifyLegalCell(coordinates);
        isEmptyCell(coordinates);
        board(coordinates.row, coordinates.col)->reload();
    }

    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        char* temp_string = new char[game.board.size()+1];
        int i=0;
        for (Matrix<std::shared_ptr<Character>>::const_iterator it = game.board.begin();
            it != game.board.end(); it++, i++)
        {
            if (*it == nullptr)
            {
                temp_string[i]=' ';
            }
            else if ((*it)->getUnitType() == SOLDIER && (*it)->getTeam()==CPP)
            {
                temp_string[i]='S';
            }
            else if ((*it)->getUnitType() == SOLDIER && (*it)->getTeam()==PYTHON)
            {
                temp_string[i]='s';
            }
            else if ((*it)->getUnitType() == MEDIC && (*it)->getTeam()==CPP)
            {
                temp_string[i]='M';
            }
            else if ((*it)->getUnitType() == MEDIC && (*it)->getTeam()==PYTHON)
            {
                temp_string[i]='m';
            }
            else if ((*it)->getUnitType() == SNIPER && (*it)->getTeam()==CPP)
            {
                temp_string[i]='N';
            }
            else if ((*it)->getUnitType() == SNIPER && (*it)->getTeam()==PYTHON)
            {
                temp_string[i]='n';
            }
        }
        temp_string[game.board.size()] = '\0';
        std::string board_string(temp_string);
        delete[] temp_string;
        return printGameBoard(os, board_string.c_str(), 
            board_string.c_str()+game.board.size(), game.board.width());
    }

    bool Game::isOver(Team* winningTeam) const
    {
        int count=0;
        Dimensions dims(board.height(), board.width());
        Matrix<enum Team> python_win(dims, PYTHON);
        Matrix<enum Team> cpp_win(dims, CPP);
        for (Matrix<std::shared_ptr<Character>>::const_iterator it_temp = board.begin();
            it_temp != board.end(); it_temp++)
        {
            if((*it_temp) != nullptr)
            {
                python_win((*it_temp)->getLocation().row, (*it_temp)->getLocation().col)
                 = (*it_temp)->getTeam();
                cpp_win((*it_temp)->getLocation().row, (*it_temp)->getLocation().col)
                 = (*it_temp)->getTeam();
                count++;
            }
        }
        if(all(python_win==PYTHON) && count != 0)
        {
            if(winningTeam != NULL)
            {
                *winningTeam = PYTHON;
            }
            return true;
        }
        if(all(cpp_win==CPP) && count != 0)
        {
            if(winningTeam != NULL)
            {
                *winningTeam = CPP;
            }
            return true;
        }
        return false;
    }
}