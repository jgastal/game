#ifndef SLOT_H
#define SLOT_H

#define _CALL_MEMBER_FN(object,ptrToMember) ((object).*(ptrToMember))

namespace libwidget {

template <typename ...Args>
class _BaseSlot
{
	public:
		virtual void operator()(Args ...args) = 0;
};

template <typename T, typename ...Args>
class Slot : public _BaseSlot<Args...>
{
	typedef void (T::*Method)(Args ...args);

	public:
		Slot(T *obj, Method method) : obj(obj), method(method) { };
		void operator()(Args ...args) { _CALL_MEMBER_FN(*obj, method)(args...); };

	private:
		T *obj;
		Method method;
};

template <typename T, typename ...Args>
Slot<T, Args...>* bind(T *obj, void (T::*method)(Args ...args))
{
	return new Slot<T, Args...>(obj, method);
};

}

#endif // SLOT_H
