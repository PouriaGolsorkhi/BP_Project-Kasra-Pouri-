#include<bits/stdc++.h>
using namespace std;

char* date(){
	time_t t = time(0);
	char* dt = ctime(&t);
	return dt;
}

struct khar{

void play2(){
	play();
	return;	
}

void play(){
	return;
}

};

int main(){
	ofstream f2("./accounts/ranking.txt");
	f2 << "kasra" << '\n';
	f2 << 0 << '\n';
	//int n;
	//cin >> n;
	//cout << n << '\n';
	return 0;
	ifstream f("./accounts/games/0000000000000000000000178089785000000000000000000000076548303000000000000000000000004384901820000000000000000000000007565459000000000000000000001698062084.txt");
	vector<string> vec;
	string s;
	while(getline(f, s))
		vec.push_back(s);
	f.close();
	ofstream f1("./accounts/games/0000000000000000000000178089785000000000000000000000076548303000000000000000000000004384901820000000000000000000000007565459000000000000000000001698062084.txt");
	for(int i = 0; i < vec.size(); ++i)
		if(i % 5 == 4 && stoi(vec[i]) > 0){
			f1 << '+' << vec[i] << '\n';
			cout << '+' << vec[i] << '\n';
		}
	f1.close();
	return 0;
	/*
	return 0;
	//cout << date() << '\n';
	time_t t = time(0);
	for(int i = 0; i < 1000 * 1000 * 1000; ++i)
		int x;
	cout << (char)7;
	cout << "done! in" << '\n';
	cout << time(0) - t << " secondes" << '\n';
	return 0;
	*/
	//ofstream f("./maps/mapnames.txt");
	/*
	vector<string> v(3);
	getline(f, v[0]);
	getline(f, v[1]);
	f.close();
	ofstream fi("./maps/mapnames.txt");
	for(int i = 0; i < 3; ++i)
		if(v[i].size());
			//fi << v[i] << '\n';
	*/
	return 0;
}