#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include "Auxiliaries.h"
#include <cassert>

namespace mtm
{
    template <class T>
    class Matrix
    {
        private:
            Dimensions dims;
            int total_size; 
            T* matrix;
            void verifyIndex(const int& index) const
            {
                if (index < 0 || index >= total_size)
                {
                    throw AccessIllegalElement();
                }
            }
            void verifyInitialization(const Dimensions& dims) const
            {
                if(dims.getRow()<=0 || dims.getCol()<=0)
                {
                    throw(IllegalInitialization());
                }
            }

            void verifyDimensionsMatch(const Dimensions& dims1, const Dimensions& dims2) const
            {
                if (dims1 != dims2)
                {
                    throw DimensionMismatch(dims1, dims2);
                }
            }
            
        public:

            /**
             * c'tor for Matrix objects.
             * 
             * @param:
             *          dims - Object of Dimensions class, which indicate the matrix height and width.
             *          initial - the initial value of the matrix members, which is of type T.
             *          if didnt get another input set to the default value by the default constructor
             *          of type T.
             * Asumptions: type T has a default ctor, operator=
             */
            explicit Matrix(Dimensions dims, T initial = T()) : dims(dims) , total_size(dims.getRow()*dims.getCol())                                                        
            {
                verifyInitialization(dims);
                matrix = new T[total_size];
                try 
                {
                    for (int i=0; i<total_size; i++)
                    {
                        matrix[i]=initial;                
                    }
                }
                catch(...)
                {
                    delete[] matrix;
                    throw;
                }
            }

            /**
             * copy c'tor for Matrix objects.
             * 
             * Asumptions: type T has an operator=, default ctor
             *          
             */
            Matrix(const Matrix<T>& other) : dims(other.dims) , total_size(other.total_size)
            {
                matrix = new T[total_size];
                try
                {
                    for (int i=0; i<other.total_size; i++)
                    {
                        matrix[i] = other.matrix[i];
                    }
                }
                catch(...)
                {
                    delete[] matrix;
                    throw;
                }
            }

            /**
             * d'tor for Matrix objects, which free the allocated memory of the matrix,
             * and then destroy the object.
             */
            ~Matrix()
            {
                delete[] matrix;
            }

            /**
             * assignment operator for two matrix.
             * @param:
             *          other - reference of another matrix object of Matrix class.
             * 
             * Asumptions: type T has an operator=, defualt ctor
             * 
             * return:
             *          a reference of the exist matrix (*this), after copied its relevant data.
             */
            Matrix<T>& operator=(const Matrix<T>& other)
            {
                if(this == &other) //Check for self assignment
                {
                    return *this;
                }
                T* temp = new T[other.total_size];
                try
                {
                    for (int i=0; i<other.total_size; i++)
                    {
                        temp[i]=other.matrix[i];
                    }
                }
                catch(...)
                {
                    delete[] temp;
                    throw;
                }
                delete[] matrix;
                dims = other.dims;
                matrix=temp;
                total_size=other.total_size;
                return *this;
            }

