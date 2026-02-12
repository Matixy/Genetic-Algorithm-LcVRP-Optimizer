//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CEVALUATOR_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CEVALUATOR_H
#pragma once
#include "../errors/CError/CError.h"
#include "../files/dataInstance/CDataInstance.h"
#include "../result/CResult.h"

class CIndividual;

class CEvaluator {
  public:
    // metody
    CResult<void, CError> bConfigure(std::string sPathName);
    double dEvaluate(const CIndividual* pcIndividual);

    // konstrutkory
    CEvaluator();

    // destruktor
    ~CEvaluator();

    // gettery i settery
    int getGenotypeSize() const;
    int getNumberOfTrucks() const;
    int dGetDist(int x, int y) const;

  private:
    // metody
    double dCalculateDistance(const Coordinate& c1, const Coordinate& c2);
    void vClear();

    double vReturnToDepot();

    void vCalculateDistanceMatrix();

    void vClearBufforMatrix();

    // pola statyczne
    static const double INVALID_INDIVIDUAL_FITNESS;

    // pola
    CDataInstance* pcData;

    std::vector<std::vector<double> > vDistMatrix;

    std::vector<int> vTruckCurrentPos;
    std::vector<int> vTruckActualCapacity;
    std::vector<double> vTruckDist;
    std::vector<bool> vTruckUsed;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CEVALUATOR_H
