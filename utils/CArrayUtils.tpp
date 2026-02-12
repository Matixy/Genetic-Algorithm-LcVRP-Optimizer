//
// Created by mateu on 30.10.2025.
//

#include "CArrayUtils.h"

#include <sstream>

template <typename T>
void CArrayUtils::vClearArray(T* piArray, int iSize) {
  if (piArray == 0 || iSize <= 0) return;

  for (int i = 0; i < iSize; i++) {
    piArray[i] = 0;
  }
}

template<typename T>
void CArrayUtils::vCopyArray(const T* piCopyFromArray,T* piCopyToArray, int iSize) {
  if (piCopyFromArray == 0 || iSize <= 0) return;

  for (int i = 0; i < iSize; i++) {
    piCopyToArray[i] = piCopyFromArray[i];
  }
}

template <typename T>
std::string CArrayUtils::sVectorToString(const std::vector<T>* pVector) {
  std::stringstream ss;

  ss << "[";
  for (int i = 0; i < pVector->size(); i++) {
    ss << pVector->at(i) << ", ";
  }
  ss << "]";

  return ss.str();
}