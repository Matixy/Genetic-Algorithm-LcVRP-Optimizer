//
// Created by Share on 17.01.2026.
//

#include "CGeneticAlgorithm.h"

#include "../errors/CArgumentOutOfBoundError.h"
#include "../utils/CArrayUtils.h"
#include "../utils/CRandomGeneratorUtil.h"
#include "individual/CIndividual.h"
#include "individual/crossStrategy/COnePointCross.h"
#include "individual/mutationStrategy/CMutationSwap.h"

#include <chrono>
#include <iostream>

const int CGeneticAlgorithm::DEFAULT_POP_SIZE = 20;
const double CGeneticAlgorithm::DEFAULT_CROSS_PROBABILITY = 0.6;
const double CGeneticAlgorithm::DEFAULT_MUT_PROBABILITY = -1.0;
const int CGeneticAlgorithm::DEFAULT_MAX_TIME = 10;
const int CGeneticAlgorithm::DEFAULT_TORUNAMENT_SIZE = 2;

static const double DISTANCE_VALUE_ERROR = -1.0;

static const std::string PROBLEM_SIZE_ERROR = "Invalid problem size in evaluator";
static const std::string POPULATION_EMPTY_ERROR = "Population is empty";

// metody

CResult<void, CError> CGeneticAlgorithm::vInitialize(CEvaluator& cEvaluator) {
  this->pcEvaluator = &cEvaluator; // ustawienie ewaluatora

  vPopulation.clear();
  vPopulation.reserve(iPopSize);

  bestIndividual = CIndividual();

  int iGenotypeSize = cEvaluator.getGenotypeSize();
  int iNumberOfTrucks = cEvaluator.getNumberOfTrucks();

  if (iGenotypeSize <= 0 || iNumberOfTrucks <= 0) {
    return CResult<void, CError>::cFail(new CArgumentOutOfBoundError(PROBLEM_SIZE_ERROR));
  }

  // jezeli uzytkownik nie zmienil prawd. mutacji albo zmienil na niepoprawna ustaw domyslna 1/m
  if (dMutProb == DEFAULT_MUT_PROBABILITY) {
    setMutationProbability((double)1/iGenotypeSize);
  }

  // generacja losowej populacji
  for (int i = 0; i < iPopSize; i++) {
    CIndividual individual(iGenotypeSize, iNumberOfTrucks);
    individual.dEvaluate(*pcEvaluator);

    vUpdateBestIndividual(individual);

    vPopulation.push_back(std::move(individual)); // ms - przenoszenie obiektu ktory i tak zaraz zniknie
  }

  return CResult<void, CError>::cOk();
}

CResult<void, CError> CGeneticAlgorithm::vRun() {
  // zabezpieczenie przed pusta populacja
  if (vPopulation.empty()) {
    return CResult<void, CError>::cFail(new CArgumentOutOfBoundError(POPULATION_EMPTY_ERROR));
  }

  int iNumberOfTrucks = pcEvaluator->getNumberOfTrucks();

  // start zegara
  using namespace std::chrono;
  high_resolution_clock::time_point startTime = high_resolution_clock::now();

  high_resolution_clock::time_point currentTime = high_resolution_clock::now();
  duration<double> elapsedTime = duration_cast<duration<double>>(currentTime - startTime);

  while (elapsedTime.count() < iMaxTime) {
    // sprawdzenie czas
    currentTime = high_resolution_clock::now();
    elapsedTime = duration_cast<duration<double>>(currentTime - startTime);


    // przygotowanie wektora nowej populacji
    std::vector<CIndividual> vNewPopulation;
    vNewPopulation.reserve(iPopSize);

    while (vNewPopulation.size() < iPopSize) {
      // STWORZENIE DZIECI (SELECKJIA I KRZYZOWANIE)
      std::pair<CIndividual, CIndividual> pChildren = pCreateChildren();

      CIndividual& child1 = pChildren.first;
      CIndividual& child2 = pChildren.second;

      // MUTACJA
      child1.vMutate(dMutProb, iNumberOfTrucks, pcMutationStrategy);
      child2.vMutate(dMutProb, iNumberOfTrucks, pcMutationStrategy);

      //OCENA
      if (!child1.getIsEvaluated()) child1.dEvaluate(*pcEvaluator);
      if (!child2.getIsEvaluated()) child2.dEvaluate(*pcEvaluator);

      // DODANIE DO NOWEJ POPULACJI I ZAKTUALZIOWANIE NAJLEPSZEGO OSOBNIKA
      vUpdateBestIndividual(child1);
      vUpdateBestIndividual(child2);
      vNewPopulation.push_back(std::move(child1));
      vNewPopulation.push_back(std::move(child2));
    }

    // WYMIANA POKOLEŃ
    vPopulation.swap(vNewPopulation);
  }

  return CResult<void, CError>::cOk();
}

double CGeneticAlgorithm::dGetDistance() const {
  if (bestIndividual.getFitness() == 0.0 || pcEvaluator == NULL) {
    return DISTANCE_VALUE_ERROR;
  }

  return bestIndividual.getFitness();
}

const std::vector<int>& CGeneticAlgorithm::vGetBestGenotype() const {
  if (bestIndividual.getFitness() != 0.0) {
    return bestIndividual.getGenotype();
  }

  static std::vector<int> empty;
  return empty;
}

void CGeneticAlgorithm::vInit(int iPopSize, double dCrossProb, double dMutProb, int iTime, IMutationStrategy *pcMutationStrategy, ICrossStrategy *pcCrossStrategy) {
  setMutationStrategy(pcMutationStrategy);
  setCrossStrategy(pcCrossStrategy);
  setPopSize(iPopSize);
  setCrossProbability(dCrossProb);
  setMutationProbability(dMutProb);
  setMaxTime(iTime);
  setEvaluator(NULL);
}

