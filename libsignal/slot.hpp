#ifndef SLOT_H
#define SLOT_H

#define _CALL_MEMBER_FN(object,ptrToMember) ((object).*(ptrToMember))

namespace libsignal {

template <typename ...Args>
class _BaseSlot
{
	public:
		virtual void operator()(Args ...args) = 0;
};

template <typename ...Args>
class FunctionSlot : public _BaseSlot<Args...>
{
	typedef void (*Function)(Args ...args);
	public:
		FunctionSlot(Function f) : f(f) { };
		virtual void operator()(Args ...args) { f(args...); };

	private:
		Function f;
};

template <typename T, typename ...Args>
class MethodSlot : public _BaseSlot<Args...>
{
	typedef void (T::*Method)(Args ...args);

	public:
		MethodSlot(T *obj, Method method) : obj(obj), method(method) { };
		void operator()(Args ...args) { _CALL_MEMBER_FN(*obj, method)(args...); };

	private:
		T *obj;
		Method method;
};

}

#endif // SLOT_H
