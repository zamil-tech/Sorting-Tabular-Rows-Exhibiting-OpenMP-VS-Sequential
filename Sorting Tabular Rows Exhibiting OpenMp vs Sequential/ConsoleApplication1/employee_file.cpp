#include<iostream>
#include<fstream>
#include<string.h>
#include <time.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
char arr[] = "abcdefghijklmnopqrstuvwxyz";
int len = sizeof(arr) - 1;
char random()
{
	return arr[rand() % len];
}

int main() {
	srand(time(NULL));
	int a;
	cout << "Enter your choice";
	cin >> a;
	int id;
	string name;
	char section;
	int salary;
	if (a == 1) {
		ifstream data("employee.txt");
		while (data >> id >> name >> salary >> section)
		{
			cout << id << " " << name << " " << salary << " " << section << " " << endl;
		}
	}
	if (a == 2) {
		string s_name;
		char c;
		ofstream data("employee.txt", std::ios::out | std::ios::app);
		int z;
		cout << "how many random values you want to generate";
		cin >> z;
		for (int i = 0; i < z; i++)
		{
			c = 'a' + rand() % 4;
			for (int j = 0; j < 5; ++j)
			{
				s_name += random();
			}
			data << i << " " << s_name << " " << rand() % 20000 + 1 << " " << c << " " << endl;
			s_name = "";
		}
	}
}
