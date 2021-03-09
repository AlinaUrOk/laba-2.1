// lab 2_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "lab 2_1.h"
using namespace std;
#pragma warning(disable : 4996)

struct user
{
	char login[50];
	long long pin;
	bool exist = true;
	int id;
}User;

struct ticket
{
	char namestation[50];
	int cost;
	int id;
}Station;

long long Hesh(char* array) {
	const int k = 31, mod = 1e9 + 7;
	long long h = 0, m = 1;
	long size = (sizeof(array)) / sizeof(array[0]);

	for (int i = 0; i < size; i++) {
		int x = (int)(array[i] - 'a' + 1);
		h = (h + m * x) % mod;
		m = (m * k) % mod;
	}
	return h;
}

bool IsNotNewUser(const user& NewUser)
{
	FILE* fp;
	bool isnot = false;
	user ExistUser;
	fp = fopen("users.bin", "rb");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		fread(&ExistUser, sizeof(user), 1, fp);
		if (strcmp(ExistUser.login, NewUser.login) == 0)
		{
			isnot = true;
			fclose(fp);
			return true;
		}
	}
	return false;
}

void ReadUser()
{

	FILE* fp;
	fp = fopen("users.bin", "rb");
	fseek(fp, sizeof(User), SEEK_END);
	long size = ftell(fp);
	fseek(fp, sizeof(User), SEEK_SET);
	int number = size / sizeof(user);
	user* User = new user[number];
	while (!feof(fp))
	{
		/*	fread(&User->login, sizeof(User->login), number, fp);
			fread(&User->pin, sizeof(User->pin), number, fp);
			fread(&User->id, sizeof(User->id), number, fp);
			fread(&User->exist, sizeof(User->exist), number, fp);*/
		fread(User, sizeof(user), number, fp);
		for (int i = 0; i < number; i++)
		{
			cout << "User login " << User[i].login << endl;
			cout << "User password " << User[i].pin << endl;
			cout << "ID: " << User[i].id << endl;
			cout << "Flag of existence: " << User[i].exist << endl;
			cout << endl;
		}

	}
	fclose(fp);
}

void ReadStations()
{
	FILE* f;
	f = fopen("station.bin", "rb");
	fseek(f, sizeof(Station), SEEK_END);
	long size = ftell(f);
	fseek(f, sizeof(Station), SEEK_SET);
	int number = size / sizeof(ticket);
	ticket* Station = new ticket[number];
	while (!feof(f))
	{
		/*fread(&Station->id, sizeof(Station->id), number, f);
		fread(&Station->namestation, sizeof(Station->namestation), number, f);
		fread(&Station->cost, sizeof(Station->cost), number, f);*/
		fread(&Station, sizeof(Station), number, f);
		for (int i = 0; i < number; i++)
		{
			cout << "ID: " << Station[i].id << endl;
			cout << "Name: " << Station[i].namestation << endl;
			cout << "Cost: " << Station[i].cost << endl;
			cout << endl;
		}

	}
	fclose(f);
}

bool IsNotNewStation(const ticket& NewStation)
{
	FILE* f;
	bool isnotnew = false;
	ticket ExistStation;
	f = fopen("station.bin", "rb");
	fseek(f, 0, SEEK_SET);
	while (!feof(f))
	{
		fread(&ExistStation, sizeof(ticket), 1, f);
		if (strcmp(ExistStation.namestation, NewStation.namestation) == 0)
		{
			isnotnew = true;
			fclose(f);
			return true;
		}
	}
	return false;
}

