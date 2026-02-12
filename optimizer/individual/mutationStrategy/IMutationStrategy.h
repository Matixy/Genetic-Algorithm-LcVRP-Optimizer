//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_IMUTATIONSTRATEGY_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_IMUTATIONSTRATEGY_H
#pragma once
#include <vector>

class IMutationStrategy {
  public:
    virtual ~IMutationStrategy() {};
    virtual void vMutate(std::vector<int>& vGenotype, int iNumTrucks, double dMutProb) = 0;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_IMUTATIONSTRATEGY_H
