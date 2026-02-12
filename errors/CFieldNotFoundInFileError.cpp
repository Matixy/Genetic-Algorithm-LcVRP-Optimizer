//
// Created by Share on 16.01.2026.
//

#include "CFieldNotFoundInFileError.h"

const std::string CFieldNotFoundInFileError::ERROR_TYPE = "CFieldNotFoundInFileError";

CFieldNotFoundInFileError::CFieldNotFoundInFileError(const std::string& sDescription) : CError(sDescription) {
  setSErrorType(ERROR_TYPE);
}