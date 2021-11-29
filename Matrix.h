//
// Created by Jiang Kairong on 2/17/18.
//

#ifndef PROG03_INLINEBOOL_MATRIX_H
#define PROG03_INLINEBOOL_MATRIX_H

#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cmath>

template<typename T, unsigned long Rows = 0, unsigned long Cols = 0>
class Matrix {
public:
  explicit Matrix();

  explicit Matrix(T initialValue);

  Matrix(std::initializer_list<T> initializer);
//  ~Matrix();

  Matrix(const Matrix<T, Rows, Cols> &rhs);

  const T &operator()(int i, int j) const;

  T &operator()(int i, int j);

  const T &operator()(int i) const;

  T &operator()(int i);

  Matrix &resize(unsigned long rows, unsigned long cols);

  Matrix &operator=(Matrix rhs);

  template<unsigned long RhsCols>
  Matrix<T, Rows, RhsCols> operator*(const Matrix<T, Cols, RhsCols> &rhs) const;

  template<typename U>
  const Matrix operator*(const U &rhs) const;

  template<typename U>
  Matrix &operator*=(const U &rhs);

  template<typename U>
  const Matrix operator/(const U &rhs) const;

  template<typename U>
  Matrix &operator/=(const U &rhs);

  template<typename U>
  const Matrix operator+(const U &rhs) const;

  template<typename U>
  Matrix &operator+=(const U &rhs);

  template<typename U>
  const Matrix operator-(const U &rhs) const;

  template<typename U>
  Matrix &operator-=(const U &rhs);

  const Matrix operator+(const Matrix &rhs) const;

  Matrix &operator+=(const Matrix &rhs);

  const Matrix operator-(const Matrix &rhs) const;

  Matrix &operator-=(const Matrix &rhs);

  const Matrix cwiseProduct(const Matrix &rhs) const;

  double norm() const;

  Matrix &normalize();

  const Matrix normalize() const;

  unsigned long rows() const;

  unsigned long cols() const;

  void print(std::ostream &os) const;

  const Matrix cross(const Matrix &rhs) const;

  T dot(const Matrix &rhs) const;

  T *getRawData();

protected:
  std::vector<T> data;
  unsigned long width, height;
};

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols>::Matrix() : width(Cols), height(Rows) {
  data = std::vector<T>(Rows * Cols, T(0));
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols>::Matrix(T initialValue) : width(Cols), height(Rows) {
  data = std::vector<T>(Rows * Cols, initialValue);
}

template<typename T, unsigned long Rows, unsigned long Cols>
unsigned long Matrix<T, Rows, Cols>::rows() const {
  return height;
}

template<typename T, unsigned long Rows, unsigned long Cols>
unsigned long Matrix<T, Rows, Cols>::cols() const {
  return width;
}

template<typename T, unsigned long Rows, unsigned long Cols>
const T &Matrix<T, Rows, Cols>::operator()(int i, int j) const {
  if (i >= height || j >= width || i < 0 || j < 0) {
    throw std::out_of_range("index out of bounds");
  }
  return data[i * width + j];
}

template<typename T, unsigned long Rows, unsigned long Cols>
T &Matrix<T, Rows, Cols>::operator()(int i, int j) {
  return const_cast<T &>((*static_cast<const Matrix<T, Rows, Cols> *>(this))(i, j));
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<unsigned long RhsCols>
Matrix<T, Rows, RhsCols> Matrix<T, Rows, Cols>::operator*(const Matrix<T, Cols, RhsCols> &rhs) const {

  if (width != rhs.height) {
    throw std::logic_error("wrong matrix sizes");
  }

  Matrix<T, Rows, RhsCols> res(0);

  if (Rows == 0 && RhsCols == 0) {
    res.resize(height, rhs.width);
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < rhs.width; j++) {
      for (int k = 0; k < width; k++) {
        res(i, j) += (*this)(i, k) * rhs(k, j);
      }
    }
  }

  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
void Matrix<T, Rows, Cols>::print(std::ostream &os) const {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      os << (*this)(i, j) << " ";
    }
    os << std::endl;
  }
}

