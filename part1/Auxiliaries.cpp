#include "Auxiliaries.h"

std::string mtm::Dimensions::toString() const {
    return "(" + std::to_string(row) + "," + std::to_string(col) + ")";
}

bool mtm::Dimensions::operator==(const Dimensions& other) const {
    return (row==other.row) && (col==other.col);
}

bool mtm::Dimensions::operator!=(const Dimensions& other) const {
    return !(*this==other);
}

int mtm::Dimensions::getRow() const {
    return (int)row;
}

int mtm::Dimensions::getCol() const {
    return (int)col;
}

std::string mtm::printMatrix(const int* matrix,const Dimensions& dim){
    std::string matrix_str;
    int col_length = dim.getCol();
    for (int i = 0; i <dim.getRow(); i++) {
        for (int j = 0; j < col_length ; j++) {
            matrix_str+= std::to_string(*(matrix+col_length*i+j)) + " "; 
        }
        matrix_str+=  "\n";
    }
    matrix_str+=  "\n";
    return matrix_str;
}