            class AccessIllegalElement : public std::exception
            {
                private:
                    std::string to_print;
                public:
                    AccessIllegalElement() : to_print("Mtm matrix error: An attempt to access an illegal element") {}
                    virtual const char* what() const noexcept override
                    {
                    return to_print.c_str();
                    }
            };
            class IllegalInitialization : public std::exception
            {
                private:
                    std::string to_print;
                public:
                    IllegalInitialization() : to_print("Mtm matrix error: Illegal initialization values") {}
                    virtual const char* what() const noexcept override
                    {
                    return to_print.c_str();
                    }
            };
            class DimensionMismatch : public std::exception
            {
                private:
                    std::string to_print;
                    Dimensions left_mat_dims;
                    Dimensions right_mat_dims;
                public:
                    DimensionMismatch(Dimensions mat1_dims, Dimensions mat2_dims2) : 
                                    to_print("Mtm matrix error: Dimension mismatch: "),
                                    left_mat_dims(mat1_dims), right_mat_dims(mat2_dims2)
                    {
                        to_print += "(" + std::to_string(left_mat_dims.getRow()) +
                        "," + std::to_string(left_mat_dims.getCol()) + ")";
                        to_print += " (" + std::to_string(right_mat_dims.getRow()) +
                        "," + std::to_string(right_mat_dims.getCol()) + ")";               
                    }
                    virtual const char* what() const noexcept override
                    {
                        return to_print.c_str();
                    }
            };
            /**
             * static member function to make diagonal matrix object of class Matrix.
             * implement value of type T in the diagonal, and default value of type T constructor otherwise.
             * 
             * @param:
             *          size - the height and width of the new matrix object.
             *
             * Assumptions: none (based on previous assumptions)
             *  
             * return:
             *          a copy of the new diagonal matrix created.
             */
            static Matrix<T> Diagonal(int size, T value)
            {
                Dimensions mat_dims(size, size);
                Matrix res(mat_dims);
                for (int i=0; i<size; i++)
                {
                    for (int j=0; j<size; j++)
                    {
                        if (i==j)
                        {
                            res(i,j)=value;
                        }
                    }
                }
                return res;            
            }

            /**
             * member function to return transpose copy of given matrix.
             * 
             * Assumptions: none (based on previous assumptions)
             * 
             * return:
             *          copy of the new matrix created.
             */
            Matrix transpose() const 
            {
                int row_mat = dims.getRow();
                int col_mat = dims.getCol();
                Dimensions dims_transpose(col_mat , row_mat);
                Matrix mat_transpose(dims_transpose);
                for (int i=0; i<row_mat; i++) 
                {
                    for (int j=0; j<col_mat; j++) 
                    {
                        mat_transpose(j,i)=(*this)(i,j);
                    }
                }
                return mat_transpose;
            }

            /**
             * return number of rows in matrix.
             */
            int height() const
            {
                return dims.getRow();
            }

            /**
             * return number of columns in matrix.
             */
            int width() const
            {
                return dims.getCol();
            }
            
            /**
             * return number of members in matrix.
             */
            int size() const
            {
                return total_size;
            }

            /**
             * operator- for two matrix object of Matrix class.
             * 
             * Asumptions:
             *          type T has += , - operators and a c'ctor
             * 
             * return:  copy of the result matrix.
             */
            Matrix<T> operator-(const Matrix<T>& mat) const
            {
                verifyDimensionsMatch(dims, mat.dims);
                Matrix<T> res(*this);
                for(int i = 0; i < total_size; i++)
                {
                    res.matrix[i] += (-mat.matrix[i]);
                }
                return res;
            }

            /**
             * unary operator- for one matrix object.
             * 
             *  Asumptions: none (based on previous assumptions)
             * 
             *  return:  copy of matrix object with oposite sign of every member in it,
             *          in case of numeric type T.
             */
            Matrix<T> operator-() const
            {
                Matrix<T> res(dims);
                return res - *this;
            }

            /**
             * operator+= for matrix object (left operand) and type T object (right operand).
             * 
             * Asumptions:
             *          type T has a += operator
             * 
             * return:  reference of the matrix itself who called the method.
             */
            Matrix<T>& operator+=(const T scalar)
            {
                for (int i = 0; i < total_size; i++)
                {
                    matrix[i]+=scalar;
                }
                return *this;
            }
            /*
             * operator() 
             * 
             * Asumptions: none (based on previous assumptions)
             * 
             * return: a reference value of matrix(row,col)
             */
            T& operator()(int row, int col)
            {   
                int index=dims.getCol()*row + col;
                verifyIndex(index);
                return matrix[index];
            }
             /*
             * const operator() 
             * 
             * Asumptions : none (based on previous assumptions)
             * 
             * return: a const reference value of const matrix(row,col)
             */
            const T& operator()(const int row, const int col) const
            {
                int index=dims.getCol()*row + col;
                verifyIndex(index);
                return matrix[index];
            }
            
