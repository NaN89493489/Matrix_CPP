#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(Test, constructor) {
  S21Matrix A;
  int i = A.GetRows();
  int j = A.GetCols();
  EXPECT_EQ(i, j);
}

TEST(Test, constructor_move) {
  S21Matrix A(2, 2);
  S21Matrix B(std::move(A));
  EXPECT_EQ(2, B.GetRows());
  EXPECT_EQ(2, B.GetCols());
  EXPECT_EQ(0, A.GetRows());
}

TEST(Test, transfer_konstruktor) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 4;
  a(1, 0) = 3;
  a(1, 1) = 2;
  S21Matrix b(a);
  ASSERT_TRUE(b == a);
}

TEST(Test, transfer_konstruktor2) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 4;
  a(1, 0) = 3;
  a(1, 1) = 2;
  a *= a;
  S21Matrix b(a);
  ASSERT_TRUE(b == a);
}

TEST(Test, transfer_konstruktor3) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 4;
  a(1, 0) = 3;
  a(1, 1) = 2;
  a = a * a;
  S21Matrix b(a);
  ASSERT_TRUE(b == a);
}

TEST(Test, set_rows) {
  S21Matrix A(3, 3);
  A.SetRows(4);
  EXPECT_EQ(4, A.GetRows());
}

TEST(Test, set_cols) {
  S21Matrix A(3, 3);
  A.SetCols(7);
  EXPECT_EQ(7, A.GetCols());
}

TEST(Test, get_rows) {
  S21Matrix A(3, 4);
  EXPECT_EQ(3, A.GetRows());
}
TEST(Test, constructor_3_5) {
  S21Matrix A(3, 5);
  EXPECT_EQ(3, A.GetRows());
  EXPECT_EQ(5, A.GetCols());
}

TEST(Test, equality) {
  S21Matrix A(4, 4);
  S21Matrix D(4, 4);
  ASSERT_TRUE(A == D);
}

TEST(EqMatrix, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(OperatorsOverload, PlusThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = i * j * 3.5;
      b(i, j) = i * j * 2.5;
      c(i, j) = i * j * (3.5 + 2.5);
    }
  }
  ASSERT_TRUE(a + b == c);
}

TEST(AccessorMutator, get_rowsTest) {
  S21Matrix a(3, 4);
  EXPECT_EQ(a.GetRows(), 3);
  // a.~S21Matrix();
}

TEST(Test, mul_mtx) {
  S21Matrix a(2, 2);
  a(0, 0) = 5;
  a(0, 1) = 4;
  a(1, 0) = 3;
  a(1, 1) = 2;
  a = a * 2;
  S21Matrix b(a);
  ASSERT_TRUE(b == a);
}

TEST(AccessorMutator, get_colsTest) {
  S21Matrix a(3, 4);
  EXPECT_EQ(a.GetCols(), 4);
}

TEST(AccessorMutator, SetRowsTwo) {
  S21Matrix a(4, 3);
  a.SetRows(3);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_FALSE(a.GetRows() == 4);
}

TEST(OperatorsOverload, assignment) {
  S21Matrix a(3, 3);
  S21Matrix c(4, 4);
  a = c;
  EXPECT_FALSE(a == c);
}

TEST(EqMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorsOverload, notEqual) {
  S21Matrix a(3, 3);
  S21Matrix b(4, 4);
  int z = a == b;
  ASSERT_TRUE(z == 0);
}

TEST(OperatorsOverload, MinusThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = i * j * 2.5;
      b(i, j) = i * j * 2.3;
      c(i, j) = i * j * (2.5 - 2.3);
    }
  }
  ASSERT_TRUE(a - b == c);
}

TEST(OperatorsOverload, PlusEqualTwo) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(0, 0) = 7.7;
  a(0, 1) = 6.7;
  a(1, 0) = 5.7;
  a(1, 1) = 4.7;
  b(0, 0) = 2.3;
  b(0, 1) = 3.3;
  b(1, 0) = 4.3;
  b(1, 1) = 5.3;
  c(0, 0) = 10;
  c(0, 1) = 10;
  c(1, 0) = 10;
  c(1, 1) = 10;
  a += b;
  ASSERT_TRUE(a == c);
}

TEST(OperatorsOverload, PlusEqualThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = i * j * 2.2;
      b(i, j) = i * j * 3.3;
      c(i, j) = i * j * (2.2 + 3.3);
    }
  }
  a += b;
  ASSERT_TRUE(a == c);
}

TEST(OperatorsOverload, MinusEqualThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = i * j * 2.2;
      b(i, j) = i * j * 1.7;
      c(i, j) = i * j * (2.2 - 1.7);
    }
  }
  a -= b;
  ASSERT_TRUE(a == c);
}

TEST(OperatorsOverload, MultNumberEqualOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = 2;
      b(i, j) = 2 * 3.14;
    }
  }
  a *= 3.14;
  ASSERT_TRUE(a == b);
}
TEST(OperatorsOverload, MulNumberEqualTwo) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  e(0, 0) = 10;
  e(0, 1) = 8;
  e(1, 0) = 6;
  e(1, 1) = 4;
  f(0, 0) = -5;
  f(0, 1) = -4;
  f(1, 0) = -3;
  f(1, 1) = -2;
  e *= -0.5;
  ASSERT_TRUE(e == f);
}

TEST(OperatorsOverload, IndexTwo) {
  S21Matrix a(34, 36);
  a(21, 21) = 21;
  ASSERT_TRUE(a(21, 21) == 21);
}

TEST(MatrixOperations, MulNumberOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = 2;
      b(i, j) = 2 * 3.14;
    }
  }
  a.MulNumber(3.14);
  ASSERT_TRUE(a == b);
}
TEST(MatrixOperations, MulNumberTwo) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  e(0, 0) = 10;
  e(0, 1) = 8;
  e(1, 0) = 6;
  e(1, 1) = 4;
  f(0, 0) = -5;
  f(0, 1) = -4;
  f(1, 0) = -3;
  f(1, 1) = -2;
  e.MulNumber(-0.5);
  ASSERT_TRUE(e == f);
}

TEST(Test, inverst_test) {
  S21Matrix result(3, 3);
  S21Matrix res(3, 3);
  double buff[9] = {1, 0.75, -0.75, 2, 3, 0.5, 10, 2, 6};
  double otv[9] = {0.544,  -0.192, 0.084, -0.224, 0.432,
                   -0.064, -0.832, 0.176, 0.048};
  result.FillMatrix(buff);
  res.FillMatrix(otv);
  result.InverseMatrix();
  ASSERT_TRUE(result == res);
}

TEST(Test, mul_test) {
  S21Matrix result(3, 1);
  S21Matrix mul(1, 3);
  S21Matrix res(3, 3);
  double buff[3] = {1, 2.75, 9};
  double buff2[3] = {1, 0.75, -0.75};
  double otv[9] = {1, 0.75, -0.75, 2.75, 2.0625, -2.0625, 9, 6.75, -6.75};
  result.FillMatrix(buff);
  mul.FillMatrix(buff2);
  res.FillMatrix(otv);
  result.MulMatrix(mul);
  ASSERT_TRUE(result == res);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}