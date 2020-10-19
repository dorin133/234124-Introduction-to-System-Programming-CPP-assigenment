#ifndef EX3_EXCEPTIONS
#define EX3_EXCEPTIONS
#include <string>

namespace mtm
{
    class Exceptions : public std::exception
    {
        protected:
            std::string to_print;
        public:
            Exceptions(std::string error) : to_print(error) {}
            virtual ~Exceptions() {}
            virtual const char* what() const noexcept
            {
                return to_print.c_str();
            }
    };

    class GameException : public Exceptions 
    {
        public:
            GameException(std::string error) : Exceptions(error) {}
            virtual ~GameException() {}
    };

    class IllegalArgument :  public GameException
    {
        public:
            IllegalArgument() :
            GameException("A game related error has occurred: IllegalArgument") {}
    };

    class IllegalCell : public GameException
    {
        public:
            IllegalCell() :
            GameException("A game related error has occurred: IllegalCell") {}
    };

    class CellEmpty :  public GameException
    {
        public:
            CellEmpty() :
            GameException("A game related error has occurred: CellEmpty") {}
    };

    class MoveTooFar : public GameException
    {
        public:
            MoveTooFar() :
            GameException("A game related error has occurred: MoveTooFar") {}
    };

    class CellOccupied : public GameException
    {
        public:
            CellOccupied() :
            GameException("A game related error has occurred: CellOccupied") {}
    };

    class OutOfAmmo : public GameException
    {
        public:
            OutOfAmmo() :
            GameException("A game related error has occurred: OutOfAmmo") {}
    };

    class OutOfRange : public GameException
    {
        public:
            OutOfRange() :
            GameException("A game related error has occurred: OutOfRange") {}
    };

    class IllegalTarget : public GameException
    {
        public:
            IllegalTarget() :
            GameException("A game related error has occurred: IllegalTarget") {}
    };
}
#endif //EX3_EXCEPTION