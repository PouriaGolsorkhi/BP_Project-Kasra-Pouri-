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

string user;

string hs(string &s){
	ll bs[5] = {259, 258, 257, 256, 263};
	ll md[5] = {1000000021, 1000000009, 1000000007, 998244353, 7333333313LL};
	ll sum = 0;
	string res = "";
	for(int k = 0; k < 5; ++k, res += to_string(sum), sum = 0)
		for(int i = 0; i < s.size(); ++i){
			sum = (sum * bs[k]) % md[k];
			sum += s[i];
			sum %= md[k];
		}
	return res;
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
	user = hs(s1);
	us << user << '\n';
	ps << hs(s2) << '\n';
	us.close();
	ps.close();
	ofstream games("./accounts/games/" + user + ".txt");
	games.close();
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
		user = hs(s1);
		if(ind != -1 && users[ind].first == user && users[ind].second == hs(s2))
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
	bool p = true;
	string s = "1", s1 = ".";
	for(bool b = false; true; b = true){
		system("cls");
		head();
		cout << "Menu:" << '\n';
		if(s[0] == '1')
			SetConsoleTextAttribute(col, 6);
		cout << "  1. Create New Map" << '\n';
		if(s == "1.1")
			SetConsoleTextAttribute(col, 8);
		cout << "    - 1.1 Easy" << '\n';
		if(s == "1.1")
			SetConsoleTextAttribute(col, 6);
		if(s == "1.2")
			SetConsoleTextAttribute(col, 8);
		cout << "    - 1.2 Hard" << '\n';
		if(s == "1.2")
			SetConsoleTextAttribute(col, 6);
		if(s[0] == '1')
			SetConsoleTextAttribute(col, 15);
		if(s[0] == '2')
			SetConsoleTextAttribute(col, 6);
		cout << "  2. Playground" << '\n';
		if(s == "2.1")
			SetConsoleTextAttribute(col, 8);
		cout << "    - 2.1 Choose from Existing Maps" << '\n';
		if(s == "2.1")
			SetConsoleTextAttribute(col, 6);
		if(s == "2.2")
			SetConsoleTextAttribute(col, 8);
		cout << "    - 2.2 Import a Custom Map" << '\n';
		if(s == "2.2")
			SetConsoleTextAttribute(col, 6);
		if(s[0] == '2')
			SetConsoleTextAttribute(col, 15);
		if(s[0] == '3')
			SetConsoleTextAttribute(col, 6);
		cout << "  3. Solve a Maze" << '\n';
		if(s == "3.1")
			SetConsoleTextAttribute(col, 8);
		cout << "    - 3.1 Choose from Existing Maps" << '\n';
		if(s == "3.1")
			SetConsoleTextAttribute(col, 6);
		if(s == "3.2")
			SetConsoleTextAttribute(col, 8);
		cout << "    - 3.2 Import a Custom Map" << '\n';
		if(s == "3.2")
			SetConsoleTextAttribute(col, 6);
		if(s[0] == '3')
			SetConsoleTextAttribute(col, 15);
		if(s == "4")
			SetConsoleTextAttribute(col, 6);
		cout << "  4. History" << '\n';
		if(s == "4")
			SetConsoleTextAttribute(col, 15);
		if(s == "5")
			SetConsoleTextAttribute(col, 6);
		cout << "  5. Leaderboard" << '\n';
		if(s == "5")
			SetConsoleTextAttribute(col, 15);
		if(s == "6")
			SetConsoleTextAttribute(col, 6);
		cout << "  6. Exit" << '\n';
		if(s == "6")
			SetConsoleTextAttribute(col, 15);
		cout << "----------\nIf you want to select an option press it's section number\nAfter you set the section you want to go press enter key\n----------" << '\n';
		if(!((s.size() == 1 && s[0] <= '6' && s[0] >= '1') || (s.size() == 3 && s[1] == '.' && s[2] <= '2' && s[2] >= '1' && s[0] <= '3' && s[0] >= '1')) && b){
			cout << "invalid input, try again" << '\n';
			p = false;
		}
		else
			p = true;
		getline(cin, s1);
		if(s1 != "")
			s = s1;
		else if(p){
			if(s[0] == '6')
				exit(0);
			if(s[0] == '5'){
				//leaderboard();
				return;
			}
			if(s[0] == '4'){
				//history(user);
				return;
			}
			if(s[0] == '3'){
				//play(s);
				return;
			}
			if(s[0] == '2'){
				//playgr(s);
				return;
			}
			if(s[0] == '1'){
				//createmp(s);
				return;
			}
		}
	}
	return;
}

int main(){
	enter();
	menu();
	return 0;
}