template<typename T, unsigned long Rows, unsigned long Cols>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator+(const Matrix<T, Rows, Cols> &rhs) const {
  if (height != rhs.height || width != rhs.width) {
    throw std::logic_error("wrong matrix sizes");
  }
  Matrix<T, Rows, Cols> res(*this);
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] += rhs.data[i];
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols>::Matrix(const Matrix<T, Rows, Cols> &rhs) : width(rhs.width), height(rhs.height),
                                                                  data(rhs.data) {}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator=(const Matrix<T, Rows, Cols> rhs) {
  height = rhs.height;
  width = rhs.width;
  data = rhs.data;

  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator-(const Matrix<T, Rows, Cols> &rhs) const {
  if (height != rhs.height || width != rhs.width) {
    throw std::logic_error("wrong matrix sizes");
  }
  Matrix<T, Rows, Cols> res(*this);
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] -= rhs.data[i];
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator*(const U &rhs) const {
  Matrix<T, Rows, Cols> res(*this);
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] *= rhs;
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator/(const U &rhs) const {
  Matrix<T, Rows, Cols> res(*this);
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] /= rhs;
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator+(const U &rhs) const {
  Matrix<T, Rows, Cols> res(*this);
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] += rhs;
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator-(const U &rhs) const {
  Matrix<T, Rows, Cols> res(*this);
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] -= rhs;
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
T Matrix<T, Rows, Cols>::dot(const Matrix<T, Rows, Cols> &rhs) const {
  if (Cols != 1) {
    throw std::logic_error("only vectors support dot product.");
  }
  T res(0);
  for (int i = 0; i < this->data.size(); i++) {
    res += (*this)(i) * rhs(i);
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
double Matrix<T, Rows, Cols>::norm() const {
  double res = 0.;
  for (int i = 0; i < width; i++) {
    double columnNorm = 0.;
    for (int j = 0; j < height; j++) {
      columnNorm += (*this)(j, i) * (*this)(j, i);
    }
    columnNorm = std::sqrt(columnNorm);
    res += columnNorm;
  }
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::cross(const Matrix &rhs) const {
  if (Rows != 3 || Cols != 1) {
    throw std::logic_error("only 3d vectors support cross product.");
  }
  Matrix<T, Rows, Cols> res;
  res(0) = (*this)(1) * rhs(2) - (*this)(2) * rhs(1);
  res(1) = (*this)(2) * rhs(0) - (*this)(0) * rhs(2);
  res(2) = (*this)(0) * rhs(1) - (*this)(1) * rhs(0);
  return res;
}

template<typename T, unsigned long Rows, unsigned long Cols>
T &Matrix<T, Rows, Cols>::operator()(int i) {
  if (Cols != 1) {
    throw std::logic_error("use both row and col for matrix indexing.");
  }
  return (*this)(i, 0);
}

template<typename T, unsigned long Rows, unsigned long Cols>
const T &Matrix<T, Rows, Cols>::operator()(int i) const {
  if (Cols != 1) {
    throw std::logic_error("use both row and col for matrix indexing.");
  }
  return (*this)(i, 0);
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::normalize() {
  *this = static_cast<const Matrix<T, Rows, Cols> *>(this)->normalize();
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator/=(const U &rhs) {
  *this = *this / rhs;
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator*=(const U &rhs) {
  *this = *this * rhs;
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator+=(const U &rhs) {
  *this = *this + rhs;
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
template<typename U>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator-=(const U &rhs) {
  *this = *this - rhs;
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator+=(const Matrix<T, Rows, Cols> &rhs) {
  *this = *this + rhs;
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::operator-=(const Matrix<T, Rows, Cols> &rhs) {
  *this = *this - rhs;
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols>::Matrix(std::initializer_list<T> initializer) : width(Cols), height(Rows) {
  if (initializer.size() != Rows * Cols) {
    throw std::logic_error("wrong initializer list size.");
  }
  data = std::vector<T>(initializer);
}

template<typename T, unsigned long Rows, unsigned long Cols>
Matrix<T, Rows, Cols> &Matrix<T, Rows, Cols>::resize(unsigned long rows, unsigned long cols) {
  if (Rows || Cols) {
    throw std::logic_error("fixed sized matrices cannot be resized.");
  }
  height = rows;
  width = cols;
  data.resize(height * width);
  return *this;
}

template<typename T, unsigned long Rows, unsigned long Cols>
T *Matrix<T, Rows, Cols>::getRawData() {
  return data.data();
}

template<typename T, unsigned long Rows, unsigned long Cols>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::normalize() const {
  if (this->norm() == 1.) {
    return *this;
  }
  return *this / this->norm();
}

template<typename T, unsigned long Rows, unsigned long Cols>
const Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::cwiseProduct(const Matrix<T, Rows, Cols> &rhs) const {
  if (width != rhs.width || height != rhs.height) {
    throw std::logic_error("wrong matrix sizes.");
  }
  auto res = *this;
  for (int i = 0; i < res.data.size(); i++) {
    res.data[i] *= rhs.data[i];
  }
  return res;
}

using Matrix2f = Matrix<float, 2, 2>;
using Matrix2d = Matrix<double, 2, 2>;
using Vector3d = Matrix<double, 3, 1>;
using Vector3f = Matrix<float, 3, 1>;
using Vector3uch = Matrix<unsigned char, 3, 1>;
#endif //PROG03_INLINEBOOL_MATRIX_H
