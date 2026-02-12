//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CFIELDNOTFOUNDINFILEERROR_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CFIELDNOTFOUNDINFILEERROR_H
#include "CError/CError.h"

#include <string>

class CFieldNotFoundInFileError : public CError {
  public:
    CFieldNotFoundInFileError(const std::string& sDescription);

  private:
    const static std::string ERROR_TYPE;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CFIELDNOTFOUNDINFILEERROR_H
