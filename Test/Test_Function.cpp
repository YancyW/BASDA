#include "Test_Function.h"
void Test_Function(){
	ShowMessage(2, "Please enter which function you want to test : ");
	ShowMessage(3, "1 test_tuple");
	ShowMessage(3, "2 test cpp_iter_tools: product");
	ShowMessage(2, "Your input is ");
	int i;
	std::cin >> i ;
	switch (i){
	case 1: Test_Tuple();break;
	case 2: Test_Cppitertools();break;
	default:
			ShowMessage(2,"wrong input number!");
			exit(0);
	}
	return;
}
