// Atharva Manjrekar

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Predefined matrix of size 4x5
#define m 4
#define n 5

class SparseMatrix {
public:
    void get(int, int);
    void set(int, int, int);
    void add();
    void printMatrix();
    void openFile(string);   

private:
    int sparseMatrix[m][n]; //First SparseMatrix defined as 4x5
    int sparseMatrix2[m][n]; //Second SparseMatrix defined as 4x5 aswell which will be used for the add() function
    int elements=0; //non-zero elements are initialized to zero and will later increase
    int new_matrix[0][3]; //initialize new_matrix with 0 rows and 3 cols which is the minimum size it can be
};

// This function will print the Compact Matrix based on the number of non-zero elements
void SparseMatrix :: printMatrix(){
    for (int i=0; i<elements; i++) {
        for (int j=0; j<3; j++) {
            cout << new_matrix[i][j] << "     ";
        }
        printf("\n");
    }
}

void SparseMatrix :: openFile(string inFileName){
    ifstream inFile;
    inFile.open(inFileName.c_str());

    // Open the input file and loop over its rows and cols to extract number of non-zero elements
    if (inFile.is_open()) {
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                inFile >> sparseMatrix[i][j]; //extract info from txt file into a 2D array called sparseMatrix[i][j]
                if (sparseMatrix[i][j] != 0) {
                    elements++;
                }
            }    
        }
        inFile.close(); // Close input file
    }
    else  { //Error message
        cerr << "Can't find input file " << inFileName << endl;
    }
}

void SparseMatrix :: get(int i, int j) 
{
    openFile("sparsematrix.txt"); //Use the openFile() function to open an input file and extract values
    new_matrix[elements][j]; //set new_matrix where size of rows are determined by number of non-zero elements
    int t=0;

    //Creating a compact matrix called new_matrix
    for (int k=0; k<m; k++) {
        for (int l=0; l<n; l++) {
            if (sparseMatrix[k][l] != 0) {
                new_matrix[t][0] = k;
                new_matrix[t][1] = l;
                new_matrix[t][2] = sparseMatrix[k][l];
                t++;
            }
        }    
    }
    //Print out the Compact Matrix with only non-zero elements and their locations
    cout << "\n" << "----------------" << "\n" << "Compact Matrix" << "\n" << "Row  Col  Val \n" << "----------------" << "\n"; 
    printMatrix();

    cout << "\nget function returns: \n";
    for (int k=0; k<elements; k++){
        if (new_matrix[k][0] == i && new_matrix[k][1] == j){
            cout << "The value at row " << i << " and column " << j << " in the Compact Matrix is " << new_matrix[k][2] << "\n";
        }
    }
    //cout << "The value at row " << i << " and column " << j << " in the SparseMatrix is " << sparseMatrix[i][j] << "\n";
}

void SparseMatrix :: set(int i, int j, int k)
{   
    cout << "\nset function returns: \n";
    for (int a=0; a<elements; a++){
        if (new_matrix[a][0] == i && new_matrix[a][1] == j){
            cout << "The value at row " << i << " and column " << j << " in the Compact Matrix was changed from " << new_matrix[a][2] << " to " << k << "\n";
            new_matrix[a][2]=k;
        }
    }
    cout << "\n" << "----------------\n" << "New Compact Matrix" << "\n" << "Row  Col  Val \n" << "----------------" << "\n";
    printMatrix();

    //cout << "The value at row " << i << " and column " << j << " was changed from " << sparseMatrix[i][j] << " to " << k << "\n";
    sparseMatrix[i][j] = k;
}

void SparseMatrix :: add()
{
    string inFileName = "sparsematrix2.txt";
    ifstream inFile;
    inFile.open(inFileName.c_str());
    cout << "\n" << "------------------" << "\n" << "New Sparse Matrix: " << "\n";
    if (inFile.is_open()) {
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                inFile >> sparseMatrix2[i][j];
                    sparseMatrix[i][j] += sparseMatrix2[i][j]; // Add values from second sparse matrix into our original matrix
                    cout << " " << sparseMatrix[i][j];
            }
            cout << "\n";    
        }
        inFile.close(); // Close input file
    }
    else  { //Error message
        cerr << "Can't find input file " << inFileName << endl;
    }
}

int main()
{
    SparseMatrix obj;
    obj.get(1,3);
    obj.set(3,4,5);
    obj.add();
    return 0;
}
