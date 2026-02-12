//
// Created by Share on 17.01.2026.
//

#ifndef MIN_PROJEKT_MATEUSZ_ZADROZNY_CGENETICALGORITHM_H
#define MIN_PROJEKT_MATEUSZ_ZADROZNY_CGENETICALGORITHM_H
#pragma once
#include "CEvaluator.h"
#include "individual/crossStrategy/ICrossStrategy.h"
#include "individual/mutationStrategy/IMutationStrategy.h"
#include "individual/CIndividual.h"

class CGeneticAlgorithm {
public:
  // metody
  CResult<void, CError> vInitialize(CEvaluator &cEvaluator);
  CResult<void, CError> vRun();

  double dGetDistance() const;
  const std::vector<int>& vGetBestGenotype() const;

  // konstruktory
  CGeneticAlgorithm();
  CGeneticAlgorithm(int iPopSize, double dCrossProb, double dMutProb, int iTime, IMutationStrategy* pcMutationStrategy = NULL, ICrossStrategy* pcCrossStrategy = NULL);

  // destruktor
  ~CGeneticAlgorithm();

  // settery i gettery
  void setPopSize(int iPopSize);
  int getPopSize() const;

  void setCrossProbability(double dCrossProb);
  double getCrossProbability() const;

  void setMutationProbability(double dMutProb);
  double getMutationProbability() const;

  void setMaxTime(int iMaxTime);
  int getMaxTime() const;

  void setMutationStrategy(IMutationStrategy* pcMutationStrategy);

  void setCrossStrategy(ICrossStrategy* pcCrossStrategy);

  void setEvaluator(CEvaluator* pcEvaluator);

  // toString()
  std::string toString();

private:
  // metody
  void vInit(int iPopSize, double dCrossProb, double dMutProb, int iTime, IMutationStrategy* pcMutationStrategy = NULL, ICrossStrategy* pcCrossStrategy = NULL);
  void vClear();

  void vUpdateBestIndividual(CIndividual& individual);

  CIndividual& tournamentSelection(int iTournamentSize);

  std::pair<CIndividual, CIndividual> pCreateChildren();

  // pola statyczne
  static const int DEFAULT_POP_SIZE;
  static const double DEFAULT_CROSS_PROBABILITY;
  static const double DEFAULT_MUT_PROBABILITY;
  static const int DEFAULT_MAX_TIME;
  static const int DEFAULT_TORUNAMENT_SIZE;

  static const IMutationStrategy* DEFAULT_MUTATION_STRATEGY;
  static const ICrossStrategy* DEFAULT_CROSS_PROBABILITY_STRATEGY;

  // pola
  int iPopSize;
  double dCrossProb;
  double dMutProb;
  int iMaxTime;

  std::vector<CIndividual> vPopulation;
  CIndividual bestIndividual;
  CEvaluator* pcEvaluator;

  // startegie
  IMutationStrategy* pcMutationStrategy;
  ICrossStrategy* pcCrossStrategy;
};

#endif // MIN_PROJEKT_MATEUSZ_ZADROZNY_CGENETICALGORITHM_H
