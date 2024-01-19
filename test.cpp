#include<bits/stdc++.h>
using namespace std;

char* date(){
	time_t t = time(0);
	char* dt = ctime(&t);
	return dt;
}

int main(){
	//cout << date() << '\n';
	ifstream f("./maps/mapnames.txt");
	vector<string> v(3);
	getline(f, v[0]);
	getline(f, v[1]);
	f.close();
	ofstream fi("./maps/mapnames.txt");
	for(int i = 0; i < 3; ++i)
		if(v[i].size());
			//fi << v[i] << '\n';
	return 0;
}