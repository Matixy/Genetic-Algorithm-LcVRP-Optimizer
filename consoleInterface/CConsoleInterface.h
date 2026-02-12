//
// Created by Share on 13.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CCONSOLEINTERFACE_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CCONSOLEINTERFACE_H
#include "../errors/CError/CError.h"

#include <string>
#include <vector>
#pragma once



class CConsoleInterface {
  public:
    // metody
    void vRun();

    // konstruktor
    CConsoleInterface();

    // destruktor
    ~CConsoleInterface();

    // setttery i gettery

  private:
    // metody
    void vPrintError(const std::string error) const;
    void vPrintError(const std::vector<CError* > error) const;
};


#endif //MIN_PROJEKT_MATEUSZ_ZADROZNY_CCONSOLEINTERFACE_H