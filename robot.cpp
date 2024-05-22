#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Khoảng cách vô cùng
#define INF 1000000000

struct Edge {
    int u; 
    int v; 
    int w; 
};

// Hàm so sánh hai cạnh theo trọng số
bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

// Hàm tìm đường đi ngắn nhất từ một đỉnh đến tất cả các đỉnh khác bằng thuật toán Dijkstra
vector<int> dijkstra(vector<Edge> edges, int n, int s) {
    // Khởi tạo mảng dist để lưu trữ khoảng cách từ s đến các đỉnh khác
    vector<int> dist(n + 1, INF);
    // Khởi tạo mảng mark để đánh dấu các đỉnh đã xét
    vector<bool> mark(n + 1, false);
    // Hàng đợi ưu tiên để lưu trữ các cặp (khoảng cách, đỉnh)
    priority_queue<pair<int, int>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        // Lấy ra cặp (khoảng cách, đỉnh) có khoảng cách nhỏ nhất
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (mark[u]) continue;
        mark[u] = true;
        // Duyệt qua các cạnh kề với đỉnh u
        for (Edge e : edges) {
            if (e.u == u) {
                int v = e.v;
                int w = e.w;
                // Nếu đỉnh v chưa được đánh dấu và khoảng cách từ s đến v lớn hơn khoảng cách từ s đến u cộng với trọng số cạnh (u, v)
                if (!mark[v] && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    return dist;
}

// Hàm kiểm tra xem robot có nhiễu không
bool isInterference(vector<Edge> edges, int n, int a, int b, int r) {
    vector<int> distA = dijkstra(edges, n, a);
    vector<int> distB = dijkstra(edges, n, b);

    for (int i = 1; i <= n; i++) {
        if (distA[i] <= r || distB[i] <= r) {
            return true;
        }
    }
    return false;
}

// Hàm in ra lịch trình robot
void schedule(vector<Edge> edges, int n, int a, int b, int c, int d, int r) {
    // Kiểm tra xem hai robot có gây nhiễu cho nhau không
    if (isInterference(edges, n, a, b, r)) {
        cout << "Không thể!" << endl;
        return;
    }
    // Sắp xếp các cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), compare);
    // Hai biến lưu trữ vị trí hiện tại của hai robot
    int posA = a;
    int posB = b;
      vector<int> distanceBetweenVertices(n + 1, INF); // Mảng lưu trữ khoảng cách giữa các đỉnh
    distanceBetweenVertices[a] = 0;
    distanceBetweenVertices[b] = 0;
    while (posA != c || posB != d) {
        for (Edge e : edges) {
            // Nếu cạnh (u, v) là cạnh kề với vị trí hiện tại của robot A và vị trí mới của robot A không gây nhiễu cho robot B
            if (e.u == posA && !isInterference(edges, n, e.v, posB, r)) {
                // Di chuyển robot A đến đỉnh v
                posA = e.v;
               distanceBetweenVertices[posA] = distanceBetweenVertices[posA] < INF ? distanceBetweenVertices[posA] : distanceBetweenVertices[posA - 1] + e.w;
                cout << posA << " " << posB << " " << distanceBetweenVertices[posA] << endl;
                // Nếu robot A đã đến đích, dừng vòng lặp
                if (posA == c) break;
            }
            // Nếu cạnh (u, v) là cạnh kề với vị trí hiện tại của robot B và vị trí mới của robot B không gây nhiễu cho robot A
            else if (e.u == posB && !isInterference(edges, n, posA, e.v, r)) {
                // Di chuyển robot B đến đỉnh v
                posB = e.v;
               distanceBetweenVertices[posB] = distanceBetweenVertices[posB] < INF ? distanceBetweenVertices[posB] : distanceBetweenVertices[posB - 1] + e.w;
                cout << posA << " " << posB << " " << distanceBetweenVertices[posB] << endl;
                // Nếu robot B đã đến đích, dừng vòng lặp
                if (posB == d) break;
            }
        }
    }
}

// Hàm chính
int main() {
    // Nhập số đỉnh và số cạnh của đồ thị
    int n, m, a, b, c, d, s;
    unsigned int r;
    vector<Edge> edges;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        edges.push_back({x, y, w});
    }
    cin >> a >> b;
    cin >> c >> d;
    cin >> r;
    schedule(edges, n, a, b, c, d, r);
    return 0;
}