//
// Created by Share on 16.01.2026.
//

#include "CMutationSwap.h"
#include "../../../utils/CRandomGeneratorUtil.h"

void CMutationSwap::vMutate(std::vector<int>& vGenotype, int iNumTrucks, double dMutProb) {
  for (int i = 0; i < vGenotype.size(); i++) {
    if (CRandomGeneratorUtil::dRandomProb() < dMutProb) {
      vGenotype.at(i) = CRandomGeneratorUtil::iRandomFromRange(0, iNumTrucks-1); // losowanie nowej ciężarówki
    }
  }
}