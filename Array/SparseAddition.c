#include <stdio.h>

#define MAX 10

typedef struct {
    int row;
    int col;
    int value;
} Triple;

// Function declarations
void createMatrix(int matrix[MAX][MAX], int rows, int cols); 
void printMatrix(int matrix[MAX][MAX], int rows, int cols);
int createSparse(int matrix[MAX][MAX], int rows, int cols, Triple sparse[]);
int addSparse(Triple a[], int sizeA, Triple b[], int sizeB, Triple result[]);
void sparseToMatrix(Triple sparse[], int size, int matrix[MAX][MAX]);

// Main function
int main() {
    int rows, cols;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    Triple sparseA[MAX], sparseB[MAX], sparseC[MAX];
    int sizeA, sizeB, sizeC;

    printf("Enter number of rows and columns of the matrices: ");
    scanf("%d%d", &rows, &cols);

    printf("\nEnter elements for Matrix A:\n");
    createMatrix(A, rows, cols);

    printf("\nEnter elements for Matrix B:\n");
    createMatrix(B, rows, cols);

    printf("\nMatrix A:\n");
    printMatrix(A, rows, cols);

    printf("\nMatrix B:\n");
    printMatrix(B, rows, cols);

    // Convert to sparse representation
    sizeA = createSparse(A, rows, cols, sparseA);
    sizeB = createSparse(B, rows, cols, sparseB);

    // Add sparse matrices
    sizeC = addSparse(sparseA, sizeA, sparseB, sizeB, sparseC);

    // Convert result back to matrix
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            C[i][j] = 0; // initialize C

    sparseToMatrix(sparseC, sizeC, C);

    printf("\nResultant Matrix C (A + B):\n");
    printMatrix(C, rows, cols);

    return 0;
}

// Function to create matrix with user input
void createMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to print matrix
void printMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to create sparse triplet representation
int createSparse(int matrix[MAX][MAX], int rows, int cols, Triple sparse[]) {
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }
    return k; // number of non-zero elements
}

// Function to add two sparse matrices
int addSparse(Triple a[], int sizeA, Triple b[], int sizeB, Triple result[]) {
    int i = 0, j = 0, k = 0;

    while (i < sizeA && j < sizeB) {
        // Compare positions
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            result[k] = a[i];
            result[k].value = a[i].value + b[j].value;
            i++; j++; k++;
        }
        else if (a[i].row < b[j].row || 
                (a[i].row == b[j].row && a[i].col < b[j].col)) {
            result[k++] = a[i++];
        }
        else {
            result[k++] = b[j++];
        }
    }

    // Remaining elements
    while (i < sizeA) result[k++] = a[i++];
    while (j < sizeB) result[k++] = b[j++];

    return k; // total non-zero elements in result
}

// Function to convert sparse to full matrix
void sparseToMatrix(Triple sparse[], int size, int matrix[MAX][MAX]) {
    for (int i = 0; i < size; i++) {
        matrix[sparse[i].row][sparse[i].col] = sparse[i].value;
    }
     printf("\nSparse Representation of Matrix C \n");
     printf("Row Col Value\n");
    for (int i = 0; i < size; i++) {
        printf("%3d %3d %5d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }
}