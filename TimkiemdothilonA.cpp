#include<iostream>
#include<string>
#include<vector>
#define int long long
#define fi first
#define se second
#define mod 1000000007
#define inf 444444444444444444
#define pii pair <int,int>
#define mp make_pair
using namespace std;
const int N = 5757;
string s[N], c, d;
vector <int> dsk[N];
int h[N], a[N], st, en, count, ans = 1;

int check (string c, string d){
	int count = 0;
	for (int k = 0; k < 5; k++){
		if (c[k] == d[k]) count++;
	}
	return count;
}

void input(){
	for (int i = 0; i < N; i++){
		cin >> s[i];
	}
	cin >> c;
	cin >> d;
	for (int i = 0; i < N; i++){
		if (check(s[i], c) == 5) st = i;
		if (check(s[i], d) == 5) en = i;
	}
}

void dfs(int x){
	for (int k = 0; k < dsk[x].size(); k++){
		int n = dsk[x][k];
		if (h[n] == 0 || a[x] + 1 < a[n]){
			h[n] = x;
			a[n] = a[x] + 1;
			dfs(n);
		}
	}
}

void solve(){
	for (int i = 0; i < N - 1; i++){
		for (int j = i + 1; j < N; j++){
			if (check(s[i], s[j]) == 4){
				dsk[j].push_back(i);
				dsk[i].push_back(j);
			}
		}
	}
	h[en] = -1;
	dfs(en);
	if (a[st] == 0) cout << "Khong co duong di";
	else {
		while (st != en){
			cout << s[st] << ", ";
			st = h[st];
		}
		cout << s[en];
	}
	cout << endl;
	for (int i = 0; i < N; i++){
		if (h[i] == 0){
			ans++;
			h[i] = -1;
			dfs(i);
		}
	}
	cout << "So thanh phan lien thong cua do thi:" << ans;
}

main(){
freopen("sgb-words.txt","r",stdin);
freopen("TimkiemdothilonA.out","w",stdout);
ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	solve();
}