            class iterator
            {
                private:
                    const Matrix<T>* mat;
                    int index;
                    /*
                    * iterator ctor
                    * 
                    * Asumptions : none (based on previous assumptions)
                    * 
                    * return: an iterator for the given index in mat ot type T
                    */
                    iterator(const Matrix<T>* mat, int input_index) : mat(mat), index(input_index) {}
                    friend class Matrix;
                public:                   
                    /*
                    * operator== (iterator)
                    * 
                    * Asumptions : none
                    * 
                    * return: true/false if the this, it iterator are equal 
                    *         (pointing on the same index in the same matrix)
                    */
                    bool operator==(const iterator& it) const
                    {
                        assert(mat == it.mat);
                        return index == it.index;
                    }
                    /*
                    * operator!= (iterator)
                    * 
                    * Asumptions : none
                    * 
                    * return: true/false if the this, it iterator are equal 
                    *         (pointing on the same index in the same matrix)
                    */ 
                    bool operator!=(const iterator& it) const
                    {
                        return !(*this == it);
                    }
                    /*
                    * operator* (iterator)
                    * 
                    * Asumptions : none 
                    * 
                    * return: return a refrence to the value the iterator points at
                    */
                    T& operator*()
                    {
                        mat->verifyIndex(index);
                        return mat->matrix[index];
                    }
                    /*
                    * operator++ (iterator)
                    * 
                    * Asumptions : none 
                    * 
                    * return: promote and return the new value the iterator points at
                    */
                    iterator& operator++() 
                    {
                        index++;
                        return *this;
                    }

                    /*
                    * operator++ (iterator)
                    * 
                    * Asumptions : none (based on previous assumptions) 
                    * 
                    * return: return the value the iterator points at and promomte it to the next
                    */
                    iterator operator++(int)
                    {
                        iterator result=*this;
                        ++*this;
                        return result;
                    }
                    iterator(const iterator&) = default;
                    iterator& operator=(const iterator&) = default;               
            };

            class const_iterator
            {
                private:
                    const Matrix<T>* const mat;
                    int index;
                    /*
                    * const_iterator ctor
                    * 
                    * Asumptions : none (based on previous assumptions)
                    * 
                    * return: an iterator for the given index in mat ot type T
                    */
                    const_iterator(const Matrix<T>* const mat, int input_index) :  mat(mat), 
                                                                                   index(input_index)  {}
                    friend class Matrix;
                public:
                    /*
                    * operator* (const_iterator)
                    * 
                    * Asumptions : none 
                    * 
                    * return: return a const reference the iterator points at
                    */
                    const T& operator*() const
                    {
                        mat->verifyIndex(index);
                        return mat->matrix[index];
                    }
                    /*
                    * operator== (const_iterator)
                    * 
                    * Asumptions : none
                    * 
                    * return: true/false if the this, it iterator are equal 
                    *         (pointing on the same index in the same const matrix)
                    */       
                    bool operator==(const const_iterator& it) const
                    {
                        assert(mat == it.mat);
                        return index == it.index;
                    }
                    /*
                    * operator!= (const_iterator)
                    * 
                    * Asumptions : none
                    * 
                    * return: true/false if the this, it iterator are equal 
                    *         (pointing on the same index in the same  const matrix)
                    */  
                    bool operator!=(const const_iterator& it) const
                    {
                        assert(mat == it.mat);
                        return index != it.index;
                    }
                    /*
                    * operator++ (const_iterator)
                    * 
                    * Asumptions : none 
                    * 
                    * return: promote and return the new value the iterator points at
                    */
                    const_iterator& operator++()
                    {
                        index++;
                        return *this;
                    }
                    /*
                    * operator++ (const_iterator)
                    * 
                    * Asumptions : none (based on previous assumptions)
                    * 
                    * return: return the value the const_iterator points at and promomte it to the next
                    */
                    const_iterator operator++(int) //postfix
                    {
                        const_iterator result=*this;
                        ++*this;
                        return result;
                    }
                    const_iterator(const const_iterator&) = default; 
                    const_iterator& operator=(const const_iterator&) = default;
            };
            iterator begin()
            {
                return iterator(this, 0);
            }
            iterator end()
            {
                int index = this->size();
                return iterator(this, index);
            }
            const_iterator end() const
            {
                int index = this->size();
                return const_iterator(this, index);
            } 
            const_iterator begin() const
            {
                return const_iterator(this, 0);
            }
            template <class Condition>
            Matrix<T> apply(Condition c) const 
            {
                Matrix<T> result(*this);
                for (typename Matrix<T>::iterator it = result.begin(); it != result.end(); ++it)
                {
                    *it = c(*it);
                }
                return result;
            }
    
