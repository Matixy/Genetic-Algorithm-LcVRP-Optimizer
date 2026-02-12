//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_ICROSSSTRATEGY_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_ICROSSSTRATEGY_H
#pragma once
#include <vector>

class ICrossStrategy {
  public:
    virtual ~ICrossStrategy() {};
    virtual std::pair<std::vector<int>, std::vector<int>> pCross(const std::vector<int>& vParent1, const std::vector<int>& vParent2, double dCrossProb) = 0;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_ICROSSSTRATEGY_H
