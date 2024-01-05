#include<bits/stdc++.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<windows.h>
using namespace std;

HANDLE col =  GetStdHandle(STD_OUTPUT_HANDLE);

using ll = long long;

void sing_up(vector<pair<string, string>> &users);
void sing_in(vector<pair<string, string>> &users);

string hs(string &s){
	int bs = 9, mod = 1000000021, res = 0;
	for(int i = 0; i < s.size(); ++i){
		res = (res * bs) % mod;
		res += s[i] - 'a' + 1;
		res %= mod;
	}
	return to_string(res);
}

void head(){
	cout << "MAZE-MAVERICK\n";
	cout << "Created by Kasra Fouladi & Pouria Golsorkhi\n";
	cout << "_______________________________________________\n\n";
	return;
}

int get_ind(vector<pair<string, string>> &users, string &s){
	string s1 = hs(s);
	for(int i = 0; i < users.size(); ++i)
		if(users[i].first == s1)
			return i;
	return -1;
}

void psw(string &s){
	s = "";
	for(bool b = false; true; b = true){
		char c = getch();
		if(c == 13)
			return;
		else if(c == '\b'){
			if(s.size()){
				s.pop_back();
				cout << "\b \b";
			}
		}
		else{
			cout << c;
			for(int i = 0; i < 300000000; ++i);
			cout << "\b*";
			s.push_back(c);
		}
	}
	return;
}

void sing_up(vector<pair<string, string>> &users){
	string s1, s2, s3;
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
	for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "If you have an account and want to sing in write \"sing in\" and press enter" << '\n';
		cout << "-------------------\n";
		if(b){
			cout << "password isn't match" << '\n';
			cout << "-------------------\n";
		}
		cout << "username: " << s1 << '\n';
		cout << "password: ";
		psw(s2);
		if(s2 == "sing in"){
			sing_in(users);
			return;	
		}
		cout << '\n';
		cout << "confirm passwaord: ";
		psw(s3);
		if(s3 == "sing in"){
			sing_in(users);
			return;	
		}
		if(s2 == s3)
			break;
	}
	ofstream us("./accounts/users.txt");
	ofstream ps("./accounts/pass.txt");
	for(auto &e: users){
		us << e.first << '\n';
		ps << e.second << '\n';
	}
	us << hs(s1) << '\n';
	ps << hs(s2) << '\n';
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
		if(s1 == "sing up"){
			sing_up(users);
			return;	
		}
		cout << "password: ";
		psw(s2);
		if(s2 == "sing up"){
			sing_up(users);
			return;	
		}
		int ind = get_ind(users, s1);
		if(ind != -1 && users[ind].first == hs(s1) && users[ind].second == hs(s2))
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
	char s = 0;
	for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "Menu:" << '\n';
		if(s == '1')
			SetConsoleTextAttribute(col, 6);
		cout << "  1. Create New Map" << '\n';
		cout << "    - 1.1 Easy" << '\n';
		cout << "    - 1.2 Hard" << '\n';
		if(s == '1')
			SetConsoleTextAttribute(col, 15);
		if(s == '2')
			SetConsoleTextAttribute(col, 6);
		cout << "  2. Playground" << '\n';
		cout << "    - 2.1 Choose from Existing Maps" << '\n';
		cout << "    - 2.2 Import a Custom Map" << '\n';
		if(s == '2')
			SetConsoleTextAttribute(col, 15);
		if(s == '3')
			SetConsoleTextAttribute(col, 6);
		cout << "  3. Solve a Maze" << '\n';
		cout << "    - 3.1 Choose from Existing Maps" << '\n';
		cout << "    - 3.2 Import a Custom Map" << '\n';
		if(s == '3')
			SetConsoleTextAttribute(col, 15);
		if(s == '4')
			SetConsoleTextAttribute(col, 6);
		cout << "  4. History" << '\n';
		if(s == '4')
			SetConsoleTextAttribute(col, 15);
		if(s == '5')
			SetConsoleTextAttribute(col, 6);
		cout << "  5. Leaderboard" << '\n';
		if(s == '5')
			SetConsoleTextAttribute(col, 15);
		if(s == '6')
			SetConsoleTextAttribute(col, 6);
		cout << "  6. Exit" << '\n';
		if(s == '6')
			SetConsoleTextAttribute(col, 15);
		cout << "----------\nIf you want to select an option press it's section number\n----------\n" << '\n';
		if(!(s >= '1' && s <= '6') && b)
			cout << "invalid input, try again" << '\n';
		s = getch();
	}
	return;
}

int main(){
	enter();
	menu();
	return 0;
}