#include "header.h"

int main()
{
	display_slots();
	int choice;
	while(1)
	{
		cout << "1.Park a car " << endl;
		cout << "2.Exit a car " << endl;
		cout << "3.Display Slots " << endl;
		cout << "4.Exit from program" << endl;
		cin >> choice;
		switch(choice)
		{
			case 1:
				park_car();
				//display_slots();
				break;
			case 2:
				exit_car();
				break;
			case 3:
				display_slots();
				break;
			case 4:
				return 0;
			default:
				cout << "Please enter a valid option " << endl;
		}

	}
}

