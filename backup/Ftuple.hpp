#pragma once
#ifndef FUNCTION_TUPLE_H
#define FUNCTION_TUPLE_H
#include <iostream>
#include <tuple>


//three for_each to traverse every tuple element
//

//for non-const lvalue reference
	template <unsigned N = 0, class F, class... T>
typename enable_if<N == sizeof...(T), void>::type for_each(std::tuple<T...>&, F&& f)
{
	ShowMessage(2,"non-const lvalue reference end()");// 便于理解，实际什么都不用做
}

	template <unsigned N = 0, class F, class... T>
typename enable_if<N < sizeof...(T), void>::type for_each(std::tuple<T...>& t, F&& f)
{
	f(get<N>(t));
	for_each<N + 1, F, T...>(t, std::forward<F>(f));
}



//for const lvalue reference
	template <unsigned N = 0, class F, class... T>
typename enable_if<N == sizeof...(T), void>::type for_each(const std::tuple<T...>&, F&& f)
{
	ShowMessage(2,"const lvalue reference end()"); // 便于理解，实际什么都不用做
}

	template <unsigned N = 0, class F, class... T>
typename enable_if <N < sizeof...(T), void>::type for_each(const std::tuple<T...>& t, F&& f)
{
	f(get<N>(t));
	for_each<N + 1, F, T...>(t, std::forward<F>(f));
}


//rvalue reference
	template <unsigned N = 0, class F, class... T>
typename enable_if<N == sizeof...(T), void>::type for_each(std::tuple<T...>&&, F&&)
{
	ShowMessage(2,"rvalue reference end()"); // 便于理解，实际什么都不用做
}

	template <unsigned N = 0, class F, class... T>
typename enable_if < N < sizeof...(T), void>::type for_each(std::tuple<T...>&& t, F&& f)
{
	f(get<N>(t));
	for_each<N + 1, F, T...>(std::move(t), std::forward<F>(f));
}

// test function
void test_tuple();
#endif

