#include "Test_Tuple.h" 
void Test_Tuple(){
	auto t1 = std::make_tuple(1, 2, 3); // non-const lvalue
	const auto t2 = std::make_tuple(4, 5, 6); // const lvalue
	for_each(t1, [](auto&& t) {std::cout << std::forward<decltype(t)>(t) << ' '; });
	for_each(t2, [](auto&& t) {std::cout << std::forward<decltype(t)>(t) << ' '; });
	for_each(std::make_tuple(7, 8 ,9), [](auto&& t) {std::cout << std::forward<decltype(t)>(t) << ' '; }); // rvalue
}
