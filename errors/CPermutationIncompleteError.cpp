//
// Created by Share on 16.01.2026.
//

#include "CPermutationIncompleteError.h"

const std::string CPermutationIncompleteError::ERROR_TYPE = "CPermutationIncomplete";

CPermutationIncompleteError::CPermutationIncompleteError(const std::string& sDescription) : CError(sDescription) {
  setSErrorType(ERROR_TYPE);
}