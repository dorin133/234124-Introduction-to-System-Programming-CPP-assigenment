#ifndef EX3_INT_MATRIX_H
#define EX3_INT_MATRIX_H
#include "Auxiliaries.h"

namespace mtm
{
    class IntMatrix
    {
        private:
            Dimensions dimensions;
            int total_size;
            int* matrix;
        public:
            /**
             * c'tor for IntMatrix objects.
             * 
             * @param:
             *          dims - Object of Dimensions class, which indicate the matrix height and width.
             *          initial - the initial value of the matrix members. By default set to 0
             *                    if didnt get another input.
             */
            IntMatrix(Dimensions dims, int initial = 0);

            /**
             * copy c'tor for IntMatrix objects.
             * 
             * @param:
             *          other - reference of another matrix object of IntMatrix class.
             */
            IntMatrix(const IntMatrix& other);

            /**
             * d'tor for IntMatrix objects, which free the allocated memory of the matrix,
             * and then destroy the object.
             */
            ~IntMatrix();

            /**
             * assignment operator for two matrix.
             * @param:
             *          other - reference of another matrix object of IntMatrix class.
             * 
             * return:
             *          a reference of the exist matrix (*this), after copied its relevant data.
             */
            IntMatrix& operator=(const IntMatrix& other);

            /**
             * static member function to make identity matrix, means 1 in the diagonal, and 0 otherwise.
             * 
             * @param:
             *          size - the height and width of the new matrix object.
             * 
             * return:
             *          a copy of the new matrix created.
             */
            static IntMatrix Identity(int size);

            /**
             * member function to return transpose copy of given matrix.
             * 
             * return:
             *          copy of the new matrix created.
             */
            IntMatrix transpose() const; //

            /**
             * return number of rows in matrix.
             */
            int height() const;

            /**
             * return number of columns in matrix.
             */
            int width() const; 
            
            /**
             * return number of members in matrix.
             */
            int size() const;

            /**
             * Printing operator for class IntMatrix
             * 
             * @param:
             *          os - Reference of an ouput stream object.
             *          mat - Reference of matrix object of IntMatrix class.
             * 
             * return:  reference of an output stream object.
             */
            friend std::ostream& operator<<(std::ostream& os, const IntMatrix& mat);

            /**
             * operator- for two matrix object of IntMatrix class.
             * 
             * @param:
             *          mat - the matrix which subtracted from the matrix whom invoked the operator.
             * 
             * return:  copy of the result matrix.
             */
            IntMatrix operator-(const IntMatrix& mat) const;

            /**
             * operator- for one matrix object.
             * 
             * return:  copy of matrix object with oposite sign of every member in it.
             */
            IntMatrix operator-() const;

            /**
             * operator+= for matrix object (left operand) and an integer (right operand).
             * 
             * @param:
             *          scalar - integer number which is added to every member of the matrix object.
             * 
             * return:  a reference of the matrix itself whom invoked the method.
             */
            IntMatrix& operator+=(int scalar);


            //IntMatrix operator+(const IntMatrix& mat) const; // CHECK TO DELETE
            //IntMatrix& operator+=(const IntMatrix& mat); // CHECK TO DELETE
            //operator IntMatrix(int num) const; // convert int to IntMatrix // CHECK TO DELETE

            
            int& operator()(const int row, const int column);
            const int& operator()(const int row,const  int column) const;
            class iterator;
            class const_iterator;
            /*IMPLEMENT FUNCTIONS TO BEGIN,END OF CONST_ITERATOR*/
            const_iterator begin() const; //dorin-done
            const_iterator end() const; //dorin-done
            iterator begin(); //dorin-done
            iterator end(); //dorin-done
    };      
        class IntMatrix::iterator
        {
            private:
                const IntMatrix* mat;
                int index;
                iterator(const IntMatrix* mat, int index); //ido
                friend class IntMatrix;
            public:
                int& operator*();  //ido (const) iterator* const this
                iterator& operator++(); // Ok
                iterator operator++(int); // postfix (it++)  //Ok
                bool operator==(const iterator& it) const; //Ok
                bool operator!=(const iterator& it) const; //Ok
                iterator(const iterator&) = default; //Ok
                iterator& operator=(const iterator&) = default; //Ok
        };            

        class IntMatrix::const_iterator
        {
            private:
                //IntMatrix::iterator* it;
                const IntMatrix* const mat;
                int index;
                const_iterator(const IntMatrix* const mat, int index);
                friend class IntMatrix;
            public:
                const int& operator*() const;  
                const_iterator& operator++(); // Ok
                const_iterator operator++(int); // postfix (it++)  //Ok
                bool operator==(const const_iterator& it) const; //Ok
                bool operator!=(const const_iterator& it) const; //Ok
                const_iterator(const const_iterator&) = default; //Ok
                const_iterator& operator=(const const_iterator&) = default; //Ok
        };
        
    IntMatrix operator+(const IntMatrix& first, const IntMatrix& second);
    IntMatrix operator+(const IntMatrix& mat, int num);
    IntMatrix operator+(int num, const IntMatrix& mat);
    IntMatrix operator==(const IntMatrix& mat, int num);
    IntMatrix operator!=(const IntMatrix& mat, int num);
    IntMatrix operator<(const IntMatrix& mat, int num);
    IntMatrix operator>(const IntMatrix& mat, int num);
    IntMatrix operator>=(const IntMatrix& mat, int num);
    IntMatrix operator<=(const IntMatrix& mat, int num);
    bool all(const IntMatrix& mat);
    bool any(const IntMatrix& mat);        
}
#endif //EX3_INT_MATRIX_H
