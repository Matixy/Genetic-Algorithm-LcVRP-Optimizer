//
// Created by Share on 16.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CINDIVIDUAL_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CINDIVIDUAL_H
#pragma once
#include "../CEvaluator.h"
#include "crossStrategy/ICrossStrategy.h"
#include "mutationStrategy/IMutationStrategy.h"

#include <vector>

class CIndividual {
  public:
    // metody
    void vMutate(double dMutProb, int iNumTrucks, IMutationStrategy* pcMutationStrategy); // mutacja
    std::pair<CIndividual, CIndividual> pCross(const CIndividual& cOther, ICrossStrategy* pcCrossStrategy, double dCrossProb); // krzyzowanie z innym osobnikiem
    double dEvaluate(CEvaluator& cEvaluator); // ocena osobnika

    // operatory
    CIndividual &operator=(const CIndividual& pcOther);

    // konstruktory
    CIndividual(); // domyslny
    CIndividual(int iGenotypeSize, int iNumTrucks); // losowy
    CIndividual(const std::vector<int>& vGenotype); // tworzacy z gotowego genotypu- dla dzieci
    CIndividual(const CIndividual& pcOther); // kopiujacy
    CIndividual(CIndividual&& pcOther); // MS

    // desturktor


    // gettery i settery
    const std::vector<int>& getGenotype() const;
    void setGenotype(const std::vector<int>& vGenotype);

    double getFitness() const;
    void setFitness(double dFitness);

    bool getIsEvaluated() const;
    void setIsEvaluated(bool bIsEvaluated);

  private:
    // metody
    void vCopy(const CIndividual& pcOther);

    // pola
    std::vector<int> vGenotype;
    double dFitness;
    bool bIsEvaluated; // flaga czy przystosowanie jest aktualne (np. po mutacji)
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CINDIVIDUAL_H
