//
// Created by Share on 13.01.2026.
//

#include "CInvalidVariableFormatError.h"

const std::string CInvalidVariableFormatError::ERROR_TYPE = "CInvalidVariableFormatError";

CInvalidVariableFormatError::CInvalidVariableFormatError(const std::string& sDescription) : CError(sDescription) {
  setSErrorType(ERROR_TYPE);
}
