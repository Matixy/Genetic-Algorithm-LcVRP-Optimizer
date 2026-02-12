//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CARGUMENTOUTOFBOUNDERROR_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CARGUMENTOUTOFBOUNDERROR_H
#include "CError/CError.h"
#pragma once

#include <string>

class CArgumentOutOfBoundError : public CError {
  public:
    CArgumentOutOfBoundError(const std::string& sDescription);

  private:
    const static std::string ERROR_TYPE;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CERRORARGUMENTOUTOFBOUNDERROR_H
