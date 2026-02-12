//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CPERMUTATIONINCOMPLETEERROR_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CPERMUTATIONINCOMPLETEERROR_H
#include "CError/CError.h"
#pragma once


class CPermutationIncompleteError : public CError {
public:
  CPermutationIncompleteError(const std::string& sDescription);

private:
  const static std::string ERROR_TYPE;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CPERMUTATIONINCOMPLETE_H
