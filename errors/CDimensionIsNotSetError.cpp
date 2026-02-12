//
// Created by Share on 16.01.2026.
//

#include "CDimensionIsNotSetError.h"

const std::string CDimensionIsNotSetError::ERROR_TYPE = "CDimensionIsNotSet";

CDimensionIsNotSetError::CDimensionIsNotSetError(const std::string& sDescription) : CError(sDescription) {
  setSErrorType(ERROR_TYPE);
}
