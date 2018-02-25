#ifndef SRC_CUSTOMERROR_H_
#define SRC_CUSTOMERROR_H_
#include <exception>
#include <string>

namespace ERR
{
	class CustomError : public std::exception
	{
		public:
			CustomError(const std::string& message);
			virtual ~CustomError();
			virtual const char* what() const throw()
			{
				return message_.c_str();
			}

		private:
			std::string message_;
	};
} /* namespace ERR */
#endif /* SRC_CUSTOMERROR_H_ */