        /**
         * operator+ for two matrixes containing objects of type T.
         * 
         * Asumptions:
         *          c'ctor is implemented
         *          type T has an operator+=
         *          
         * return:
         *          copy of the summed/chained matrix. in case of chained, will chain mat2 to mat1
         *          part by part.
         */
        Matrix<T> operator+(const Matrix<T>& mat) const      
        {
            verifyDimensionsMatch(dims, mat.dims);
            Matrix<T> res(*this);
            for (int i=0; i<mat.height(); i++)
            {
                for (int j = 0; j < mat.width(); j++)
                {
                    res(i,j) += mat(i,j);
                }
            }
            return res;
        }
        /*
        * operator< 
        *          return a bool matrix with the same dimensions as the given matrix.
        *          put true in (i,j) in the result matrix - if the obj of type T is bigger 
        *                      than the given matrix in the (i,j) field (also a type T).
        *          put false - otherwise.
        * Asumptions:
        *          c'ctor is impemented
        *          type T has an operator< implementation
        *          
        * return:
        *          copy of the the result matrix of type Matrix<bool> 
        */
        Matrix<bool> operator<(T obj) const
        {
            int col_mat = width();
            int row_mat = height();
            Dimensions dims_mat(row_mat, col_mat);
            Matrix<bool> res(dims_mat, false);
            for (int i=0; i<row_mat; i++) 
            {
                for (int j=0; j<col_mat; j++) 
                {
                    if((*this)(i,j) < obj)
                    {
                        res(i,j) = true;
                    }
                }
            }
            return res;
        }

        /*
        * operator==
        *          return a bool matrix with the same dimensions as the given matrix.
        *          put true in (i,j) in the result matrix - if the obj of type T is equal 
        *                      to the given matrix in the (i,j) field (also a type T).
        *          put false - otherwise.
        * Asumptions:
        *          c'ctor is impemented
        *          type T has an operator== implementation
        *          
        * return:
        *          copy of the the result matrix of type Matrix<bool> 
        */
        Matrix<bool> operator==(T obj) const
        {
            int col_mat=width();
            int row_mat=height();
            Dimensions dims_mat(row_mat, col_mat);
            Matrix<bool> res(dims_mat, false);
            for (int i=0; i<row_mat; i++) 
            {
                for (int j=0; j<col_mat; j++) 
                {
                    if((*this)(i,j) == obj)
                    {
                        res(i,j) = true;
                    }
                }
            }
            return res;
        }

        /*
        * operator!=
        *          return a bool matrix with the same dimensions as the given matrix.
        *          put true in (i,j) in the result matrix - if the obj of type T is not equal 
        *                      to the given matrix in the (i,j) field (also a type T).
        *          put false - otherwise.
        * Asumptions:
        *          c'ctor is impemented
        *          type T has an operator== implementation (operator- surely exists for bool type)
        *          
        * return:
        *          copy of the the result matrix of type Matrix<bool> 
        */
        Matrix<bool> operator!=(T obj) const
        {
            Dimensions dims_mat(height(), width());
            Matrix<bool> res(dims_mat, true);
            return res - (*this == obj);
        }

        /*
        * operator>
        *          return a bool matrix with the same dimensions as the given matrix.
        *          put true in (i,j) in the result matrix - if the obj of type T is smaller than 
        *                       the given matrix in the (i,j) field (also a type T).
        *          put false - otherwise.
        * Asumptions:
        *          c'ctor is impemented
        *          type T has an operator==,operator< implementation (operator- surely exists for bool type)
        *          
        * return:
        *          copy of the the result matrix of type Matrix<bool> 
        */   
        Matrix<bool> operator>(T obj) const
        {
            Dimensions dims_mat(height(), width());
            Matrix<bool> res(dims_mat, true);
            return res - (*this == obj) - (*this < obj);
        }
        
