#include "Ftest.h"
void Test(){
	ShowMessage(2, "Please enter which function you want to test : ");
	ShowMessage(3, "1 test_tuple");
	int i;
	std::cin << i ;
	switch (i){
	case 1: test_tuple();
	default:
			ShowMessage(2,"wrong input number!");
	}
	return;
}
