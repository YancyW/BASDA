#pragma once
#ifndef FUNCTION_TUPLE_H
#define FUNCTION_TUPLE_H
#include <iostream>
#include <tuple>
#include <experimental/tuple>


//three for_each to traverse every tuple element
//

//for non-const lvalue reference
	template <unsigned N = 0, class F, class... T>
typename std::enable_if<N == sizeof...(T), void>::type for_each(std::tuple<T...>&, F&& f)
{
//	ShowMessage(2,"non-const lvalue reference end()");// 便于理解，实际什么都不用做
	ShowMessage(2);// 便于理解，实际什么都不用做
}

	template <unsigned N = 0, class F, class... T>
typename std::enable_if<N < sizeof...(T), void>::type for_each(std::tuple<T...>& t, F&& f)
{
	f(std::get<N>(t));
	for_each<N + 1, F, T...>(t, std::forward<F>(f));
}



//for const lvalue reference
	template <unsigned N = 0, class F, class... T>
typename std::enable_if<N == sizeof...(T), void>::type for_each(const std::tuple<T...>&, F&& f)
{
//	ShowMessage(2,"const lvalue reference end()"); // 便于理解，实际什么都不用做
	ShowMessage(2);// 便于理解，实际什么都不用做
}

	template <unsigned N = 0, class F, class... T>
typename std::enable_if <N < sizeof...(T), void>::type for_each(const std::tuple<T...>& t, F&& f)
{
	f(std::get<N>(t));
	for_each<N + 1, F, T...>(t, std::forward<F>(f));
}


//rvalue reference
	template <unsigned N = 0, class F, class... T>
typename std::enable_if<N == sizeof...(T), void>::type for_each(std::tuple<T...>&&, F&&)
{
//	ShowMessage(2,"rvalue reference end()"); // 便于理解，实际什么都不用做
	ShowMessage(2);// 便于理解，实际什么都不用做
}

	template <unsigned N = 0, class F, class... T>
typename std::enable_if < N < sizeof...(T), void>::type for_each(std::tuple<T...>&& t, F&& f)
{
	f(std::get<N>(t));
	for_each<N + 1, F, T...>(std::move(t), std::forward<F>(f));
}

// test function
template <class Tuple,
   class T = std::decay_t<std::tuple_element_t<0, std::decay_t<Tuple>>>>
std::vector<T> to_vector(Tuple&& tuple)
{
    return std::experimental::apply([](auto&&... elems){
        return std::vector<T>{std::forward<decltype(elems)>(elems)...};
    }, std::forward<Tuple>(tuple));
}
#endif

