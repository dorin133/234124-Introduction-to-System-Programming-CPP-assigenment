#include <assert.h>
#include "IntMatrix.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace mtm;

namespace mtm {
    IntMatrix::IntMatrix(Dimensions dims, int initial) : dimensions(dims),
                          total_size(dims.getRow()*dims.getCol()), matrix(new int[total_size])
    {
        for(int i=0; i < total_size; i++) 
        {
            matrix[i]= initial;
        }
    }

    IntMatrix::IntMatrix(const IntMatrix& other) : dimensions(other.dimensions),
                                                    total_size(other.total_size)
    { 
        matrix = new int[total_size];
        for (int i=0; i<total_size; i++)
        {
            matrix[i]=other.matrix[i];
        }
    }

    IntMatrix::~IntMatrix()
    {
        delete[] matrix;
    }

    IntMatrix& IntMatrix::operator=(const IntMatrix& other) //whats wrong with declaration?
    {
        if (this == &other)
        {
            return *this;
        }
        int* temp = new int[other.total_size];
        int row = dimensions.getRow();
        int col = dimensions.getCol();
        for (int i=0; i < total_size; i++)
        {
            temp[i]=other.matrix[i];
        }
        delete[] matrix;
        matrix = temp;
        return *this;
    }

    int IntMatrix::height() const
    {
        return dimensions.getRow();
    }

    int IntMatrix::width() const
    {
        return dimensions.getCol();
    }

    int IntMatrix::size() const
    {
        return total_size;
    }

