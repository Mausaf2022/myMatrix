/*
Mutafa Ausaf
Project 3--CS251-SPRING2023--mymatrix
Dr Adam T Koehler.
*/
#include <iostream>
#include <exception>
#include <stdexcept>
#include "mymatrix.h"

using namespace std;

bool size_test1(); 
bool exception_test_example(); 
bool intializting_test2(); 
bool parametarized_test3(); 
bool chaning_matrix_elements_test4(); 
bool grow_matrix_test5(mymatrix<int>); 
bool copy_constructor_test6(); 
bool matrix_multiplication_test7(mymatrix<int>); 
bool grow_col_test8(mymatrix<int>); 

/*
This is the main function which is running a series of tests on the mymatrix class.
It creates an instance of the class, sets its elements, and then runs various test functions
to check its functionalities such as initializing matrix, accessing elements, changing elements,
growing matrix, matrix multiplication, and handling exceptions. The results of the tests are stored 
in the passed and failed variables, and at the end of all tests, the number of passed and failed tests
are printed on the console.
*/
int main()
{
	int passed = 0;
	int failed = 0;
	
	mymatrix<int> m1;
	m1(0, 0) = 1;
	m1(1, 1) = 2;
	m1(2, 2) = 3;
	m1(3, 3) = 4;
	grow_matrix_test5(m1);
	if (size_test1())
		passed++;
	else {
		cout << "size_test1 failed"	<< endl;
		failed++;
	}
	if (intializting_test2())
	{
		passed++;
	}
	else
	{
		cout << "intializting_test2 failed" << endl;
		failed++;
	}
	if (parametarized_test3())
	{
		passed++;
	}
	else
	{
		cout << "parameterzied_test failed" << endl;
		failed++;
	}
	if (copy_constructor_test6()) {
		passed++;
	}
	else
	{
		cout << "Copy constructor failed";
		failed++;
	}
	if (exception_test_example())
	{
		passed++;	
	}
	else {
		failed++;
	}
	if (grow_col_test8(m1))
	{
		passed++;
	}
	else
	{
		failed++;
		cout << "grow_col_test failed" << endl;
	}
	if (chaning_matrix_elements_test4())
	{
		passed++;
	}
	else
	{
		failed++;
	}

	if (matrix_multiplication_test7(m1))
	{
		passed++;
	}
	else
	{
		failed++;
		cout << "matrix_multiplication_test7 failed" << endl;
	}
	
	cout << "Tests passed : "		<< passed << endl;
	cout << "Tests failed : "		<< failed << endl;
	return 0;
}

// This function tests whether the size of a matrix object is calculated and returned correctly.
bool size_test1()
{
	// creates 4x4 matrix
	mymatrix<int> M;
	if (M.size() == 16)
		return true;
	else
		return false;
}

/*
This function tests whether an exception is thrown in a specific scenario, 
possibly to test the error handling of the program.
*/
bool exception_test_example()
{
	try {
		mymatrix<int> M1;
		mymatrix<int> M2;
		M1.growcols(3, 16);
		mymatrix<int> result;
		result = M1 * M2;
		// matrix multiply should throw an exception
		// if we get here
		// no exception was thrown --- error
		cout << "matrix multiply test failed: "<< "jagged matrix did not throw exception"<< endl;
		//failed++;
		return false;
	}
	catch (...) {
		//passed++;
		// if we get here,
		// exception was thrown --- correct
		//cout << "Exception thrown" << endl;
		return true;
	}
	return -1;
}

// This function tests whether the initialization of a matrix object is done correctly.
bool intializting_test2()
{
	try {
		mymatrix<int> TEST;
		cout << "Intializing Test Case 2" << endl;
		cout << "Output of default 4x4 matrix with 0's" << endl;
		TEST._output();
		return true;
	}
	catch (...)
	{
		return false;
	}
}

