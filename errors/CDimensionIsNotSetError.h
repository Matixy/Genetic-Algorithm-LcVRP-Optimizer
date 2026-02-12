//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CDIMENSIONISNOTSETERROR_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CDIMENSIONISNOTSETERROR_H
#include "CError/CError.h"
#pragma once


class CDimensionIsNotSetError : public CError {
public:
  CDimensionIsNotSetError(const std::string& sDescription);

private:
  const static std::string ERROR_TYPE;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CDIMENSIONISNOTSET_H
