//
// Created by Jiang Kairong on 3/11/18.
//

#ifndef PROG03_INLINEBOOL_IMAGE_H
#define PROG03_INLINEBOOL_IMAGE_H

#include <vector>
#include "Color.h"

//template<typename T>
//class Image {
//  explicit Image(unsigned long width, unsigned long height);
//
//  T *getRawData();
//
//  const T &operator()(int i, int j) const;
//
//  T &operator()(int i, int j);
//
//protected:
//  std::vector<T> data;
//  unsigned long width, height;
//};
//
//template<typename T>
//Image<T>::Image(unsigned long width, unsigned long height) : width(width), height(height){
//  data = std::vector<T>(width * height);
//}
//
//template<typename T>
//T *Image<T>::getRawData() {
//  return data.data();
//}
//
//template<typename T>
//const T &Image<T>::operator()(int i, int j) const {
//  if (i >= height || j >= width || i < 0 || j < 0) {
//    throw std::out_of_range("index out of bounds");
//  }
//  return data[i * width + j];
//}
//
//template<typename T>
//T &Image<T>::operator()(int i, int j) {
//  return const_cast<T &>((*static_cast<const Image<T> *>(this))(i, j));
//}
using Image32f = Matrix<ColorRGB32f>;

using Image8i = Matrix<ColorRGB8i>;

#endif //PROG03_INLINEBOOL_IMAGE_H
