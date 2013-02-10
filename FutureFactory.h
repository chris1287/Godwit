#ifndef FUTURE_FACTORY_H
#define FUTURE_FACTORY_H

#include <future>
#include <memory>
#include <functional>

template <typename T, typename... Args>
class FutureFactory
{
public:
	typedef std::unique_ptr<T> pT;
	typedef std::future<pT> future_pT;
	typedef std::function<void(pT)> callback_pT;
	
public:
	static pT create_sync(Args... params)
	{
		return pT(new T(params...));
	}
	
	static future_pT create_async_byFuture(Args... params)
	{
		return std::async(std::launch::async, &FutureFactory<T, Args...>::create_sync, params...);
	}
	
	static void create_async_byCallback(callback_pT cb, Args... params)
	{
		std::async(std::launch::async, &FutureFactory<T, Args...>::manage_async_byCallback, cb, params...);
	}

private:
	FutureFactory(){}
	
	static void manage_async_byCallback(callback_pT cb, Args... params)
	{
		auto ptr = FutureFactory<T, Args...>::create_sync(params...);
		cb(std::move(ptr));
	}
};

#endif