// This function tests whether a matrix object is initialized correctly with specific parameters.
bool parametarized_test3() {
	try {
		int rows = 0;
		int columns = 0;
		cout << "Parameterized Matrix Intialization Test Case 3" << endl;
		cout << "Enter number of rows: ";
		cin >> rows;
		cout << "Enter Number of columns: ";
		cin >> columns;
		mymatrix<int> m(rows, columns);
		m._output();
		return true;
	}
	catch (...)
	{
		return false;
	}

}

// This function tests whether the elements of a matrix object can be changed correctly.
bool chaning_matrix_elements_test4()
{
	try {
		mymatrix<int> m1;
		cout << "Changing or Updating matrix elements using operator () Test Case 4 " << endl;
		cout << "Changing 0's to other values" << endl;
		m1(0, 0) = 1;
		m1(1, 1) = 2;
		m1(2, 2) = 3;
		m1(3, 3) = 4;
		
		m1._output();
		return true;
	}
	catch (...)
	{
		return false;
	}

}

// This function tests whether a copy of a matrix object is created correctly.
bool copy_constructor_test6() {
	try {
		mymatrix<int> m1;
		m1(0, 0) = 1;
		m1(1, 1) = 2;
		m1(2, 2) = 3;
		m1(3, 3) = 4;
		cout << "\nCopy constructor test\nOriginal Matrix" << endl;
		m1._output();
		mymatrix<int>m2 = m1;
		m2(0, 1) = 6;
		cout << "Copied Matrix with changes at (0,1):" << endl;
		m2._output();
		return true;
	}
	catch (...)
	{
		cout << "Copy constructor failed" << endl;
		return false;
	}
}

// This function tests whether a matrix object can be resized correctly by adding columns.
bool grow_col_test8(mymatrix<int> m1) {
	try
	{
		cout << "\nGrow Column number Test" << endl;
		cout << "Original matrix: " << endl;

		m1._output();
		int row = 0;
		int col = 0;
		cout << "Enter row >> ";
		cin >> row;
		cout << "Enter new number of columns at row " << row << " >> ";
		cin >> col;

		cout << "\nNew matrix: " << endl;
		m1.growcols((row - 1), col);
		m1._output();
		//cout << "Cols: " << m1.numcols(0) << endl;
		return true;
	}
	catch (...)
	{
		cout << "Column grow test failed" << endl;
		return false;
	}

}

// This function tests whether matrix multiplication is performed correctly on two matrix objects.
bool matrix_multiplication_test7(mymatrix<int> m1)
{
	try
	{

		mymatrix<int>m2(4, 6);

		m2(0, 1) = 4;
		m2(2, 2) = 1;
		m2(1, 4) = 3;
		m2(1, 1) = 2;
		m2(2, 4) = 1;

		cout << "Matrix Multiplication Test\n" << endl;
		cout << "Matrix 1: " << endl;
		m1._output();
		cout << "\nMatrix 2: " << endl;
		m2._output();
		mymatrix<int>resultant = m1 * m2;
		cout << "\nMultiplication result of Matrix 1 and Matrix 2 (m1*m2)\n" << endl;
		resultant._output();
		return true;
	}
	catch (...)
	{
		cout << "Matrix multiplication test failed" << endl;
		return false;
	}
}

// This function tests whether a matrix object can be resized correctly by adding rows and columns.
bool grow_matrix_test5(mymatrix<int> m1)
{
	try
	{
		cout << "Grow Matrix test\n" << endl;
		cout << "Original matrix:" << endl;
		m1._output();
		int row = 0;
		int col = 0;
		cout << "Enter new Number of rows: ";
		cin >> row;
		cout << "Enter new Number of columns: ";
		cin >> col;
		cout << "Updated Matrix: " << endl;
		m1.grow(row, col);
		m1._output();
		return true;
	}
	catch (...)
	{
		cout << "Grow Matrix function failed" << endl;
		return false;
	}

}
