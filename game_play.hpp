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
	
	string user, user1, name, creator, diff;

	bool ext = false;
	
	int n, m, l, sp = 11;

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
		cout << '\n';
		return;
	}

	void print_map(){
		head();
		cout << name << " created by ";
		c_col(1);
		cout << creator;
		c_col(15);
		cout << ":\nHeight = " << n << ", Width = " << m << ", Path lenght = " << l << "\n\n";
		cout << "difficulty: " << diff << "\n\n";
		for(int _ = 0; _ < m * (sp + 1); ++_)
			cout << '_';
		cout << '_';
		cout << '\n';
		for(int i = 0; i < n; ++i){
			cout << "|";
			for(int j = 0; j < m; ++j){
				if(maze[i][j] && mark[i][j])
					c_col(1);
				cout << maze[i][j];
				if(maze[i][j] && mark[i][j])
					c_col(15);
				for(int k = 0; k < sp - max(1, (int)ceil(log10(abs(maze[i][j]) + 1))) - (int)(maze[i][j] < 0); ++k)
					cout << " ";
				cout << "|";
			}
			cout << '\n';
			for(int _ = 0; _ < m * (sp + 1); ++_)
				if(_ % (sp + 1))
					cout << '_';
				else
					cout << '|';
			cout << "|";
			cout << '\n';
		}
		cout << "\n------------------------\nCommands that you need when you're playing:\n";
		cout << "w: move to the upper cell, s: move to the lower cell\n";
		cout << "a: move to left, d: move to right\n";
		cout << "t: timer\n";
		cout << "q: quit(and show soloution)\n";
		cout << "-------------------------\n";
		cout << "press any key to continue ";
		getch();
		return;
	}
	
	void load_data(ifstream &mp){
		getline(mp,  creator);
		getline(mp, name);
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
		return;
	}
	
	void sen1(){
		ifstream mapls("./maps/mapnames.txt");
		string s;
		vector<string> mapname;
		while(getline(mapls, s))
			mapname.push_back(s);
		mapls.close();
		for(bool b = false; true; ){
			head();
			cout << "You can choose one of this maps:" << '\n';
			for(int i = 0; i < mapname.size(); ++i)
				cout << " - " << i + 1 << ". " << mapname[i] << '\n';
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
			b = false;
		}
		return;
	}
	
	void upload_data(ofstream &mp, string mapn){
		head();
		mp << user1 << '\n';
		mp << mapn << '\n';
		cout << "enter the height and width of maze and the path lenght in this order(height withd path lenght)" << '\n';
		cin >> n >> m >> l;
		if(n == 3 && l == n + m - 1){
			mp << "Easy" << '\n';
			diff = "Easy";
		}
		else{
			mp << "Hard" << '\n';
			diff = "Hard";
		}
		mp << n << " " << m << " " << l << '\n';
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
		return;
	}
	
	void sen2(){
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
			cout << "if you're opinion changed you can write b and press enter key" << '\n';
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
		upload_data(mp, s);
		creator = user1;
		name = s;
		mp.close();
		print_map();
		return;
	}
	
	void open(string u, string u1, string inpt){
		user = u, user1 = u1;
		while(true){
			if(inpt.size() == 1){
				for(bool b = false; true; b = true){
					head();
					cout << "If you want to solve a maze back to menu and Choose '\"3. Solve a Maze\"\n\n";
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
	
};