        /*
        * operator<=
        *          return a bool matrix with the same dimensions as the given matrix.
        *          put true in (i,j) in the result matrix - if the obj of type T is bigger or equal than 
        *                       the given matrix in the (i,j) field (also a type T).
        *          put false - otherwise.
        * Asumptions:
        *          c'ctor is impemented
        *          type T has an operator==,operator< implementation (operator+ surely exists for bool type)
        *          
        * return:
        *          copy of the the result matrix of type Matrix<bool> 
        */ 
        Matrix<bool> operator<=(T obj) const
        {
            return (*this == obj) + (*this < obj);
        }

        /*
        * operator<=
        *          return a bool matrix with the same dimensions as the given matrix.
        *          put true in (i,j) in the result matrix - if the obj of type T is smaller or equal than 
        *                       the given matrix in the (i,j) field (also a type T).
        *          put false - otherwise.
        * Asumptions:
        *          c'ctor is impemented
        *          type T has an operator==,operator> implementation (operator+ surely exists for bool type)
        *          
        * return:
        *          copy of the the result matrix of type Matrix<bool> 
        */ 
        Matrix<bool> operator>=(T obj) const
        {
            return (*this == obj) + (*this > obj);
        }
    };
    
    //END OF INNER METHODS
    
    /*
    * Printing operator for class Matrix
    * 
    * Asumptions: iterator/const_iterator exist for Matrix<T>  
    * 
    * return: reference of an output stream object.
    */
    template<class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
    {
        return printMatrix(os, mat.begin(), mat.end(), mat.width());
    }

    /**
     * operator+ for a matrix of type T (left object), and a single object of type T (right object).
     * 
     * Asumptions:
     *          operator+= is implemented as a public funtion for Matrix<T>
     *          c'ctor is impemented
     *          the type T given has an operator+= 
     * return:
     *          copy of the summed matrix with the given object.
     */
    template<class T>
    Matrix<T> operator+(const Matrix<T>& mat1, const T& obj)            
    {
        Matrix<T> res(mat1);
        return (res += obj);
    }

    /**
     * operator+ for a matrix of type T (right object), and a single object of type T (left object).
     * 
     * Asumptions:
     *          c'ctor is impemented
     *          type T has an operator+, operator=
     * 
     * return:
     *          copy of the summed/chained matrix (in case of chained, chain obj to left).
     */
    template<class T>
    Matrix<T> operator+(const T& obj, const Matrix<T>& mat1)
    {
        Matrix<T> res(mat1);
        for (int i=0; i<mat1.height(); i++)
        {
            for (int j=0; j<mat1.width(); j++)
            {
                res(i,j) = obj + res(i,j);
            }
        }
        return res;
    }

    /**
     * boolean function all.
     * 
     * Asumptions:
     *          type T has a convertion to a boolean type
     *          type T has a operator==
     * return:
     *          true - if could convert every member of the matrix to true.
     *          false - otherwise.
     */
    template<class T>
    bool all(const Matrix<T>& mat) 
    {
        for (int i=0; i<mat.height(); i++)
        {
            for (int j=0; j<mat.width(); j++)
            {
                if (!mat(i,j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * boolean function any.
     * 
     * Asumptions
     *          type T has a convertion to a boolean type
     *          type T has a operator==
     *          
     * return:
     *          true - if could convert at least one member of the matrix to true.
     *          false - otherwise, means none of the matrix members could be converted to true.
     */
    template<class T>
    bool any(const Matrix<T>& mat)
    {
        for (int i=0; i<mat.height(); i++)
        {
            for (int j=0; j<mat.width(); j++)
            {
                if (mat(i,j))
                {
                    return true;
                }
            }
        }
        return false;
    }
}

#endif //EX3_MATRIX_H