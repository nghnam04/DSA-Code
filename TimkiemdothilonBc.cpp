#include<iostream>
#include<vector>
#include<string>
#define int long long
#define fi first
#define se second
#define mod 1000000007
#define inf 444444444444444444
#define pii pair <int,int>
#define mp make_pair
using namespace std;
const int N = 5757;
string s[N], u, v;
vector <int> dsk[N], ds[N];
int dd[N], a[N], st, en, tmp, ans;

int cmp(string u, string v){
	int tmp = 5;
	for (int k = 0; k < 5; k++){
		if (u[k] == v[k]) tmp--;
	}
	return tmp;
}

int check (string u, string v){
	int tmp = 1;
	while (tmp < 5){
		for (int i = 0; i < 5; i++){
			if (u[tmp] == v[i]){
				tmp++;
				v[i] = 0;
				break;
			}
			if (i == 4) return 1;
		}
	}
	return 0;
}

void input(){
	for (int i = 0; i < N; i++){
		cin >> s[i];
	}
	cin >> u; //Nhap tu bat dau
	cin >> v; //Nhap tu ket thuc
	for (int i = 0; i < N; i++){
		if (cmp(s[i], u) == 0) st = i;
		if (cmp(s[i], v) == 0) en = i;
	}
}

void dfs(int m){
	for (int k = 0; k < ds[m].size(); k++){
		int n = ds[m][k];
		if (dd[n] == 0 || a[m] + 1 < a[n]){
			dd[n] = m;
			a[n] = a[m] + 1;
			dfs(n);
		}
	}
}

void solve(){
	for (int i = 0; i < N; i++){
//		cout << s[i]; cout << " ";
		for (int j = 0; j < N; j++){
			if (check(s[i], s[j]) == 0 && i != j){
//				cout <<s[j]; cout << " ";
				dsk[i].push_back(j);
				ds[j].push_back(i);
			}
		}
//		cout << endl;
	}
	dd[en] = -1;
	dfs(en);
	if (a[st] == 0) cout << "Khong co duong di";
	else {
		while (st != en){
			cout << s[st] << ", ";
			st = dd[st];
		}
		cout << s[en];
	}
}

main(){
freopen("TimkiemdothilonB.inp","r",stdin);
freopen("TimkiemdothilonB.out","w",stdout);
ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	solve();
}