void CGeneticAlgorithm::vClear() {
  if (pcMutationStrategy != NULL) {
    delete pcMutationStrategy;
  }
  if (pcCrossStrategy != NULL) {
    delete pcCrossStrategy;
  }
}

void CGeneticAlgorithm::vUpdateBestIndividual(CIndividual& individual) {
  if (bestIndividual.getFitness() == 0.0 || individual.getFitness() < bestIndividual.getFitness()) {
    bestIndividual = individual;
  }
}

CIndividual& CGeneticAlgorithm::tournamentSelection(int iTournamentSize) {
  CIndividual* pcWinner = &vPopulation.at(CRandomGeneratorUtil::iRandomFromRange(0, vPopulation.size() - 1)); // wylosowanie pierwszego kandytata

  // rozegraj turniej- wybierz najlepszego osobnika
  for (int i = 0; i < iTournamentSize - 1; i++) {
    CIndividual* pcParticipant = &vPopulation.at(CRandomGeneratorUtil::iRandomFromRange(0, vPopulation.size() - 1));

    if (pcParticipant->getFitness() < pcWinner->getFitness()) {
      pcWinner = pcParticipant;
    }
  }

  return *pcWinner; // zwroc wygranego
}

std::pair<CIndividual, CIndividual> CGeneticAlgorithm::pCreateChildren() {
  // SELEKCJA
  CIndividual& parent1 = tournamentSelection(DEFAULT_TORUNAMENT_SIZE);
  CIndividual& parent2 = tournamentSelection(DEFAULT_TORUNAMENT_SIZE);

  // KRZYŻOWANIE
  std::pair<CIndividual, CIndividual> pChildren = parent1.pCross(parent2, pcCrossStrategy, dCrossProb);
  CIndividual pcChild1 = pChildren.first;
  CIndividual pcChild2 = pChildren.second;

  return std::make_pair(pcChild1, pcChild2);
}

// konstruktory

CGeneticAlgorithm::CGeneticAlgorithm() {
  vInit(DEFAULT_POP_SIZE, DEFAULT_CROSS_PROBABILITY, DEFAULT_MUT_PROBABILITY, DEFAULT_MAX_TIME);
}

CGeneticAlgorithm::CGeneticAlgorithm(int iPopSize, double dCrossProb, double dMutProb, int iTime, IMutationStrategy* pcMutationStrategy, ICrossStrategy* pcCrossStrategy) {
  vInit(iPopSize, dCrossProb, dMutProb, iTime, pcMutationStrategy, pcCrossStrategy);
}

// destruktor

CGeneticAlgorithm::~CGeneticAlgorithm() {
  vClear();
}

// gettery i settery

void CGeneticAlgorithm::setPopSize(int iPopSize) {
  if (iPopSize <= 0) {
    this->iPopSize = DEFAULT_POP_SIZE;
  } else if (iPopSize % 2 == 1) {
    this->iPopSize = iPopSize + 1;
  } else {
    this->iPopSize = iPopSize;
  }
}
int CGeneticAlgorithm::getPopSize() const {
  return iPopSize;
}

void CGeneticAlgorithm::setCrossProbability(double dCrossProb) {
  if (dCrossProb < 0.0 || dCrossProb > 1.0) {
    this->dCrossProb = DEFAULT_CROSS_PROBABILITY;
  } else {
    this->dCrossProb = dCrossProb;
  }
}
double CGeneticAlgorithm::getCrossProbability() const {
  return dCrossProb;
}

void CGeneticAlgorithm::setMutationProbability(double dMutProb) {
  if (dMutProb < 0.0 || dMutProb > 1.0) {
    this->dMutProb = DEFAULT_MUT_PROBABILITY;
  } else {
    this->dMutProb = dMutProb;
  }
}
double CGeneticAlgorithm::getMutationProbability() const {
  return dMutProb;
}

void CGeneticAlgorithm::setMaxTime(int iMaxTime) {
  if (iMaxTime <= 0 ) {
    this->iMaxTime = DEFAULT_MAX_TIME;
  } else {
    this->iMaxTime = iMaxTime;
  }
}
int CGeneticAlgorithm::getMaxTime() const {
  return iMaxTime;
}

void CGeneticAlgorithm::setMutationStrategy(IMutationStrategy* pcMutationStrategy) {
  if (pcMutationStrategy == NULL) {
    this->pcMutationStrategy = new CMutationSwap();
  } else {
    this->pcMutationStrategy = pcMutationStrategy;
  }
}

void CGeneticAlgorithm::setCrossStrategy(ICrossStrategy* pcCrossStrategy) {
  if (pcCrossStrategy == NULL) {
    this->pcCrossStrategy = new COnePointCross();
  } else {
    this->pcCrossStrategy = pcCrossStrategy;
  }
}

void CGeneticAlgorithm::setEvaluator(CEvaluator* pcEvaluator) {
  this->pcEvaluator = pcEvaluator;
}

// toString
std::string CGeneticAlgorithm::toString() {
  std::stringstream ss;

  ss << "Parameters:\n"
    << "Pop=" << iPopSize
    << "\nCross=" << dCrossProb
    << "\nMut=" << dMutProb
    << "\nTime=" << iMaxTime << "s"
    << "\nBest route length=" << dGetDistance()
    << "\nBest route= " << CArrayUtils::sVectorToString(&vGetBestGenotype());
  return ss.str();
}
