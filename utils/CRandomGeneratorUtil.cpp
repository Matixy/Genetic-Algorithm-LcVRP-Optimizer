//
// Created by Share on 16.01.2026.
//

#include "CRandomGeneratorUtil.h"

#include <random>

// inicjacja generatora z ziarnem

std::random_device CRandomGeneratorUtil::sd;
std::mt19937 CRandomGeneratorUtil::gen(sd());

int CRandomGeneratorUtil::iRandomFromRange(int iMin, int iMax) {
  std::uniform_int_distribution<int> iNum(iMin, iMax);
  return iNum(gen);
}

double CRandomGeneratorUtil::dRandomProb() {
  static std::uniform_real_distribution<double> dis(0.0, 1.0);
  return dis(gen);
}
