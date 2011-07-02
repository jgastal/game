#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace libwidget {

class Signal
{
	public:
		typedef void (*FuncPtr)();

		void connect(FuncPtr func);
		void operator()();

	private:
		std::vector<FuncPtr> listeners;
};

}

#endif // SIGNAL_H
