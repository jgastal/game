#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace libwidget {

template <typename ...Args>
class Signal
{
	public:
		typedef void (*FuncPtr)(Args ...args);

		void connect(FuncPtr func) { listeners.push_back(func); };
		void operator()(Args ...args) { for(int i = 0; i < listeners.size(); i++) listeners[i](args...); };

	private:
		std::vector<FuncPtr> listeners;
};

}

#endif // SIGNAL_H
