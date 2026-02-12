//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CRANDOMGENERATORUTIL_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CRANDOMGENERATORUTIL_H
#include <random>

class CRandomGeneratorUtil {
  public:
    // losowanie liczby calkowitej z zakresu [iMin, iMax]
    static int iRandomFromRange(int iMin, int iMax);

    // losowanie double z [0.0, 1.0]
    static double dRandomProb();

  private:
    static std::random_device sd;
    static std::mt19937 gen;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CRANDOMGENERATORUTIL_H