    IntMatrix IntMatrix::Identity(int size)
    {
        Dimensions dims(size ,size);
        IntMatrix mat_id(dims);
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
            if(j == i) {
                mat_id(i,j) = 1;
            } 
            }
        }
        return mat_id;
    }

    IntMatrix IntMatrix::transpose() const
    {
        int row_mat = dimensions.getRow();
        int col_mat = dimensions.getCol();
        Dimensions dims_transpose(col_mat , row_mat);
        IntMatrix mat_transpose(dims_transpose);
        for (int i=0; i<row_mat; i++) 
        {
            for (int j=0; j<col_mat; j++) 
            {
                mat_transpose(j,i)=(*this)(i,j);
            }
        }
        return mat_transpose;
    }
     // CHECK TO DELETE
    /*IntMatrix::operator IntMatrix(int num) const; 
    {
        return IntMatrix(dimensions, num);
    }*/

    /*IntMatrix IntMatrix::operator+(const IntMatrix& mat_a)
    {
        Dimensions dims = mat_a.dimensions;
        IntMatrix mat_b = *this;
        return (mat_b += mat_a);
    }*/

    IntMatrix IntMatrix::operator-() const
    {
        IntMatrix mat_minus(*this);
        for(int i = 0; i < mat_minus.total_size; i++)
        {
            mat_minus.matrix[i]= -mat_minus.matrix[i];
        }
        return mat_minus;
    }
    //operator+ for two matrix, return new matrix.
    /*IntMatrix IntMatrix::operator+(const IntMatrix& mat) const
    {
        IntMatrix res = (*this);
        for (int i=0; i<mat.height(); i++)
        {
            for (int j=0; j<mat.width(); j++)
            {
                res(i,j) += mat(i,j);
            }
        }
        return res;
    }*/

    IntMatrix IntMatrix::operator-(const IntMatrix& mat) const
    {
        IntMatrix res_mat = *this;
        int row = mat.height();
        int col = mat.width();
        for (int i = 0; i < row ; i++) 
        {
            for (int j = 0; j < col ; j++) 
            {
                res_mat(i,j) -= mat(i,j);
            }
        }
        return res_mat;
    }

    IntMatrix& IntMatrix::operator+=(int scalar)
    {
        for (int i = 0; i < total_size; i++)
        {
            matrix[i] += scalar;
        }
        return *this;
    }

    int& IntMatrix::operator()(const int row, const int column) 
    {
        return matrix[dimensions.getCol()*row + column];
    }

    const int& IntMatrix::operator()(const int row, const int column) const 
    {
        return matrix[dimensions.getCol()*row + column];
    }


    //END OF PUBLIC FUNCTIONS

    IntMatrix operator+(const IntMatrix& first, const IntMatrix& second)
    {
        return first - (-second);      
    }

    IntMatrix operator+(const IntMatrix& mat, int num)
    {
        IntMatrix res(mat);
        res += num;
        return res;
    }
        
    IntMatrix operator+(int num, const IntMatrix& mat)
    {
        return mat + num;
    }

    bool all(const IntMatrix& mat) 
    {
        int row = mat.height();
        int col = mat.width();
        for (int i = 0; i < row ; i++) 
        {
            for (int j = 0; j < col ; j++) 
            {
                if(mat(i,j) == 0)
                {
                    return false;
                }
            }      
        }
        return true;
    }

    bool any(const IntMatrix& mat)
    {
        if(mtm::all(mat))
        {
            return true;
        }
        else
        {
            if (mtm::all(mat==0))
            {
                return false;
            }
            return true; 
        }
        
        return (!mtm::all(mat));
    }

    std::ostream& operator<<(std::ostream& os, const IntMatrix& mat)
    {
        os << printMatrix(mat.matrix, mat.dimensions);
        return os;
    }

    IntMatrix operator==(const IntMatrix& mat, const int b)
    {
        IntMatrix mat_b = mat;
        int mat_rows=mat.height();
        int mat_cols=mat.width();
        for (int i=0; i<mat_rows; i++)
        {
            for (int j=0; j<mat_cols; j++)
            {
                    if(mat(i,j) == b)
                    {
                        mat_b(i,j)=true;
                    }
                    else
                    {
                        mat_b(i,j)=false;
                    }
                    
            }
        }
        return mat_b;
    }

    IntMatrix operator!=(const IntMatrix& mat_a, const int b)
    {
        Dimensions dims_mat_a(mat_a.height(), mat_a.width());
        IntMatrix mat_b (dims_mat_a, 1);
        return (mat_b-(mat_a==b));
    }

    IntMatrix operator>(const IntMatrix& mat, int num) 
    {
        int row = mat.height();
        int col = mat.width();
        Dimensions dims(row,col);
        IntMatrix res(dims);
        for (int i = 0; i < row ; i++) 
        {
            for (int j = 0; j < col ; j++) 
            {
                if(mat(i,j) > num) {
                    res(i,j) = 1;
                }
            }
        }
        return res;
    }

    IntMatrix operator<(const IntMatrix& mat, int num)  
    {
        Dimensions mat_dims(mat.height(), mat.width());
        IntMatrix res(mat_dims, 1);
        return res-(mat>num)-(mat==num);
    }

    IntMatrix operator>=(const IntMatrix& mat, int num)  
    {
        return (mat>num) + (mat==num);
    }

    IntMatrix operator<=(const IntMatrix& mat, int num)
    {
        return (mat<num) + (mat==num);
    }

    //START OF ITERATOR
    
    IntMatrix::iterator::iterator(const IntMatrix* mat, int index) : mat(mat), index(index)
    {}

    int& IntMatrix::iterator::operator*() //if this is const: const IntMatrix* mat
    {
        assert (index>= 0);
        assert (index<mat->size());
        return mat->matrix[index];
    }    

    IntMatrix::iterator IntMatrix::iterator::operator++(int)
    {
        iterator result=*this;
        ++*this;
        return result;
    }

    bool IntMatrix::iterator::operator==(const iterator& it) const
    {
        assert(mat == it.mat);
        return index == it.index;
    }

    bool IntMatrix::iterator::operator!=(const iterator& it) const
    {
        return !(*this == it);
    }

    IntMatrix::iterator& IntMatrix::iterator::operator++()
    {
        index++;
        return *this;
    }

    IntMatrix::iterator IntMatrix::begin() 
    {
        return iterator(this, 0);
    }

    IntMatrix::iterator IntMatrix::end() 
    {
        int index = this->size();
        return iterator(this, index);
    }

    //END OF ITARATOR
    
    //START OF CONST_ITERATOR

    IntMatrix::const_iterator::const_iterator(const IntMatrix* const mat, int index) : 
    mat(mat), index(index)
    {}

    IntMatrix::const_iterator IntMatrix::begin() const
    {        
        return const_iterator(this, 0);
    }

    IntMatrix::const_iterator IntMatrix::end() const
    {
        int index = this->size();
        return const_iterator(this, index);
    }

    const int& IntMatrix::const_iterator::operator*() const //if this is const: const IntMatrix* mat
    {
        assert (index>= 0);
        assert (index<mat->size());
        return mat->matrix[index];
    }    

    IntMatrix::const_iterator& IntMatrix::const_iterator::operator++()
    {
        assert ((*this) != mat->end());
        index++;
        return *this;
    }

    IntMatrix::const_iterator IntMatrix::const_iterator::operator++(int)
    {
        const_iterator result=*this;
        ++*this;
        return result;
    }

    bool IntMatrix::const_iterator::operator==(const const_iterator& it) const
    {
        assert(mat == it.mat);
        return index == it.index;
    }

    bool IntMatrix::const_iterator::operator!=(const const_iterator& it) const
    {
        return !(*this == it);
    }

}




//void sumOfMatrix(const IntMatrix& mat) 
//for (IntMatrix::Iterator it = mat.begin(); it != mat.end(); ++it)


/** for const iteraator operator()*
 * int& IntMatrix::const_iterator::operator*()
    {
        assert (index>= 0);
        assert (index<mat->size());
        int col=index%(mat->width());
        int row=index/(mat->width());
        return (*mat)(row, col);
    }    
*/