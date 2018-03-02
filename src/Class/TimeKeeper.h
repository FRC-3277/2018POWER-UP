#ifndef SRC_TIMEKEEPER_H_
#define SRC_TIMEKEEPER_H_

#include <chrono>

namespace Kronos
{
	class TimeKeeper
	{
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> TimerBegin;
			std::chrono::time_point<std::chrono::high_resolution_clock> TimerCurrent;
		public:
			TimeKeeper();
			virtual ~TimeKeeper();
			// Time elapsed is in seconds
			double GetElapsedTime();
			void ResetClockStart();
	};
} /* namespace Kronos */
#endif /* SRC_TIMEKEEPER_H_ */