//void DeleteUser()
//{
//	FILE* fp;
//	fp = fopen("users.bin", "ab");
//	int check = 0;
//	user NewUser;
//	cout << "Enter login of the user you want to delete:" << endl;
//	cin >> NewUser.login;
//
//	fseek(fp, 0, SEEK_SET);
//	while (!feof(fp))
//	{
//		/*fread(&NewUser, sizeof(user), 1, fp);*/
//		if (IsNotNewUser(NewUser) == true)
//		{
//			check++;
//			User.exist = false;
//			int size = 0 - sizeof(user);
//			fseek(fp, size, SEEK_CUR);
//			fwrite(&User, sizeof(user), 1, fp);
//			cout << NewUser.login << " was deleted." << endl;
//			fclose(fp);
//			
//		}
//		else
//		{
//			cout << NewUser.login << " not found" << endl;
//		}
//	}
//}

void AdminMenu()
{

	int number;
	cout << "--------------------------------------------" << endl;
	cout << "Enter what you want to do:" << endl;
	cout << "1) Read all users' information" << endl;
	cout << "2) Delete user" << endl;
	cout << "3) Create new station" << endl;
	cout << "4) Read all stations' information" << endl;
	cout << "--------------------------------------------" << endl;
	cin >> number; cout << endl;
	switch (number)
	{
	case 1:
	{
		ReadUser();
		return AdminMenu();

	}
	break;
	case 2:
	{
		FILE* fp;
		fp = fopen("users.bin", "ab");
		int check = 0;
		user NewUser;
		cout << "Enter login of the user you want to delete:" << endl;
		cin >> NewUser.login;

		fseek(fp, 0, SEEK_SET);
		while (!feof(fp))
		{
			/*fread(&NewUser, sizeof(user), 1, fp);*/
			if (IsNotNewUser(NewUser) == true)
			{
				NewUser.exist = false;
				int size = 0 - sizeof(user);
				fseek(fp, size, SEEK_CUR);
				fwrite(&NewUser, sizeof(user), 1, fp);
				cout << NewUser.login << " was deleted." << endl;
				cout << "Flag of existence: " << NewUser.exist << endl;
				fclose(fp);
				return AdminMenu();
			}
			else
			{
				cout << NewUser.login << " not found" << endl;
				return AdminMenu();
			}
		}

	}
    break;
	case 3:
	{
		FILE* f;
		ticket NewStation;
		f = fopen("station.bin", "ab");
		fseek(f, 0, SEEK_SET);
		cout << "Enter name of Station: ";
		cout << endl;
		cin >> NewStation.namestation;
		while (!feof(f))
		{

			if (IsNotNewStation(NewStation) == true)
			{
				cout << "This station is already exist." << endl;
				return AdminMenu();
			}
			else
			{
				cout << "Enter cost of train"; cout << endl;
				cin >> NewStation.cost;
				fwrite(&NewStation, sizeof(NewStation), 1, f);
				cout << "New station " << NewStation.namestation << " was created." << endl;
				fclose(f);
				return AdminMenu();
			}
		}
	}
	break;

	case 4:
	{
		ReadStations();
		return AdminMenu();
	}
	}

	}

void UserMenu()
{
	int number;
	cout << "--------------------------------------------" << endl;
	cout << "Choose: " << endl;
	cout << "1) See all stations" << endl;
	cout << "2) Buying a ticket" << endl;
	cout << "3) Exit" << endl;
	cout << "--------------------------------------------" << endl;
	cin >> number; cout << endl;
	switch (number)
	{
	case 1:
	{
		ReadStations();
		return UserMenu();
	}
	break;
	case 2:
	{
		FILE* f;
		f = fopen("station.bin", "rb");
		fseek(f, sizeof(Station), SEEK_END);
		long size = ftell(f);
		fseek(f, sizeof(Station), SEEK_SET);
		int number = size / sizeof(ticket);
		ticket* Station = new ticket[number];
		int k;
		int choose;
		cout << "Choose station from 0 to " << -1 + number - 2 << endl;
		ReadStations();
		cin >> k;
		int tickets;
		while (!feof(f))
		{
			fread(&Station->namestation, sizeof(Station->namestation), number, f);
			fread(&Station->cost, sizeof(Station->cost), number, f);
			cout << "You choose station " << Station[k].namestation << endl;
			cout << "Are you sure? (1-yes) (2-no)" << endl;
			cin >> choose;
			switch (choose)
			{
			case(1):
			{
				cout << "How many tickets you need?" << endl;
				cin >> tickets;
				cout << "Cost: " << tickets * Station[k].cost << endl;
				cout << "You bought " << tickets << " ticket(s) from Kyiv to " << Station[k].namestation << endl;
				return UserMenu();
			}
			break;
			case 2:
			{
				return UserMenu();
			}
			break;
			}
		}
		fclose(f);
	}
	break;
	case 3:
	{
		cout << "Thanks for your trust in us. Bye!" << endl;
		system("pause");
	}
	break;
	}
}

