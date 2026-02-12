//
// Created by Share on 13.01.2026.
//

#include "CConsoleInterface.h"

#include "../files/dataInstance/CDataInstance.h"
#include "../files/fileLoader/CFileLoader.h"
#include "../optimizer/CEvaluator.h"
#include "../optimizer/CGeneticAlgorithm.h"
#include "../optimizer/individual/CIndividual.h"

#include <iostream>
#include <ostream>

static const std::string START_INFO = "=== STARTING OPTIMIZATION ===";
static const std::string FILE_PATH_INFO = "File path: ";
static const std::string DATA_READ_SUCCESS = "DATA LOAD SUCCESS";
static const std::string DATA_READ_ERROR = "DATA READ ERROR";
static const std::string INITIALIZE_ERROR = "INITIALIZE ERROR";
static const std::string INITIALIZE_SUCCESS = "INITIALIZE SUCCESS";
static const std::string RUN_START_ERROR = "RUN START ERROR";
static const std::string RUN_START_SUCCESS = "RUN START SUCCESS";

static const std::string PATH_NAME = "files/data/P-n16-k8.lcvrp";

void CConsoleInterface::vRun() {
  std::cout << START_INFO << std::endl;
  std::cout << FILE_PATH_INFO << PATH_NAME << std::endl;

  CEvaluator cEvaluator;

  CResult<void, CError> loadedDataLog = cEvaluator.bConfigure(PATH_NAME);

  if (loadedDataLog.bIsSuccess()) {
    std::cout << DATA_READ_SUCCESS << std::endl;

    CGeneticAlgorithm cGenAlg = CGeneticAlgorithm(100, -0.8, -0.02, 5);

    CResult<void, CError> initializeLog = cGenAlg.vInitialize(cEvaluator);

    if (initializeLog.bIsSuccess()) {
      std::cout << INITIALIZE_SUCCESS << std::endl;
      CResult<void, CError> runLog = cGenAlg.vRun();

      if (runLog.bIsSuccess()) {
        std::cout << RUN_START_SUCCESS << std::endl;
        std::cout << cGenAlg.toString() << std::endl;
      } else {
        vPrintError(RUN_START_ERROR);
        vPrintError(runLog.vGetErrors());
      }
    } else {
      vPrintError(INITIALIZE_ERROR);
      vPrintError(initializeLog.vGetErrors());
    }

  } else {
    vPrintError(DATA_READ_ERROR);
    vPrintError(loadedDataLog.vGetErrors());
  }

}

CConsoleInterface::CConsoleInterface() {
}

CConsoleInterface::~CConsoleInterface() {
}

void CConsoleInterface::vPrintError(const std::string sError) const {
  std::cerr << sError << std::endl;
}

void CConsoleInterface::vPrintError(const std::vector<CError* > sError) const {
  for (int i = 0; i < sError.size(); i++) {
    vPrintError(sError.at(i)->toString());
  }
}
