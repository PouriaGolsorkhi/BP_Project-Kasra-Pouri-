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

using ll = long long;

struct gameplay{
	#ifdef WINDOWS
		HANDLE col =  GetStdHandle(STD_OUTPUT_HANDLE);
	#endif
	
	string user, user1, name, creator, diff, mode;

	bool ext = false;
	
	int n, m, l, mn, mx, b1, b2, ssp;

	vector<int> sp;

	vector<vector<ll>> maze;
	
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
		cout << "difficulty: " << diff << "\n\n";
		for(int _ = 0; _ < ssp + m + 1; ++_)
			cout << '_';
		cout << '\n';
		for(int i = 0; i < n; ++i){
			cout << "|";
			for(int j = 0; j < m; ++j){
				if(mark[i][j])
					c_col(1 + (!maze[i][j] ? 3 : 0));
				cout << maze[i][j];
				if(mark[i][j])
					c_col(15);
				for(int k = 0; k < sp[j] - max(1, (int)ceil(log10(abs(maze[i][j]) + 1))) - (int)(maze[i][j] < 0); ++k)
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
		cout << "t: timer, u: undo\n";
		cout << "q: quit and show soloution\n";
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
				sp[j] = max(sp[j], max(1, (int)ceil(log10(abs(maze[i][j]) + 1))) + (int)(maze[i][j] < 0));
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
			cout << "(There is no guarantee that maps that are not generated by random generator will have a solution)" << '\n';
			for(int i = 0; i < mapname.size(); ++i)
				cout << " - " << i + 1 << ". " << mapname[i] << '\n';
			if(!mapname.size())
				cout << " - There is no map but you can create maps by choosing 2.2 or 1 from menu" << '\n';
			cout << "enter number of the map you want" << '\n';
			cout << "if your opinion changed write -1 and press enter key" << '\n';
			if(b)
				cout << "invalid input, try again" << '\n';
			int ind;
			cin >> ind;
			if(ind == -1){
				ext = true;
				return;
			}
			if(mapname.size() < ind || ind < 1){
				b = true;
				continue;
			}
			ifstream mp("./maps/" + mapname[ind - 1] + ".txt");
			load_data(mp);
			mp.close();
			print_map();
			cout << "press any key to continue ";
			getch();
			b = false;
		}
		return;
	}
	// x 0 y --> z   max(x-z, x)    min(y-z, y)
	//                 x      y-z
	//                x-z       y
	void gen(ofstream &mp){
		for(int i = 0; i < n; ++i){
			maze.push_back({}), mark.push_back({});
			for(int j = 0; j < m; ++j)
				maze[i].push_back(0), mark[i].push_back(false);
		}
		// masir javab
		// por kardan masir
		int cnt0 = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(!mark[i][j]){
					if(((rand() + time(0)) & 1) && cnt0 != bu){
						mark[i][j] = true;
						++cnt0;
					}
					else{
						maze[i][j] = ((rand() + time(0)) % (mx - mn)) + mn;
						maze[i][j] += (int)(maze[i][j] >= 0);
					}
				}
		for(int i = (rand() + time(0)) % n, ii = 0; ii < n; ++ii, i = (i + 1) % n)
			for(int j = (rand() + time(0)) % m, jj = 0; jj < m; ++jj, j = (j + 1) % m)
				if(!mark[i][j] && cnt0 != bl){
					mark[i][j] = true;
					maze[i][j] = 0;
					++cnt0;
				}
		for(int i = 0; i < n; ++i, cout << '\n')
			for(int j = 0; j < m; ++j)
				mp << maze[i][j] << " ";
		return;
	}
	
	void upload_data(ofstream &mp, string mapn, char c = '*'){
		head();
		mp << user1 << '\n';
		mp << mapn << '\n';
		mp << mode << '\n';
		if(c == '1'){
			cout << "enter the height and width of the maze" << '\n';
			cin >> m;
			n = 3, l = m + 2, mn = -3, mx = 3;
			cout << "enter the minimum number, and maximum number of 0s respectively" << '\n';
			cin >> b1 >> b2;
		}
		else if(c == '2'){
			cout << "enter the height and width of the maze and the path lenght in this order(height withd path lenght)" << '\n';
			cin >> n >> m >> l;
			cout << "enter the minimum number in the maze and maximum number in the maze respectively" << '\n';
			cin >> mn >> mx;
			cout << "enter the minimum number, and maximum number of 0s respectively" << '\n';
			cin >> b1 >> b2;
		}
		else{
			cout << "enter the height and width of the maze and the path lenght in this order(height withd path lenght)" << '\n';
			cin >> n >> m >> l;
		}
		if(n <= 3 && l == n + m - 1){
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
			for(int i = 0; i < n; ++i){
				maze.push_back({}), mark.push_back({});
				for(int j = 0; j < m; ++j){
					maze[i].push_back(0);
					mark[i].push_back(false);
					cin >> maze[i][j];
					if(!maze[i][j])
						mark[i][j] = true;
					mp << maze[i][j] << " ";
				}
				mp << '\n';
			}
			sp.clear();
			ssp = 0;
			for(int j = 0; j < m; ++j){
				sp.push_back(0);
				for(int i = 0; i < n; ++i)
					sp[j] = max(sp[j], max(1, (int)ceil(log10(abs(maze[i][j]) + 1))) + (int)(maze[i][j] < 0));
				ssp += sp[j];
			}
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
			cout << "if you're opinion changed you can write b and press the enter key" << '\n';
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
		print_map();
		cout << "press any key to continue ";
		getch();
		return;
	}
	
	void open(string u, string u1, string inpt){
		user = u, user1 = u1;
		mode = "(manual)";
		while(true){
			if(inpt.size() == 1){
				for(bool b = false; true; b = true){
					head();
					cout << "If you want to solve a maze back to menu and Choose \"3. Solve a Maze\"\n\n";
					c_col(6);
					cout << "2. Playground" << '\n';
					cout << "  - 2.1 Choose from Existing Maps" << '\n';
					cout << "  - 2.2 Import a Custom Map" << '\n';
					c_col(15);
					cout << "\nIf you want 2.1 press 1 or if you rather 2.2 press 2 and for back to menu press b\n";
					if(b)
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
				sen1();
				inpt.pop_back();
				inpt.pop_back();
				continue;
			}
			else{
				sen2();
				inpt.pop_back();
				inpt.pop_back();
				continue;
			}
		}
		return;
	}
	
	void create(string u, string u1, string inpt){
		user = u, user1 = u1;
		mode = "(random generator)";
		while(true){
			if(inpt.size() == 1){
				for(bool b = false; true; b = true){
					head();
					c_col(6);
					cout << "1. Create New Map" << '\n';
					cout << "  - 1.1 Easy" << '\n';
					cout << "  - 1.2 Hard" << '\n';
					c_col(15);
					cout << "\nIf you want 1.1 press 1 or if you rather 1.2 press 2 and for back to menu press b\n";
					if(b)
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
				sen2(inpt[2]);
				inpt.pop_back();
				inpt.pop_back();
				continue;
			}
			else{
				sen2(inpt[2]);
				inpt.pop_back();
				inpt.pop_back();
				continue;
			}
		}
		return;
	}
	
};