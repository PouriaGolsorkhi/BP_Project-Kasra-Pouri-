#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int constexpr inf = (1LL << 60), maxn = 100;

ll mp[maxn][maxn];

ll rnd(int l = -inf, int r = inf, int k = 0){
	ll t = time(nullptr);
	ll rng = r - l - 1;
	ll res = ((abs(rand()) + t) % rng) + l;
	if(res >= 0)
		return res + 1;
	return res;
}

void mini_search_en(){
	/*
	It will searches parts of program
	e.g:
		search(sign up) -> sign up
	func
	-------------------------
	map
	-------------------------
	user
	-------------------------
	*/
	// show res
}

void sing_up(){
	cout << "enter a username and password" << '\n';
	string us, ps;
	while(true){
		cout << "username = ";
		cin >> us;
		if(/*us is a new user name*/)
			break;
		cout << "This username is taken" << '\n';
	}
	cout << '\n' << "password = ";
	cin >> ps;
	cout << '\n';
	system("CLS");
	cout << "Hi! " << us << " wanna have some fun?" << '\n';
	/*user's data storing in files...*/
	seelp(2);
	dashboard();
	return;
}

void sing_in(){
	int cnt = 0;
	string us, pw;
	while(++cnt){
		system("CLS");
		if(cnt >= 2)
			cout << "Incorrect username/password" << '\n';
		cout << "username: ";
		cin >> us;
		cout << '\n' << "password: ";
		cin >> pw;
		cout << '\n';
		/* check us & pw */
	}
}

void welcome(){
	cout << "Hi! please enter your account" << '\n';
	cout << "If you dont have an account yet, create one! (press 'R' for sing up or 'E' for sing in)" << '\n';
    string s;
	while(true){
		cin >> s;
		if(s == "R"){
			sing_up();
			return;
		}
		if(s == "E"){
			sing_in();
		}
	}
	sing_up();
    sing_in();
}

void user_history(/*user id*/){
	
}

void scoreboard(){
	user_history(/*user id*/);
}

void solve(){
	mp[i][j] = ;
}

void gen_map(int x, int y, int a = -3, int b = 3){
	for(int i = 0; i < x; ++i)
		for(int j = 0; j < x; ++j)
			if(rnd() & 7 == 7)
				mp[i][j] = 0;
			else
				mp[i][j] = rnd(a, b);
	return;
}

void new_map(){
	cout << "You can create a map in 2 levels, hard(Press h) or easy(Press e) which one you perfer" << '\n';
	string s;
	while(true){
		cin >> s;
		if(s != "h" && s != "e")
			cout << "Invalid input, try again" << '\n';
		else
			break;
	}
	int x, y, a, b;
	cout << "Now please specify the width and hight of the map: ";
	cin >> x >> y;
	if(s[0] == 'e'){
		gen_map(x, y);
		return;
	}
	cout << "Numbers in grids cells in range of [a, b], specify a & b" << '\n';
	cout << "a = ";
	cin >> a;
	cout << '\n' << "b = ";
	cin >> b;
	gen_map(x, y, a, b);
	return;
}


void play(){
	old_map();
	new_map();
}

void dashboard(/*user id*/){
	scoreboard();
	user_history(/*user id*/);
	play();
}

void check(string &s, bool &b = true){
	if(s == "search"){
		mini_search_en();
		return;
	}
	if(s == "q"){
		b = false;
		return;
	}
	
}

int main(){
    opening();
    welcome();
    //dashboard();
}
