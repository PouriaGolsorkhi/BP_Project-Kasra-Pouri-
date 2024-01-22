#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <math.h>
#include <algorithm>
using namespace std;

#define WINDOWS

#ifdef WINDOWS
    #include <windows.h>
#endif

#define int long long

#define rand() (int)(abs(rand()) + (int)time(0))

struct gameplay{
	#ifdef WINDOWS
		HANDLE col =  GetStdHandle(STD_OUTPUT_HANDLE);
	#endif
	
	string user, user1, name, creator, diff, mode;
	
	time_t tb, tp;
	
	bool ext = false, frombot = false, forplay = false, in_play = false;
	
	int n, m, l, mn, mx, b1, b2, ssp;

	int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
	
	int pl = 15;
	
	vector<int> sp;

	vector<vector<int>> maze, ans;
	
	vector<vector<bool>> mark;
	
	void c_col(int c){
    	#ifdef  WINDOWS
        	SetConsoleTextAttribute(col, c);
	    #else
    	    //do something
        	return;
	    #endif
    	return;
	}

	void cls(){
    	#ifdef WINDOWS
        	system("cls");
	    #else
    	    system("clear");
    	#endif
    	return;
	}

	char* date(){
		time_t t = time(0);
		char* dt = ctime(&t);
		return dt;
	}

	void head(){
    	cls();
		c_col(10);
		cout << "Maze Maverick\n";
		cout << "Created by: Kasra Fouladi and Pouria Golsorkhi\n";
		c_col(15);
		cout << "_______________________________________________\n";
		if(user.size()){
			c_col(1);
			cout << "~ " << user1 << "\n";
			c_col(15);
			cout << "_______________________________________________\n";
		}
		c_col(14);
		cout << "Local time: " << date() << '\n';
		c_col(15);
		return;
	}

	void print_map(){
		head();
		cout << name << " created by ";
		c_col(1);
		cout << creator;
		c_col(15);
		cout << " " << mode << ":\nHeight = " << n << ", Width = " << m << ", Path lenght = " << l << "\n\n";
		cout << "difficulty: " << diff << "\n";
		if(in_play){
			c_col(14);
			cout << "Timer: " << time(0) - tb << "s\n\n";
			c_col(15);
		}
		for(int _ = 0; _ < ssp + m + 1; ++_)
			cout << '_';
		cout << '\n';
		for(int i = 0; i < n; ++i){
			cout << "|";
			for(int j = 0; j < m; ++j){
				if(mark[i][j])
					c_col(1 + (maze[i][j] && frombot? 5: 0) + (!maze[i][j] ? 3 : 0));
				cout << maze[i][j];
				if(mark[i][j])
					c_col(15);
				for(int k = 0; k < sp[j] - max(1LL, (int)ceil(log10(abs(maze[i][j]) + 1))) - (int)(maze[i][j] < 0); ++k)
					cout << " ";
				cout << "|";
			}
			cout << '\n';
			for(int k = 0; k < m; ++k){
				cout << '|';
				for(int _ = 0; _ < sp[k]; ++_)
					cout << '_';
			}
			cout << "|\n";
		}
		cout << "\n------------------------\nCommands that you need when you're playing:\n";
		cout << "w: move to the upper cell, s: move to the lower cell\n";
		cout << "a: move to left, d: move to right\n";
		cout << "u: undo, q: quit and show soloution\n";
		cout << "-------------------------\n";
		return;
	}
	
	void load_data(ifstream &mp){
		getline(mp, creator);
		getline(mp, name);
		getline(mp, mode);
		mp >> diff;
		mp >> n >> m >> l;
		for(int i = 0; i < n; ++i){
			maze.push_back({}), mark.push_back({});
			for(int j = 0; j < m; ++j){
				maze[i].push_back(0);
				mark[i].push_back(false);
				mp >> maze[i][j];
				if(!maze[i][j])
					mark[i][j] = true;
			}
		}
		sp.clear();
		ssp = 0;
		for(int j = 0; j < m; ++j){
			sp.push_back(0);
			for(int i = 0; i < m; ++i)
				sp[j] = max(sp[j], max(1LL, (int)ceil(log10(abs(maze[i][j]) + 1))) + (int)(maze[i][j] < 0));
			ssp += sp[j];
		}
		return;
	}
	
