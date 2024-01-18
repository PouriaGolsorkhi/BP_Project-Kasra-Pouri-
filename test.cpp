#include<bits/stdc++.h>
using namespace std;

int main(){
	ifstream f("./maps/mapnames.txt");
	vector<string> v(2);
	getline(f, v[0]);
	getline(f, v[1]);
	f.close();
	ofstream fi("./maps/mapnames.txt");
	for(int i = 0; i < 2; ++i)
		if(v[i].size())
			fi << v[i] << '\n';
	return 0;
}