int main()
{
	cout << "Enter 1 for login or 2 for register" << endl;
	int key;
	cin >> key; cout << endl;

	switch (key)
	{
	case 1:
	{
		user NewUser, ExistUser;
		FILE* fp = fopen("users.bin", "rb");
		fseek(fp, 0, SEEK_SET);
		if ((fp) == NULL)
		{
			cout << "Cannot open file" << endl;
			return NULL;
		}
		cout << "Enter login: "; cout << endl;
		cin >> NewUser.login;
		cout << "Enter parol: "; cout << endl;
		char pass[50];
		cin >> pass;
		NewUser.pin = Hesh(pass);
		cout << "--------------------------------------------" << endl;
		bool IsLogPerson = false;
		while (!feof(fp))
		{
			fread(&ExistUser, sizeof(ExistUser), 1, fp);

			if (IsNotNewUser(NewUser) == true)
			{
				if (ExistUser.pin == NewUser.pin)
				{
					IsLogPerson = true;
				}

			}
			else
			{
				cout << "Uncorrect login! Try again." << endl;
				return main();
			}

		}
		if (IsLogPerson = false)
		{
			cout << "Uncorrect password!" << endl;
			return main();
		}
		else
		{
			char loggin[50] = "kate";
			if (strcmp(NewUser.login, loggin) == 0)
			{
				cout << "Hi admin" << endl;
				AdminMenu();
			}
			else
			{
				cout << "Hey user" << endl;
				UserMenu();
			}
		}
	}
	break;

	case 2:
	{
		FILE* fp;
		char login[50], parol[50];
		user NewUser;
		fp = fopen("users.bin", "ab");
		fseek(fp, 0, SEEK_SET);
		cout << "Enter login: "; cout << endl;
		cin >> NewUser.login;
		cout << "Enter parol: "; cout << endl;
		char pass[50];
		cin >> pass;
		NewUser.pin = Hesh(pass);
		while (!feof(fp))
		{

			if (IsNotNewUser(NewUser) == true)
			{
				cout << "This login is already taken. Try another one." << endl;
				return main();
			}
			else
			{
				fwrite(&NewUser, sizeof(NewUser), 1, fp);
				fclose(fp);
				cout << "You are registed." << endl;
				return main();
			}
		}
	}
	break;
	}
}




/*	FILE* fp;
	user NewUser;
	char login[50];
	fp = fopen("users.bin", "ab");*/
	/*cout << "Enter login of the user you want to change:" << endl;
	cin >> NewUser.login;
	int check = 0;

	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		if (IsNotNewUser(NewUser) == true)
		{
			check++;
			NewUser.exist = false;
			int size = 0 - sizeof(user);
			fseek(fp, size, SEEK_CUR);
			fwrite(&NewUser, sizeof(user), 1, fp);
			cout<<"Flag of existence: " << NewUser.exist << endl;
			return AdminMenu();
		}
	}*/

	//fseek(fp, 0, SEEK_SET);
	//while (!feof(fp))
	//{
	//	fread(&DelUser, sizeof(user), 1, fp);
	//		DelUser.exist = false;
	//	fpos_t k;
	//	fgetpos(fp, &k);
	//	int p= k - sizeof(user);
	//	User.exist = false;
	//	/*int size = 0 - sizeof(user);
	//	fseek(fp, size, SEEK_CUR);*/
	//	fseek(fp, p, SEEK_CUR);
	//	User.exist = false;
	//	fwrite(&DelUser, sizeof(DelUser), 1, fp);
	//	cout << DelUser.login << " was deleted." << endl;
	//	return AdminMenu();
	//	
	//	
	//}

