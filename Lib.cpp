#include "Lib.h"

double Lib::GetTimeStampNs()
{
	std::chrono::nanoseconds ns =
		duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
	return ns.count() / 1000000000.0;
}

double Lib::GetTimeStamp()
{
	std::chrono::seconds sd =
		duration_cast<std::chrono::seconds>(system_clock::now().time_since_epoch());
	return sd.count();
}
