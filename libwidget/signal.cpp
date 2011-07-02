#include "signal.h"

namespace libwidget {

void Signal::connect(FuncPtr func)
{
	listeners.push_back(func);
}

void Signal::operator()()
{
	for(std::vector<FuncPtr>::iterator it = listeners.begin(); it != listeners.end(); it++)
		(*it)();
}

}
