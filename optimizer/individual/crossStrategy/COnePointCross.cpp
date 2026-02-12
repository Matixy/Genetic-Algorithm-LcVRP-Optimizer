//
// Created by Share on 17.01.2026.
//

#include "COnePointCross.h"

#include "../../../utils/CRandomGeneratorUtil.h"

std::pair<std::vector<int>, std::vector<int>> COnePointCross::pCross(const std::vector<int> &vParent1, const std::vector<int> &vParent2, double dCrossProb) {
  if (CRandomGeneratorUtil::dRandomProb() < dCrossProb) {
    int iCrossPoint = CRandomGeneratorUtil::iRandomFromRange(1, vParent1.size() - 1);

    std::vector<int> vChild1 = vParent1;
    std::vector<int> vChild2 = vParent2;

    // przeciecie koncow genotypu
    for (int i = iCrossPoint; i < vParent1.size(); i++) {
      vChild1.at(i) = vParent2.at(i);
      vChild2.at(i) = vParent1.at(i);
    }

    return std::make_pair(vChild1, vChild2); // zwrocenie potomkow
  }

  return std::make_pair(vParent1, vParent2);
};