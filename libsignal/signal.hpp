#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include "slot.hpp"

namespace libsignal {

/**
 * @brief Macro that creates signals and everything it needs.
 *
 * @warning @b only use this macro at the very @b end of your class.
 */
#define CREATE_SIGNAL(name, conName, args...) \
	private: \
		Signal<args> name; \
	public: \
		void conName(Signal<args>::Slot listener) { name.connect(listener); };

template <typename ...Args>
class Signal
{
	public:
		typedef _BaseSlot<Args...>* Slot;
		~Signal() { for(int i = 0; i < slots.size(); i++) delete slots[i]; };

		void connect(Slot s) { slots.push_back(s); };
		void operator()(Args ...args)
		{
			for(int i = 0; i < slots.size(); i++)
				(*slots[i])(args...);
		};

	private:
		std::vector<Slot> slots;
};

template <typename T, typename ...Args>
typename Signal<Args...>::Slot bind(T *obj, void (T::*method)(Args ...args))
{
	return new MethodSlot<T, Args...>(obj, method);
}

template <typename ...Args>
typename Signal<Args...>::Slot bind(void (*f)(Args ...args))
{
	return new FunctionSlot<Args...>(f);
}

}

#endif // SIGNAL_H