	void sen1(){
		ifstream mapls("./maps/mapnames.txt");
		string s;
		vector<string> mapname;
		while(getline(mapls, s))
			mapname.push_back(s);
		mapls.close();
		for(bool b = false; true;){
			head();
			cout << "You can choose one of the maps:" << '\n';
			cout << "(There is no guarantee that maps that are not generated by random generator will have a solution)" << "\n\n";
			for(int i = 0; i < mapname.size(); ++i)
				cout << " - " << i + 1 << ". " << mapname[i] << '\n';
			if(!mapname.size())
				cout << "\n~ There is no map but you can create maps by choosing 2.2 or 1 from menu" << '\n';
			cout << "enter number of the map you want" << '\n';
			cout << "you can write -1 and press the enter key for back" << '\n';
			if(b)
				cout << "invalid input, try again" << '\n';
			int ind;
			cin >> ind;
			if(ind == -1)
				return;
			if(mapname.size() < ind || ind < 1){
				b = true;
				continue;
			}
			ifstream mp("./maps/" + mapname[ind - 1] + ".txt");
			load_data(mp);
			mp.close();
			if(forplay){
				play();
				continue;
			}
			print_map();
			cout << "press any key to continue ";
			getch();
			b = false;
		}
		return;
	}
	
	bool valid(vector<int> c){
		if(c[0] < 0 || c[0] > n - 1)
			return false;
		if(c[1] < 0 || c[1] > m - 1)
			return false;
		return !mark[c[0]][c[1]];
	}
	
	bool ok, give_up;

	void solve(vector<int> c, int p, int sum){
		if(c[0] == n - 1 && c[1] == m - 1 && !p && !sum){ 
			ok = true;
			return;
		}
		if(!p)
			return;
		if(time(0) - tp > pl){
			give_up = true;
			return;
		}
		for(int i = rand() % 4 , j = 0 ; j < 4; ++j, i = (i + 1) % 4)
			if(valid({c[0] + dx[i], c[1] + dy[i]})){
				mark[c[0] + dx[i]][c[1] + dy[i]] = true;
				ans.push_back({c[0] + dx[i], c[1] + dy[i]});
				solve({c[0] + dx[i], c[1] + dy[i]}, p - 1, sum + maze[c[0]][c[1]]);
				if(ok || give_up)
					return;
				mark[c[0] + dx[i]][c[1] + dy[i]] = false;
				ans.pop_back();
			}
			return;
	}

	int rnd(int mn, int mx){
		int res = rand() % (mx - mn) + mn;
		if(res >= 0)
			++res;
		return res;
	}
	
