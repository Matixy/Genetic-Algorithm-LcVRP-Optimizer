//
// Created by Share on 17.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CONEPOINTCROSS_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CONEPOINTCROSS_H
#include "ICrossStrategy.h"

class COnePointCross : public ICrossStrategy {
  public:
    std::pair<std::vector<int>, std::vector<int>> pCross(const std::vector<int> &vParent1, const std::vector<int> &vParent2, double dCrossProb) override;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CONEPOINTCROSS_H
