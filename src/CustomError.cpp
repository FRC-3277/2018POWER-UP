#include "CustomError.h"

namespace ERR
{
	CustomError::CustomError(const std::string& message) : message_(message)
	{
	}

	CustomError::~CustomError()
	{
	}
}
/* namespace ERR */
