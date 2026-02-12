//
// Created by mateu on 30.10.2025.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_ARRAYUTILS_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_ARRAYUTILS_H
#pragma once
#include <string>

class CArrayUtils {
  public:
    // metody
    template<typename T>
    static void vClearArray(T* piArray, int iSize);

    template<typename T>
    static void vCopyArray(const T* piCopyFromArray,T* piCopyToArray, int iSize);

    template<typename T>
    static std::string sVectorToString(const std::vector<T>* pVector);
};

#include "CArrayUtils.tpp"


#endif //LISTA_2_ARRAYUTILS_H