#include "Test_Function.h"
void Test_Function(){
	ShowMessage(2, "Please enter which function you want to test : ");
	ShowMessage(3, "1 test_tuple");
	int i;
	std::cin >> i ;
	switch (i){
	case 1: Test_Tuple();
	default:
			ShowMessage(2,"wrong input number!");
	}
	return;
}
