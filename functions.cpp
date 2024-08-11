#include "header.h"

void display_slots()
{
	FILE* fptr = fopen("data.txt","r");
	fseek(fptr,0,SEEK_SET);
	if(!fptr)
	{
		cout << "Unable to open file " << endl;
	}
	else
	{
		char ch;
		for(int i = 1;i<=10;i++)
		{
			cout << "Slot " << i;
			fread(&ch,1,1,fptr);
			if( ch == '0')
			{
				cout << "	Available " << endl;
			}
			else
			{
				cout << "	Occupied " << endl;
			}
		}
	}
	fclose(fptr);

}
void park_car()
{
	int park_flag = 0;
	char ch;
	int i;
	char id[30],temp[30];
	FILE* fptr = fopen("data.txt","r+");
	fseek(fptr,0,SEEK_SET);
	FILE* password = fopen("password_file.txt","r+");
	fseek(password,0,SEEK_SET);
	for( i = 0;i<10;i++)
	{
		fread(&ch,1,1,fptr);
		if(ch == '0')
		{
			cout << "Please set a 4 digit password: " ;
			getchar();
			scanf("%[^\n]",id);
			if(strlen(id) == 4)
			{
				fseek(fptr,i,SEEK_SET);
				fputc('1',fptr);
				park_flag = 1;
				fprintf(password,"%s\n",id);

			}
			else
			{
				cout << "---------------------------------------" << endl;
				cout << "Please enter ID of 4 characters " << endl;
				cout << "---------------------------------------" << endl;
			}
			break;
		}
		else
		{
			fscanf(password,"%[^\n]\n",temp);
		}
	}
	if(park_flag)
	{
		cout << "----------------------------------" << endl;
		cout << "Slot " << i+1 << " Occupied for your car " << endl;
		cout << "----------------------------------" << endl;
	}
	else
	{
		cout << "-----------------------------" << endl;
		cout << "Can't book slot for your car" << endl;
		cout << "-----------------------------" << endl;
	}
	fclose(fptr);
	fclose(password);

}

void exit_car()
{
	int slot,exit_flag = 0;
	char id[30],temp[30];
	FILE* data = fopen("data.txt","r+");
	FILE* password = fopen("password_file.txt","r");
	FILE* temp_file = fopen("temp.txt","w");
	cout << "Enter Slot number: " ;
	cin >> slot;
	fseek(data,slot-1,SEEK_SET);
	char ch;
	fread(&ch,1,1,data);
	if(ch == '1')
	{
		cout << "Enter unique ID: ";
		getchar();
		scanf("%[^\n]",id);;
		int line_number = 0;
		while(fscanf(password,"%[^\n]\n",temp) != EOF)
		{
			line_number++;
			if(line_number == slot)
			{
				if( strcmp(id,temp) == 0)
				{
					fseek(data,slot-1,SEEK_SET);
					fputc('0',data);
					fprintf(temp_file,"0000\n");
					cout << "-------------------------" << endl;
					cout << "Successfully exit the car " << endl;
					cout << "-------------------------" << endl;

				}

				else
				{
					cout << "--------------------------------" << endl;
					cout << "Id not matched Please try again " << endl;
					cout << "--------------------------------" << endl;
					break;
				}
			}
			else
			{
				fprintf(temp_file,"%s\n",temp);
			}
		}
	}
	else
	{
		cout << "-------------------------------------------" << endl;
		cout << "Slot not occupied enter correct slot number " << endl;
		cout << "-------------------------------------------" << endl;
	}
	fclose(temp_file);
	fclose(password);
	temp_file = fopen("temp.txt","r");
	password = fopen("password_file.txt","w");
	while( fread(&ch,1,1,temp_file) > 0)
	{
		fwrite(&ch,1,1,password);
	}
	fclose(temp_file);
	fclose(password);
	fclose(data);

}

