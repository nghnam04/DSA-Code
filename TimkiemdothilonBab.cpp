#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#define int long long
#define fi first
#define se second
#define mod 1000000007
#define inf 444444444444444444
#define pii pair <int,int>
#define mp make_pair
using namespace std;
const int N = 5757, M = 100000;
string s[M], st;
int t = 1, u, pre[M], tmp = 1, ddr[M], dd[M], com[M], c;
pii post[M];
vector <int> dsk[M], dskr[M];

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
	for (int i = 1; i <= N; i++){
		cin >> s[i];
	}
	cin >> st; //Nhap tu can tim cac tu cung lien thong manh;
	for (int i = 1; i <= N; i++){
		if (s[i] == st){
			u = i;
			break;
		} 
	}
}

void previsit (int u){
	pre[u] = tmp;
	tmp++;
}

void postvisit (int u){
	post[u] = mp(tmp, u);
	tmp++;
}

void explore (int u, vector <int> a[], int d[]){
	previsit(u);
	for (int i = 0; i < a[u].size(); i++){
		int v = a[u][i];
		if (d[v] == 0){
			d[v] = u;
			com[v] = com[u];
			explore(v, a, d);
		}
	}
	if (com[u] == 0) postvisit(u);
}

void dfs(){
	for (int i = 1; i <= N; i++){
		if (ddr[i] == 0){
			ddr[i] = -1;
			explore(i, dskr, ddr);
		}
	}
}

void solve(){
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			if (check(s[i], s[j]) == 0 && i != j){
				dsk[i].push_back(j);
				dskr[j].push_back(i);
			}
		}
	}
	dfs();
	sort(post + 1, post + N + 1);
	for (int i = N; i > 0; i--){
		if (dd[post[i].se] == 0){
			dd[post[i].se] = -1;
			c++;
			com[post[i].se] = c;
			explore(post[i].se, dsk, dd);
		}
	}
	cout << "So thanh phan lien thong manh la " << c << endl;
	cout << "Cac tu cung thanh phan lien thong manh voi " << st << endl;
	for (int i = 1; i <= N; i++){
		if (com[u] == com[i] && u != i) cout << s[i] << endl;
	}
}

main(){
freopen("TimkiemdothilonB.inp","r",stdin);
freopen("TimkiemdothilonB.out","w",stdout);
ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int ntest = 1; ntest <= t; ntest++){
		input();
		solve();
	}
}


