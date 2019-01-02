#include"Header.h"

using namespace std;


int main()
{
	
	string command;

	do
	{
		cin >> command;
		if (command == "buildIndex")
			buildIndex();
		else if (command == "search")
			search();
		else if (command == "sequentialSearch")
			sequentialSearch();

	} while (command != "exit");

	system("pause");
	return 0;
}