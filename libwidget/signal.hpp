#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include "slot.hpp"

namespace libwidget {

template <typename ...Args>
class Signal
{
	public:
		typedef void (*FuncPtr)(Args ...args);

		void connect(FuncPtr func) { listeners.push_back(func); };
		void connect(_BaseSlot<Args...> *s) { slots.push_back(s); };
		void operator()(Args ...args)
		{
			for(int i = 0; i < listeners.size(); i++)
				listeners[i](args...);
			for(int i = 0; i < slots.size(); i++)
				(*slots[i])(args...);
		};

	private:
		std::vector<FuncPtr> listeners;
		std::vector<_BaseSlot<Args...>*> slots;
};

}

#endif // SIGNAL_H
