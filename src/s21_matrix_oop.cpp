
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1) {
  AlocMatrix(&matrix_, rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows > 0 && cols > 0) {
    AlocMatrix(&matrix_, rows_, cols_);
  } else {
    std::cout << "Invalid argument values";
  };
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    DelMatrix(matrix_);
  }
}

// Accessor and mutator (Getters and setters)

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows == rows_)
    return;
  double **newMatrix;
  AlocMatrix(&newMatrix, rows, cols_);
  for (int i = 0; i < rows && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      newMatrix[i][j] = (*this)(i, j);
    }
  }
  DelMatrix(matrix_);
  rows_ = rows;
  matrix_ = newMatrix;
}

void S21Matrix::SetCols(int cols) {
  if (cols == cols_)
    return;
  double **newMatrix;
  AlocMatrix(&newMatrix, rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols && j < cols_; j++) {
      newMatrix[i][j] = (*this)(i, j);
    }
  }
  DelMatrix(matrix_);
  cols_ = cols;
  matrix_ = newMatrix;
}

// Main functions:

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = false;
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    result = true;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (this->matrix_[i][j] != other.matrix_[i][j]) {
          result = false;
        };
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
      }
    }
  } else {
    std::cout << "Different matrix sizes";
  };
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
      }
    }
  } else {
    std::cout << "Different matrix sizes";
  };
}

void S21Matrix::MulNumber(const double num) {
  if (num > 0 || num <= 0) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] * num;
      }
    }
  } else {
    std::cout << "Incorrect number";
  };
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ == other.rows_) {
    // double buffer[this->rows_*other.cols_]={0};
    double *buffer = new double[this->rows_ * other.cols_];
    buffer[this->rows_ * other.cols_] = {0};
    int k = 0;
    for (int i = 0; i < this->rows_; i++) {
      int h = 0;
      while (h < other.cols_) {
        double x = 0;
        for (int j = 0; j < this->cols_; j++) {
          x += this->matrix_[i][j] * other.matrix_[j][h];
        }
        buffer[k] = x;
        k++;
        h++;
      }
    }
    this->ReplacementMatrix(buffer, this->rows_, other.cols_);
    delete[] buffer;
  } else {
    std::cout << "The number of columns of the first matrix is not equal to "
                 "the number of rows of the second matrix";
  }
}

void S21Matrix::Transpose() {
  if (this->rows_ > 0 && this->cols_ > 0) {
    // double buffer[this->rows_*this->cols_] = {0};
    double *buffer = new double[this->rows_ * this->cols_];
    int k = 0;
    for (int i = 0; i < this->cols_; i++) {
      for (int j = 0; j < this->rows_; j++) {
        buffer[k] = this->matrix_[j][i];
        k++;
      }
    }
    this->ReplacementMatrix(buffer, this->cols_, this->rows_);
    delete[] buffer;
  }
}

void S21Matrix::CalcComplements() {
  if ((this->rows_ == this->cols_) && this->cols_ > 1) {
    // double result[this->rows_*this->cols_]={0};
    double *result = new double[this->rows_ * this->cols_];
    int k = 0;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        double det = 0;
        S21Matrix buffer(this->rows_ - 1, this->cols_ - 1);
        buffer.SmallMatrix(i, j, *this);
        det = buffer.Determinant();
        result[k] = pow(-1, (i + j)) * det;
        k++;
      }
    }
    this->ReplacementMatrix(result, this->rows_, this->cols_);
    delete[] result;
  }
}

double S21Matrix::Determinant() {
  double x = 0;
  if (this->rows_ == this->cols_) {
    if (this->cols_ > 2) {
      int n = 1;
      for (int i = 0; i < this->cols_; i++) {
        S21Matrix buffer(this->rows_ - 1, this->cols_ - 1);
        buffer.SmallMatrix(0, i, *this);
        double vr = buffer.Determinant();
        x = x + n * this->matrix_[0][i] * vr;
        n = n * (-1);
      }
    } else if (this->cols_ == 2) {
      x += this->Minor();
    } else if (this->cols_ == 1) {
      x += this->matrix_[0][0];
    }
  }
  return x;
}

void S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det != 0) {
    double *result = new double[this->rows_ * this->cols_];
    S21Matrix buffer(*this);
    buffer.CalcComplements();
    buffer.Transpose();
    int k = 0;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result[k] = buffer.matrix_[i][j] / det;
        k++;
      }
    }
    this->ReplacementMatrix(result, this->rows_, this->cols_);
    delete[] result;
  }
}

// Operators () + - * = == *= -= +=

double &S21Matrix::operator()(int i, int j) {
  CheckInd(i, j);
  return matrix_[i][j];
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double &num) {
  S21Matrix res = *this;
  MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }
void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }
void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }
void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }
void S21Matrix::operator*=(const double &num) { MulNumber(num); }

// Other methods..

void S21Matrix::FillMatrix(double *seq) {
  int n = 0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = seq[n++];
    }
  }
}

void S21Matrix::SmallMatrix(int n, int m, S21Matrix &other) {
  int p = 0;
  int t = 0;
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      if (i != n && j != m) {
        this->matrix_[p][t] = other.matrix_[i][j];
        t++;
        if (t == this->cols_) {
          p++;
          t = 0;
        }
      }
    }
  }
}

double S21Matrix::Minor() {
  double x = 0;
  x = (this->matrix_[0][0] * this->matrix_[1][1]) -
      (this->matrix_[0][1] * this->matrix_[1][0]);
  return x;
}

void S21Matrix::ReplacementMatrix(double *seq, int rows, int cols) {
  DelMatrix(this->matrix_);
  AlocMatrix(&matrix_, rows, cols);
  this->cols_ = rows;
  this->rows_ = cols;
  this->FillMatrix(seq);
}

void S21Matrix::CheckInd(int i, int j) {
  if (i < 0 || i > rows_ - 1) {
    std::cout << "Invalid argument of rows";
  }
  if (j < 0 || j > cols_ - 1) {
    std::cout << "Invalid argument of cols";
  }
}

void S21Matrix::AlocMatrix(double ***matrix, int rows, int cols) {
  if (rows > 0 && cols > 0) {
    *matrix = new double *[rows]();
    for (int i = 0; i < rows; i++) {
      (*matrix)[i] = new double[cols]();
    }
  } else {
    std::cout << "Invalid argument values";
  };
}

void S21Matrix::DelMatrix(double **matrix) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}
