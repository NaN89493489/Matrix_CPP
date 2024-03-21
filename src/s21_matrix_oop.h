#include <cmath>
#include <iostream>

class S21Matrix {
private:
  // Attributes
  int rows_, cols_; // Rows and columns
  double **matrix_; // Pointer to the memory where the matrix is allocated

public:
  S21Matrix(); // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix(); // Destructor

  // Accessor and mutator:
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // Functions:
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  void Transpose();
  void CalcComplements();
  double Determinant();
  void InverseMatrix();

  // Operators:
  double &operator()(int i, int j);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double &num);
  bool operator==(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(const double &num);

  // Other methods..
  void AlocMatrix(double ***matrix, int rows, int cols);
  void ReplacementMatrix(double *seq, int rows, int cols);
  void FillMatrix(double *seq);
  void CheckInd(int i, int j);
  void SmallMatrix(int n, int m, S21Matrix &other);
  double Minor();
  void DelMatrix(double **matrix);
};
