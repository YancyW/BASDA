#include "Ftuple.hpp"

void test_tuple(){
	auto t1 = make_tuple(1, 2, 3); // non-const lvalue
	const auto t2 = make_tuple(4, 5, 6); // const lvalue
	for_each(t1, [](auto&& t) {cout << forward<decltype(t)>(t) << ' '; });
	for_each(t2, [](auto&& t) {cout << forward<decltype(t)>(t) << ' '; });
	for_each(make_tuple(7, 8 ,9), [](auto&& t) {cout << forward<decltype(t)>(t) << ' '; }); // rvalue
}
