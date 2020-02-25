#include <iostream>// cout | cin
#include <cstdlib>// system
#include <string> // string
#include "TanchiSnake.h"

using namespace std;

int main(void)
{
	TanchiSnake MySnake(520, 520, 10);
	MySnake.start_the_game();
	system("pause");
	return 0;
}
