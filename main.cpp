#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

constexpr auto inf = int{ 987'654'321 };

const auto& dx = vi{ -1,1,0,0 };
const auto& dy = vi{ 0,0,-1,1 };

int bfs(int n, vvi& f, int px, int py, int sz, int ec) {
	auto dist = vvi(n, vi(n, inf));
	dist[py][px] = 0;

	auto q = queue<pair<int, int>>{};
	q.push({ px, py });

	auto minDist = int{ -1 };
	auto fx = int{};
	auto fy = int{};
	while (!q.empty()) {
		auto t = q.front();
		q.pop();

		const auto& x = t.first;
		const auto& y = t.second;

		if (0 < f[y][x] && f[y][x] < sz) {
			if (minDist < 0) {
				minDist = dist[y][x];
				fx = x;
				fy = y;
			}
			else {
				if (dist[y][x] < minDist) {
					minDist = dist[y][x];
					fx = x;
					fy = y;
				}
				else if (dist[y][x] == minDist) {
					if (y < fy) {
						fx = x;
						fy = y;
					}
					else if (y == fy && x < fx) {
						fx = x;
						fy = y;
					}
				}
			}
		}

		for (auto d = 0; d < 4; ++d) {
			const auto& nx = x + dx[d];
			const auto& ny = y + dy[d];

			if (nx < 0 || n <= nx ||
				ny < 0 || n <= ny) {
				continue;
			}

			if (sz < f[ny][nx]) {
				continue;
			}

			const auto& newDist = dist[y][x] + 1;
			if (newDist < dist[ny][nx]) {
				dist[ny][nx] = newDist;
				q.push({ nx, ny });
			}
		}
	}

	if (minDist < 0) {
		return 0;
	}

	f[fy][fx] = 0;

	++ec;

	if (ec == sz) {
		++sz;
		ec = 0;
	}

	return minDist + bfs(n, f, fx, fy, sz, ec);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	cin >> n;

	auto f = vvi(n, vi(n));
	auto px = int{};
	auto py = int{};
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			cin >> f[i][j];

			if (9 == f[i][j]) {
				px = j;
				py = i;
				f[i][j] = 0;
			}
		}
	}

	auto ans = int{ 0 };
	auto next = int{ 0 };
	do {
		next = bfs(n, f, px, py, 2, 0);
		ans += next;
	} while (0 < next);

	cout << ans;

	return 0;
}