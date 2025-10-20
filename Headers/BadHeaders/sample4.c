// will header.h be included more than once? -> No if it has filegaurds
// Note that multiple inclusions of standard header files like stdio.h 
//will only add the code onece, because there is a file gaurd for each header
#include "header.h"
#include "header.h"

int main(void) {
	test();
	return 0;
}
