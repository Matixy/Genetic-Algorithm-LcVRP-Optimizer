//
// Created by Share on 16.01.2026.
//

#include "CArgumentOutOfBoundError.h"

const std::string CArgumentOutOfBoundError::ERROR_TYPE = "CArgumentOutOfBoundError";

CArgumentOutOfBoundError::CArgumentOutOfBoundError(const std::string& sDescription) : CError(sDescription) {
  setSErrorType(ERROR_TYPE);
}