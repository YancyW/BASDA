#include "Test_CPPIterTools.h" 
using iter::product;
void Test_Cppitertools(){
	std::vector<int> v1{1,2,3};
	std::vector<int> v2{7,8};
	std::vector<std::string> v3{"the","cat"};
	std::vector<std::string> v4{"hi","what's","up","dude"};
	for (auto&& [a, b, c, d] : product(v1,v2,v3,v4)) {
		std::cout << a << ", " << b << ", " << c << ", " << d << '\n';
	}
}