/*	int check = 0;
	{
		cout << "Enter new username" << endl;
		cin >> NewUser.login;
		fpos_t posi;
		int check = 0;
		fgetpos(fp, &posi);
		fseek(fp, 0, SEEK_SET);
		while (!feof(fp))
		{
			fread(&User, sizeof(user), 1, fp);
			if (IsNotNewUser(NewUser) == true)
			{
				NewUser.exist = false;
				posi = posi - sizeof(user);
				fsetpos(fp, &posi);
				fwrite(&NewUser.exist, sizeof(user), 1, fp);
				cout << "Flag of existence: " << NewUser.exist << endl;
				return AdminMenu();
			}
			else
			{
				cout << "This username isn't exist" << endl;
				return AdminMenu();
			}
		}

	}*/
	//user NewUser;
	//int check = 0;
	//cout << "Enter login of the user you want to delete:" << endl;
	//cin >> NewUser.login;

	//fseek(fp, 0, SEEK_SET);
	//while (!feof(fp))
	//{
	//	/*fread(&NewUser, sizeof(user), 1, fp);*/
	//	if (IsNotNewUser(NewUser) == true)
	//	{
	//		check++;
	//		NewUser.exist = false;
	//		int size = 0 - sizeof(user);
	//		fseek(fp, size, SEEK_CUR);
	//		fwrite(&NewUser, sizeof(user), 1, fp);
	//		cout << NewUser.login << " was deleted." << endl;
	//		cout << "Flag of existence: " << NewUser.exist << endl;
	//		fclose(fp);
	//		return AdminMenu();
	//		/*break;*/
	//	}
	//	else
	//	{
	//		cout << NewUser.login << " not found" << endl;
	//		return AdminMenu();
	//	}
	//}

 //   fseek(fp, sizeof(User), SEEK_END);
	//user DelUser;
	//fseek(fp, sizeof(User), SEEK_SET);
	//cout << "Enter login of the user you want to delete:" << endl;
	//cin >> DelUser.login; cout << endl;
	//while (!feof(fp))
	//{
	//	(fread(&DelUser, sizeof(DelUser), 1, fp));
	//	DelUser.exist = false;
	//	fpos_t find;
	//	fgetpos(fp, &find);
	//	int f = find - sizeof(user);
	//	fseek(fp, f, SEEK_SET);
	//	fwrite(&DelUser.exist, sizeof(user), 1, fp);
	//	cout << DelUser.login << " was deleted." << endl;
	//	cout << "Flag of existence: " << DelUser.exist << endl;
	//	return AdminMenu();
	//}

	




	//void ReadStation()
	//{
	//	ticket Station;
	//	FILE* f;
	//	f = fopen("station.bin", "rb");
	//	fseek(f, 0, SEEK_SET);
	//	while (!feof(f))
	//	{
	//		fread(&Station, sizeof(ticket), 1, f);
	//		{
	//			cout << "Station's name: " << Station.namestation << endl;
	//			cout << "Train's cost: " << Station.cost << endl;
	//			cout << endl;
	//		}
	//	}
	//	fclose(f);
	//}

	//bool IsNotNewStation(const ticket& NewStation)
	//{
	//	bool isnotnew = false;
	//	ticket ExistStation;
	//	ifstream f;
	//	f.open("station.txt");
	//	while (!f.eof())
	//	{
	//		f >> ExistStation.namestation;
	//		f >> ExistStation.cost;
	//		if (strcmp(ExistStation.namestation, NewStation.namestation) == 0)
	//		{
	//			isnotnew = true;
	//			f.close();
	//			return true;
	//		}
	//	}
	//	return false;
	//}