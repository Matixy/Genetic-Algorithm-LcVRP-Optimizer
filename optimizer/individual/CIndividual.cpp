//
// Created by Share on 16.01.2026.
//

#include "CIndividual.h"

#include "../../utils/CRandomGeneratorUtil.h"

// metody

void CIndividual::vMutate(double dMutProb, int iNumTrucks, IMutationStrategy *pcMutationStrategy) {
  // zabezpieczenie przed nie podaniem strategi
  if (pcMutationStrategy) {
    pcMutationStrategy->vMutate(vGenotype, iNumTrucks, dMutProb);

    setIsEvaluated(false); // ustawienie po mutacji nieobliczonego fitnessu
  }
}

std::pair<CIndividual, CIndividual> CIndividual::pCross(const CIndividual& cOther, ICrossStrategy *pcCrossStrategy, double dMutProb) {
  // zabezpieczenie przed nie podaniem strategi
  if (pcCrossStrategy) {
    std::pair<std::vector<int>, std::vector<int>> pChildrenGenotypes = pcCrossStrategy->pCross(vGenotype, cOther.vGenotype, dMutProb);

    return std::make_pair(CIndividual(pChildrenGenotypes.first), CIndividual(pChildrenGenotypes.second));
  }

  return std::make_pair(CIndividual(), CIndividual()); // blad- zwrocenie pustych obiektow
}

double CIndividual::dEvaluate(CEvaluator& cEvaluator) {
  if (!bIsEvaluated) {
    setFitness(cEvaluator.dEvaluate(this));
    setIsEvaluated(true);
  }

  return dFitness;
}

// operatory

CIndividual &CIndividual::operator=(const CIndividual &pcOther) {
  // zabezpieczenie przed pisaniem samego siebie
  if (this == &pcOther) {
    return *this;
  }

  vCopy(pcOther);

  return *this;
}

// konstruktory

CIndividual::CIndividual() {
  dFitness = 0.0;
  bIsEvaluated = false;
}

CIndividual::CIndividual(int iGenotypeSize, int iNumTrucks) {
  vGenotype.reserve(iGenotypeSize);
  for (int i = 0; i < iGenotypeSize; i++) {
    vGenotype.push_back(CRandomGeneratorUtil::iRandomFromRange(0, iNumTrucks - 1));
  }

  setFitness(0.0);
  setIsEvaluated(false);
}

CIndividual::CIndividual(const std::vector<int>& vGenotype) {
  setGenotype(vGenotype);
  setFitness(0.0);
  setIsEvaluated(false);
}

CIndividual::CIndividual(const CIndividual& pcOther) {
  vCopy(pcOther);
}

CIndividual::CIndividual(CIndividual&& pcOther) {
  vGenotype = std::move(pcOther.vGenotype);
  dFitness = pcOther.dFitness;
  bIsEvaluated = pcOther.bIsEvaluated;
}

void CIndividual::vCopy(const CIndividual& pcOther) {
  vGenotype = pcOther.vGenotype;
  dFitness = pcOther.dFitness;
  bIsEvaluated = pcOther.bIsEvaluated;
}

// gettery i settery

const std::vector<int>& CIndividual::getGenotype() const {
  return vGenotype;
}
void CIndividual::setGenotype(const std::vector<int>& vGenotype) {
  this->vGenotype = vGenotype;
}

double CIndividual::getFitness() const {
  return dFitness;
}
void CIndividual::setFitness(double dFitness) {
  this->dFitness = dFitness;
}

bool CIndividual::getIsEvaluated() const {
  return bIsEvaluated;
}
void CIndividual::setIsEvaluated(bool bIsEvaluated) {
  this->bIsEvaluated = bIsEvaluated;
}
