#pragma once
/*mymatrix.h*/
/*
Mutafa Ausaf
Project 3--CS251-SPRING2023--mymatrix
Dr Adam T Koehler.
*/
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023


//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

//#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
    struct ROW
    {
        T* Cols;     // dynamic array of column elements
        int NumCols;  // total # of columns (0..NumCols-1)
    };

    ROW* Rows;     // dynamic array of ROWs
    int  NumRows;  // total # of rows (0..NumRows-1)

public:
    //
    // default constructor:
    //
    // Called automatically by C++ to construct a 4x4 matrix.  All 
    // elements are initialized to the default value of T.
    //
    mymatrix()
    {
        Rows = new ROW[4];  // an array with 4 ROW structs:
        NumRows = 4;

        // initialize each row to have 4 columns:
        for (int r = 0; r < NumRows; ++r)
        {
            Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
            Rows[r].NumCols = 4;

            // initialize the elements to their default value:
            for (int c = 0; c < Rows[r].NumCols; ++c)
            {
                Rows[r].Cols[c] = T{};  // default value for type T:
            }
        }
    }

    //
    // parameterized constructor:
    //
    // Called automatically by C++ to construct a matrix with R rows, 
    // where each row has C columns. All elements are initialized to 
    // the default value of T.
    //
    
    /*
    this code initializes a dynamic two-dimensional array (i.e., a matrix)
    with a given number of rows and columns, where each element is initialized to its default value.
    */
    mymatrix(int R, int C)
    {
        if (R < 1)
            throw invalid_argument("mymatrix::constructor: # of rows");
        if (C < 1)
            throw invalid_argument("mymatrix::constructor: # of cols");

        //
        // TODO
        //
        Rows = new ROW[R];  
        NumRows = R;
        // row initializing  to columns given by user 
        for (int i = 0; i < NumRows; ++i)
        {
            Rows[i].Cols = new T[C]; 
            Rows[i].NumCols = C;

            // initialize the elements to their default value:
            for (int j = 0; j < Rows[i].NumCols; ++j)
            {
                Rows[i].Cols[j] = {};  
            }
        }
    }


    //
    // copy constructor:
    //
    // Called automatically by C++ to construct a matrix that contains a 
    // copy of an existing matrix.  Example: this occurs when passing 
    // mymatrix as a parameter by value
    //
    //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
    //   { ... }
    //
    
    /*
    this code initializes a new mymatrix object by copying the contents of an existing mymatrix object.
    It allocates new memory for the current object's rows and columns, copies the elements 
    of the existing object's rows and columns to the new memory, and assigns the new memory 
    to the current object's member variables.
    */
    mymatrix(const mymatrix<T>& other)
    {
        //
        // TODO
        //
        this->NumRows = other.NumRows;
        this->Rows = new ROW[other.NumRows];

        for (int rowIndex = 0; rowIndex < NumRows; rowIndex++)
        {
            this->Rows[rowIndex].Cols = new T[other.Rows[rowIndex].NumCols];
            this->Rows[rowIndex].NumCols = other.Rows[rowIndex].NumCols;

            for (int j = 0; j < Rows[rowIndex].NumCols; j++) 
            {
                this->Rows[rowIndex].Cols[j] = other.Rows[rowIndex].Cols[j];
            }
        }
    }

    // numrows
    //
    // Returns the # of rows in the matrix.  The indices for these rows
    // are 0..numrows-1.
    //
    int numrows() const
    {
        //
        // TODO
        //

        return NumRows;
    }


    //
    // numcols
    //
    // Returns the # of columns in row r.  The indices for these columns
    // are 0..numcols-1.  Note that the # of columns can be different 
    // row-by-row since "jagged" rows are supported --- matrices are not
    // necessarily rectangular.
    //
    int numcols(int r) const
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::numcols: row");

        //
        // TODO
        //
        return Rows[r].NumCols;
    }


    //
    // growcols
    //
    // Grows the # of columns in row r to at least C.  If row r contains 
    // fewer than C columns, then columns are added; the existing elements
    // are retained and new locations are initialized to the default value 
    // for T.  If row r has C or more columns, then all existing columns
    // are retained -- we never reduce the # of columns.
    //
    // Jagged rows are supported, i.e. different rows may have different
    // column capacities -- matrices are not necessarily rectangular.
    //
    
    
    /*
    this function extends a specified row of the mymatrix object to have a new number of columns.
    It creates a new dynamic array of type T, copies the existing elements to it, 
    initializes any remaining columns to their default value, deallocates the old memory allocated 
    to the row, and assigns the new memory to the row.
    */
    
    void growcols(int r, int C)
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::growcols: row");
        if (C < 1)
            throw invalid_argument("mymatrix::growcols: columns");

        //
        // TODO:
        //
        //Grow row r to have C columns
        T* n_rows = new T[C];

        for (int index = 0; index < Rows[r].NumCols; index++) 
        {
            if (index < C) {
                n_rows[index] = Rows[r].Cols[index];
            }
        }
        //
        for (int index = Rows[r].NumCols; index < C; index++)
        {
            n_rows[index] = T{};
        }
        delete[] Rows[r].Cols;
        Rows[r].Cols = NULL;
        Rows[r].Cols = n_rows; 
        Rows[r].NumCols = C;  
    }
    
    /*
    void growcols(int r, int C)
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::growcols: row");
        if (C < 1)
            throw invalid_argument("mymatrix::growcols: columns");
        
        T* n_rows = new T[C];
        
        for (int i = 0; i < C; i++)
        {
            if (i < Rows[r].NumCols) {
                n_rows[i] = Rows[r].Cols[i];
                }
            else {
                n_rows[i] = T{};
                }
        }
        
            delete[] Rows[r].Cols;
            Rows[r].Cols = n_rows;
            Rows[r].NumCols = C;
    }*/

    //
    // grow
    //
    // Grows the size of the matrix so that it contains at least R rows,
    // and every row contains at least C columns.
    // 
    // If the matrix contains fewer than R rows, then rows are added
    // to the matrix; each new row will have C columns initialized to 
    // the default value of T.  If R <= numrows(), then all existing
    // rows are retained -- we never reduce the # of rows.
    //
    // If any row contains fewer than C columns, then columns are added
    // to increase the # of columns to C; existing values are retained
    // and additional columns are initialized to the default value of T.
    // If C <= numcols(r) for any row r, then all existing columns are
    // retained -- we never reduce the # of columns.
    // 
    
    /*
    The function first checks if the new number of rows and columns are valid input values. 
    If the number of rows is greater than the current number of rows, it creates a new array 
    of rows with the desired number of rows, and then loops through each row to either copy 
    the existing values from the original matrix or initialize new values to the default value 
    for the data type. If the new number of columns is greater than the current number of columns, 
    the growcols function is called to increase the number of columns for each row. Finally, 
    the function updates the NumRows variable to reflect the new number of rows and replaces 
    the Rows array with the new array created earlier.
    */
    void grow(int R, int C)
    {
        if (R < 1)
            throw invalid_argument("mymatrix::grow: # of rows");
        if (C < 1)
            throw invalid_argument("mymatrix::grow: # of cols");

        //
        // TODO:
        //
        if (NumRows < R) 
        { 
           
            ROW* new_Row = new ROW[R];
            for (int index = 0; index < R; index++)
            {
                if (index < NumRows)
                { 
                    int n_col_len = C;
                    int c_col_len = this->Rows[index].NumCols;
                    if (c_col_len > n_col_len)
                    {  
                        n_col_len = c_col_len;
                    }
                    else 
                    {
                        new_Row[index].Cols = new T[n_col_len]; 
                        new_Row[index].NumCols = n_col_len; 
                        for (int a = 0; a < n_col_len; a++) { 
                            if (a < c_col_len)
                            {
                                new_Row[index].Cols[a] = this->Rows[index].Cols[a];
                            }
                            else
                            { 
                                new_Row[index].Cols[a] = T{};
                            }
                        }
                    }
                }
                else
                { 
                    new_Row[index].Cols = new T[C];
                    new_Row[index].NumCols = C;
                    int y = 0;
                    while (y < C)
                    {
                        new_Row[index].Cols[y] = T{};
                        y++;
                    }
                    
                }
            }
            Rows = new_Row;
            NumRows = R;
        }
        else { 
            for (int row_indexed = 0; row_indexed < NumRows; row_indexed++)
            {
                growcols(row_indexed, C);
                /*if (Rows[row_indexed].NumCols < C)
                {
                    
                }*/
            }
        }
    }


    //
    // size
    //
    // Returns the total # of elements in the matrix.
    //
    
    /*
    The size() method is returning the total number of elements in the matrix by summing up 
    the number of columns in each row. It initializes a variable total to zero, then iterates 
    through all the rows of the matrix and adds the number of columns in each row to total. 
    Finally, it returns the sum.
    */
    int size() const
    {
        //
        // TODO
        //
        int total = 0;

        for (int i = 0; i < NumRows; ++i) {
            total = total + Rows[i].NumCols;
        }
        return total;
        
    }


    //
    // at
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    M.at(r, c) = ...
    //    cout << M.at(r, c) << endl;
    //
    
    /*
    This is the implementation of the at() method which returns a reference to the element 
    at the specified row and column of the matrix. It takes two arguments r and c representing 
    the row and column index respectively.
    */
    T& at(int r, int c) const
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::at: row");
        if (c < 0 || c >= Rows[r].NumCols)
            throw invalid_argument("mymatrix::at: col");

        //
        // TODO
        //

        T* temp = &Rows[r].Cols[c];  // we need to return something, so a temp for now:

        return *temp;
    }


    //
    // ()
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    M(r, c) = ...
    //    cout << M(r, c) << endl;
    //
    
    /*
    This code defines an overload of the parentheses operator that allows accessing elements 
    of a mymatrix object using the syntax matrix(r, c). It first checks if the given row and 
    column indices are within bounds, and then returns a reference to the element at the specified 
    position in the matrix.
    */
    T& operator()(int r, int c) const
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::(): row");
        if (c < 0 || c >= Rows[r].NumCols)
            throw invalid_argument("mymatrix::(): col");

        //
        // TODO
        //

        T* temp = &Rows[r].Cols[c];  // we need to return something, so a temp for now:

        return *temp;
    }

    //
    // scalar multiplication
    //
    // Multiplies every element of this matrix by the given scalar value,
    // producing a new matrix that is returned.  "This" matrix is not
    // changed.
    //
    // Example:  M2 = M1 * 2;
    //
    
    /*
    This code defines an overloaded multiplication operator for the mymatrix class 
    that allows the matrix to be multiplied by a scalar value. The code first creates 
    a copy of the matrix using the copy constructor, then multiplies each element 
    of the matrix by the scalar value. Finally, the modified copy is returned as the result.
    */
    mymatrix<T> operator*(T scalar)
    {
        mymatrix<T> result = *this;

        //
        // TODO
        //

        for (int row_index = 0; row_index < NumRows; row_index++)
        {
            for (int col_index = 0; col_index < Rows[row_index].NumCols; col_index++)
            {
                result.Rows[row_index].Cols[col_index] = Rows[row_index].Cols[col_index] * scalar;
            } 
        } 

        return result;
    }


    //
    // matrix multiplication
    //
    // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
    // M2 is the "other" matrix.  This produces a new matrix, which is returned.
    // "This" matrix is not changed, and neither is the "other" matrix.
    //
    // Example:  M3 = M1 * M2;
    //
    // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
    // addition, the sizes of M1 and M2 must be compatible in the following sense:
    // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
    // multiplication can be performed, and the resulting matrix is of size RxC.
    //
    mymatrix<T> operator*(const mymatrix<T>& other)
    {
        //mymatrix<T> result;

        //
        // both matrices must be rectangular for this to work:
        //

        //
        // TODO
        //
        // if (this matrix is not rectangular)
        //   throw runtime_error("mymatrix::*: this not rectangular");
        //
        for (int i = 0; i < numrows(); ++i)
        { 
            for (int j = 0; j < numrows(); ++j)
            {
                if (Rows[i].NumCols == Rows[j].NumCols)
                {
                    continue;
                }
                else {
                    throw runtime_error("mymatrix::*: this not rectangular");
                    break;
                }
            }
            break; 
        }
        // if (other matrix is not rectangular)
        //   throw runtime_error("mymatrix::*: other not rectangular");
        for (int x = 0; x < other.numrows(); x++) 
        {
            for (int y = 0; y < (other.numrows()); y++)
            {
                if (other.Rows[x].NumCols == other.Rows[y].NumCols)
                {
                    continue;
                }
                else {
                    throw runtime_error("mymatrix::*: other not rectangular");
                    break;
                }
            }
            break; 
        }
        //mymatrix<T> result(NumRows, other.Rows[0].NumCols);
        //
        // Okay, both matrices are rectangular.  Can we multiply?  Only
        // if M1 is R1xN and M2 is NxC2.  This yields a result that is
        // R1xC2.
        // 
        // Example: 3x4 * 4x2 => 3x2
        //

        //
        // TODO
        //
        // if (this matrix's # of columns != other matrix's # of rows)
        //   throw runtime_error("mymatrix::*: size mismatch");
        if (this->Rows[0].NumCols != other.NumRows)
        {
            throw runtime_error("mymatrix::*: size mismatch");
        }

        for (int index = 0; index < NumRows; index++)
        {
            if (Rows[index].NumCols == other.numrows())
            {
                break;
            }
            else
            {
                throw runtime_error("mymatrix::*: size mismatch");
            }
        }
        //
        // Okay, we can multiply:
        //

        //
        // TODO
        //
        mymatrix<T> result(NumRows, other.Rows[0].NumCols);

        for (int x = 0; x < NumRows; x++)
        {
            for (int y = 0; y < other.Rows[0].NumCols; y++)
            {
                result.Rows[x].Cols[y] = 0;
                for (int z = 0; z < Rows[0].NumCols; z++)
                {
                    result.Rows[x].Cols[y] += this->Rows[x].Cols[z] * other.Rows[z].Cols[y];
                }
            }
        }

        return result;

    }


    //
    // _output
    //
    // Outputs the contents of the matrix; for debugging purposes.
    //
    
    /*
    this function is used to display the contents of a matrix to the user.
    */
    void _output()
    {
        for (int r = 0; r < this->NumRows; ++r)
        {
            for (int c = 0; c < this->Rows[r].NumCols; ++c)
            {
                cout << this->Rows[r].Cols[c] << " ";
            }
            cout << endl;
        }
    }

};
