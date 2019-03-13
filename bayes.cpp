#include <iostream>
#include "src/classify.h"

int main(int argc, char const *argv[]){
	cclassify *a = new cclassify(2);
	a->classify("data/class_sample.dat");
	a->find_class("Chinese Chinese Chinese Tokyo Japan");

	delete a;
	return 0;
}