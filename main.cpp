#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void sing_up(vector<pair<string, string>> &users);
void sing_in(vector<pair<string, string>> &users);

void sing_up(vector<pair<string, string>> &users){
	string s1, s2;
	while(bool b = false; true; b = true){
		system("cls");
		cout << "username: ";
		if(b)
			cout << "username is taken" << '\n';	
		getline(cin, s1);
		auto poz = lowerbound(users.begin(), users.end(), {s1, ""});
		if((*poz).first != s1)
			break;
	}
	system("cls");
	cout << "username: " << s1 << '\n';
	cout << "password: ";
	getline(cin, s2);
	
	return;
}

void sing_in(vector<pair<string, string>> &users){
	
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
	sort(users.begin(), users.end());
	for(bool b = false; true; b = true){
		system("cls");
		cout << "Have an account? (y/n)" << '\n';
		if(b)
			cout << "invalid input, try again" << '\n';
		getline(cin, s);
		if(s == "y" || s == "n")
			break;
	}
	if(s[0] == 'y')
		sing_in(users, pass);
	else
		sing_up(users, pass);
	return;
}

void menu(){
	cout << "1. Create a New Map" << '\n';
	cout << '\t' << "- 1.1 Easy" << '\n';
	cout << '\t' << "- 1.2 Hard" << '\n';
	cout << "2. Playground" << '\n';
	cout << '\t' << "- 2.1 Choose from Existing Maps" << '\n';
	cout << '\t' << "- 2.2 Import a Custom Map" << '\n';
	cout << "3. Solve a Maze" << '\n';
	cout << '\t' << "- 3.1 Choose from Existing Maps" << '\n';
	cout << '\t' << "- 3.2 Import a Custom Map" << '\n';
	cout << "4. History" << '\n';
	cout << "5. Leaderboard" << '\n';
	cout << "6. Exit" << '\n';
	
}

int main(){
	enter();
	menu();
	return 0;
}