	void gen(ofstream &mp){
		for(int i = 0; i < n; ++i){
			maze.push_back({}), mark.push_back({});
			for(int j = 0; j < m; ++j)
				maze[i].push_back(0), mark[i].push_back(false);
		}
		ok = give_up = false;
		mark[0][0] = true;
		ans.push_back({0, 0});
		tp = time(0);
		solve({0, 0}, l, 0);
		int sum = 0, mx1 = min(abs(mx), abs(mn)), mn1 = -mx1;
		for(int i = 0; i < l - 2; ++i){
			maze[ans[i][0]][ans[i][1]] = rnd(mn1 - min(0LL, sum), mx1 - max(0LL, sum));
			sum += maze[ans[i][0]][ans[i][1]];
		}
		while(true){
			int k = rnd(mn1 - min(0LL, sum), mx1 - max(0LL, sum));
			if(k + sum){
				maze[ans[l - 2][0]][ans[l - 2][1]] = k;
				sum += k;
				break;
			}
		}
		int cnt0 = (m * n) - l - 1;
		maze[ans[l - 1][0]][ans[l - 1][1]] = -sum;
		maze[n - 1][m - 1] = rnd(mn, mx);
		vector<vector<bool>> mark1(n, vector<bool>(m, false));
		for(auto &e: ans)
			mark1[e[0]][e[1]] = true;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(!mark1[i][j])
					if(rand() % 2 == 1 && (cnt0 > b1))
						maze[i][j] = rnd(mn, mx), --cnt0, mark1[i][j] = true;
		if(cnt0 > b2)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j)
					if(!mark1[i][j] && (cnt0 > b2))
						maze[i][j] = rnd(mn, mx), mark1[i][j] = true, --cnt0;
		for(int i = 0; i < n; ++i, mp << '\n')
			for(int j = 0; j < m; ++j){
				mp << maze[i][j] << " ";
				if(!maze[i][j])
					mark[i][j] = true;
			}
		return;
	}
	
	void upload_data(ofstream &mp, string mapn, char c = '*'){
		head();
		mp << user1 << '\n';
		mp << mapn << '\n';
		mp << mode << '\n';
		if(c == '1'){
			cout << "enter the height and width of the maze repectively" << '\n';
			cin >> n >> m;
			l = m + n - 2, mn = -3, mx = 3, b1 = 2, b2 = 5;
		}
		else if(c == '2'){
			cout << "enter the height and width of the maze and the path lenght respectively" << '\n';
			cin >> n >> m >> l;
			cout << "enter the minimum number in the maze and maximum number in the maze respectively" << '\n';
			cin >> mn >> mx;
			cout << "enter the minimum number, and maximum number of 0s respectively" << '\n';
			cin >> b1 >> b2;
		}
		else{
			cout << "enter the height and width of the maze and the path lenght respectively" << '\n';
			cin >> n >> m >> l;
		}
		if(c == '1' || (c != '2' && (c == '*' || b2 < 6) && l == n + m - 2)){
			mp << "Easy" << '\n';
			diff = "Easy";
		}
		else{
			mp << "Hard" << '\n';
			diff = "Hard";
		}
		mp << n << " " << m << " " << l << '\n';
		if(c != '*')
			gen(mp);
		else{
			cout << "Now you have to fill the maze cells\n";
			maze.push_back({}), mark.push_back({});
			for(int i = 0; i < n; ++i, mp << '\n'){
				maze.push_back({}), mark.push_back({});
				for(int j = 0; j < m; ++j){
					maze[i].push_back(0);
					mark[i].push_back(false);
					cin >> maze[i][j];
					if(!maze[i][j])
						mark[i][j] = true;
					mp << maze[i][j] << " ";
				}
			}
		}
		sp.clear();
		ssp = 0;
		for(int j = 0; j < m; ++j){
			sp.push_back(0);
			for(int i = 0; i < n; ++i)
				sp[j] = max(sp[j], max(1LL, (int)ceil(log10(abs(maze[i][j]) + 1))) + (int)(maze[i][j] < 0));
			ssp += sp[j];
		}
		return;
	}
	
	void sen2(char c = '*'){
		ifstream mapls("./maps/mapnames.txt");
		int cnt = 0;
		string s, s1;
		vector<string> mapname, maplist;
		while(getline(mapls, s)){
			mapname.push_back(s);
			maplist.push_back(s);
		}
		mapls.close();
		if(maplist.size())
			sort(maplist.begin(), maplist.end());
		bool p = false;
		while(true){
			head();
			cout << "you can write b and press the enter key for back" << '\n';
			cout << "Map's name: ";
			s = "";
			while(!s.size())
				getline(cin, s);
			if(s == "b"){
				ext = true;
				return;
			}
			cout << '\n';
			if(maplist.size() && binary_search(maplist.begin(), maplist.end(), s)){
				cout << "this map name is already exists do you want to replace it? (y:yes/any other key:no)" << '\n';
				char c = getch();
				if(c == 'y'){
					ifstream f("./maps/" + s + ".txt");
					getline(f, s1);
					f.close();
					if(user1 == s1){
						p = true;
						break;
					}
					else{
						cout << "sorry but you can't just the creator of the map can change it" << '\n';
						cout << "press any key to continue" << '\n';
						getch();
					}
				}
			}
			else
				break;
		}
		if(!p)
			mapname.push_back(s);
		cout << "press (b:if you want to back, any other key:to continue)\n";
		if(getch() == 'b')
			return;
		reverse(mapname.begin(), mapname.end());
		ofstream mapls_("./maps/mapnames.txt");
		for(auto &e: mapname)
			mapls_ << e << '\n';
		mapls_.close();
		ofstream mp("./maps/" + s + ".txt");
		upload_data(mp, s, c);
		creator = user1;
		name = s;
		mp.close();
		if(forplay){
			play();
			return;
		}
		print_map();
		cout << "press any key to continue ";
		getch();
		return;
	}
	
	void create(string u, string u1, string inpt){
		if(inpt[0] == '3'){
			forplay = true;
			inpt[0] = '2';
		}
		user = u, user1 = u1;
		mode = "(manual)";
		if(inpt[0] == '1'){
			mode = "(random generator)";
			frombot = true;
		}
		while(true){
			maze.clear(), mark.clear(), ans.clear();
			if(inpt.size() == 1){
				for(bool bbb = false; true; bbb = true){
					head();
					if(inpt[0] == '1'){
						c_col(6);
						cout << "1. Create New Map" << '\n';
						cout << "  - 1.1 Easy" << '\n';
						cout << "  - 1.2 Hard" << '\n';
					}
					else{
						if(!forplay)
							cout << "If you want to solve a maze back to menu and Choose \"3. Solve a Maze\"\n\n";
						c_col(6);
						cout << (forplay ? "3. Solve a maze" : "2. Playground") << '\n';
						cout << "  - " << 2 + forplay << ".1 Choose from Existing Maps" << '\n';
						cout << "  - " << 2 + forplay << ".2 Import a Custom Map" << '\n';
					}
					c_col(15);
					cout << "\nIf you want "<< (char)(inpt[0] + forplay) << ".1 press 1 or if you rather " << (char)(inpt[0] + forplay) <<".2 press 2 and for back to menu press b\n";
					if(bbb)
						cout << "invalid input, try again" << '\n';
					char c = getch();
					if(c == '1' || c == '2'){
						inpt.push_back('.');
						inpt.push_back(c);
						break;
					}
					if(c == 'b')
						return;
				}
			}
			if(inpt[2] == '1'){
				inpt[0] == '1' ? sen2(inpt[2]) : sen1();
				inpt.pop_back(), inpt.pop_back();
				continue;
			}
			else{
				sen2(inpt[0] == '1' ? inpt[2] : '*');
				inpt.pop_back(), inpt.pop_back();
				continue;
			}
		}
		return;
	}
	
	void quit(){
		frombot = true;
		ans.clear(), ans.push_back({0, 0});
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				mark[i][j] = !maze[i][j];	
		mark[0][0] = true;
		ok = give_up = false;
		tp = time(0);
		solve({0, 0}, l, 0);
		if(!ok)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j)
					mark[i][j] = !maze[i][j];
		print_map();
		if(ok)
			cout << "Unfortunately you lost! Now you can see the solution" << '\n';
		else
			cout << "Sorry seems this map doesn't have any solution" << '\n';
		cout << "press any key to continue ";
		getch();
		frombot = in_play = false;
		return;
	}
	
	void play(){
		print_map();
		cout << "press (b:for back, any other key:for continue)" << '\n';
		if(getch() == 'b')
			return;
		in_play = true;
		tb = time(0);
		ans.push_back({0, 0});
		mark[0][0] = true;
		vector<int> cor = {0, 0};
		int sum = maze[0][0], plen = 0;
		char mvs[4] = {'s', 'w', 'd', 'a'};
		while(true){
			print_map();
			cout << "**If you do an invalid move nothing wil change**" << '\n';
			if(sum == maze[n - 1][m - 1] && plen == l){
				cout << "You solve this maze! congragulations\n";
				cout << "press any key to continue ";
				getch();
				update(true);
				return;
			}
			char c = getch();
			if(c == 'q'){
				quit();
				update(false);
				return;
			}
			if(c == 'u' && ans.size() > 1){
				mark[cor[0]][cor[1]] = false;
				sum -= maze[cor[0]][cor[1]];
				--plen;
				ans.pop_back();
				cor = ans.back();
			}
			for(int i = 0; i < 4; ++i)
				if(c == mvs[i] && valid({cor[0] + dx[i], cor[1] + dy[i]})){
					mark[(cor[0] += dx[i])][(cor[1] += dy[i])] = true;
					ans.push_back({cor[0], cor[1]});
					sum += maze[cor[0]][cor[1]];
					++plen;
					break;
				}
		}
		in_play = false;
		return;
	}
	
	void update(bool win){
		int timer = time(0) - tb, r_changes = (win ? (n + m) * l / (timer / 60 + 1) : -50);
		string s = ctime(&tb), ln;
		ifstream hs("./accounts/games/" + user + ".txt");
		vector<string> vec;
		while(getline(hs, ln))
			vec.push_back(ln);
		hs.close();
		ofstream histo("./accounts/games/" + user + ".txt");
		histo << s << '\n';
		histo << name << '\n';
		histo << (win ? "Y" : "N") << '\n';
		histo << timer << '\n';
		histo << r_changes << '\n';
		for(string &e: vec)
			histo << e << '\n';
		vec.clear();
		histo.close();
		ifstream rnk("./accounts/ranking.txt");
		while(getline(rnk, ln))
			vec.push_back(ln);
		for(int i = 0; i < vec.size(); i += 2)
			if(user1 == vec[i]){
				vec[i + 1] = to_string(stoi(vec[i + 1]) + r_changes);
				break;
			}
		ofstream rank("./accounts/ranking.txt");
		for(int i = 0; i < vec.size(); ++i)
			rank << vec[i] << '\n';
		rank.close();
		return;
	}
	
};