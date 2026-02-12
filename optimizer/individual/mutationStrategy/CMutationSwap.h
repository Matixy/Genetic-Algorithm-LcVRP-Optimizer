//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CMUTATIONSWAP_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CMUTATIONSWAP_H
#pragma once
#include "IMutationStrategy.h"

class CMutationSwap : public IMutationStrategy {
  public:
    void vMutate(std::vector<int> &vGenotype, int iNumTrucks, double dMutProb) override;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CMUTATIONSWAP_H
