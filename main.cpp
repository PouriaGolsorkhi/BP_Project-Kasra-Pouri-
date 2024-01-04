#include<bits/stdc++.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
using namespace std;

using ll = long long;

void sing_up(vector<pair<string, string>> &users);
void sing_in(vector<pair<string, string>> &users);

void head(){
	cout << "MAZE-MAVERTIK\n";
	cout << "Created by Kasra Fouladi & Pouria Golsorkhi\n";
	cout << "-------------------------------------------------------------\n\n";
	return;
}

int get_ind(vector<pair<string, string>> &users, string &s){
	for(int i = 0; i < users.size(); ++i)
		if(users[i].first == s)
			return i;
	return -1;
}

void psw(string &s){
	s = "";
	cout << "\b";
	while(true){
		char c = getch();
		if(c == 13)
			return;
		else if(c == '\b'){
			if(s.size()){
				s.pop_back();
				cout << "\b\b";
			}
		}
		else{
			cout << c;
			sleep(0.02);
			cout << "\b ";
			if(s.size())
				cout << '\b';
			cout << "*";
			s.push_back(c);
		}
	}
	return;
}

void sing_up(vector<pair<string, string>> &users){
	string s1, s2;
	for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "If you have an account and want to sing in write \"sing in\" and press enter" << '\n';
		cout << "-------------------\n";
		if(b)
			cout << "username is taken" << '\n';
		cout << "username: ";
		getline(cin, s1);
		if(s1 == "sing in"){
			sing_in(users);
			return;
		}
		int ind = get_ind(users, s1);
		if(ind == -1)
			break;
	}
	system("cls");
	head();
	cout << "If you have an account and want to sing in write \"sing in\" and press enter" << '\n';
	cout << "-------------------\n";
	cout << "username: " << s1 << '\n';
	cout << "password: ";
	//getline(cin, s2);
	psw(s2);
	if(s2 == "sing in"){
		sing_in(users);
		return;	
	}
	ofstream us("./accounts/users.txt");
	ofstream ps("./accounts/pass.txt");
	for(auto &e: users){
		us << e.first << '\n';
		ps << e.second << '\n';
	}
	us << s1 << '\n';
	ps << s2 << '\n';
	us.close();
	ps.close();
	return;
}

void sing_in(vector<pair<string, string>> &users){
	string s1, s2;
	for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "If want to create account write \"sing up\" and press enter" << '\n';
		cout << "-------------------\n";
		if(b)
			cout << "username or password is in correct" << '\n';
		cout << "username: ";
		getline(cin, s1);
		if(s1 == "sing in"){
			sing_in(users);
			return;	
		}
		cout << "password: ";
		/////////////////
		//getline(cin, s2);
		psw(s2);
		/////////////////
		if(s2 == "sing in"){
			sing_in(users);
			return;	
		}
		int ind = get_ind(users, s1);
		if(ind != -1 && users[ind].first == s1 && users[ind].second == s2)
			return;
	}
	return;
}

void enter(){
	ifstream us("./accounts/users.txt");
	ifstream ps("./accounts/pass.txt");
	if(!us.is_open() || !ps.is_open()){
		cerr << "Can't find data" << '\n';
		exit(1);
	}
	vector<pair<string, string>> users;
	string s;
	while(getline(us, s)){
		users.push_back({});
		users.back().first = s;
		getline(ps, s);
		users.back().second = s;
	}
	us.close();
	ps.close();
	for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "Have an account? (y/n)" << '\n';
		if(b)
			cout << "invalid input, try again" << '\n';
		getline(cin, s);
		if(s == "y" || s == "n")
			break;
	}
	if(s[0] == 'y')
		sing_in(users);
	else
		sing_up(users);
	return;
}

void menu(){
	//system("Color 0D");
	//for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "Menu:" << '\n';
		cout << "  1. Create a New Map" << '\n';
		cout << "    - 1.1 Easy" << '\n';
		cout << "    - 1.2 Hard" << '\n';
		cout << "  2. Playground" << '\n';
		cout << "    - 2.1 Choose from Existing Maps" << '\n';
		cout << "    - 2.2 Import a Custom Map" << '\n';
		cout << "  3. Solve a Maze" << '\n';
		cout << "    - 3.1 Choose from Existing Maps" << '\n';
		cout << "    - 3.2 Import a Custom Map" << '\n';
		cout << "  4. History" << '\n';
		cout << "  5. Leaderboard" << '\n';
		cout << "  6. Exit" << '\n';
	//}
	return;
}
// - : undo
int main(){
	system("Color 0A");
	enter();
	menu();
	//forget();
	return 0;
}