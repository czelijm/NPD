#include "TimeMeasure.hpp"
#
double HowMuchTimeWasPassed(clock_t time)
{

	return (static_cast <double>(time)/CLOCKS_PER_SEC);
}
