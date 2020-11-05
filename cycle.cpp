#include <iostream>
#include <list>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Graph {
	public:
		Graph(int V): vertices(V), adj(new list<int>[V]) {}

		~Graph() {
			delete [] adj;
		}

		void addEdge(int u, int v) {
			adj[u].push_back(v);
		}

		bool cycle(vector<int> &path) const {
			vector<state> status(vertices);
			vector<int> p(vertices);
			bool cycle = false;

			for (int u = 0; u < vertices; ++u) {
				p[u] = -1;
				status[u] = UNVISITED;
			}
			for (int u = 0; u < vertices; ++u) {
				if (status[u] == UNVISITED && !cycle) {
					cycle_help(path, u, p, status, cycle);
				}
			}

			reverse(path.begin(), path.end());

			return cycle;
		}

	private:
		int vertices;
		list<int> *adj;
		enum state {UNVISITED, SEEN, VISITED};

		void cycle_help(vector<int> &path, int u, vector<int> &p, vector<state> &status, bool &cycle) const {
			if (cycle)
				return;

			status[u] = SEEN;

			for (int v : adj[u]) {
				if (status[v] == UNVISITED) {
					p[v] = u;
					cycle_help(path, v, p, status, cycle);
					if (cycle)
						return;
				}
				else if(status[v] == SEEN) {
					cycle = true;
					path.push_back(u);
					int pa = u;
					while (pa != v) {
						pa = p[pa];
						path.push_back(pa);
					}
					break;
				}
			}
			status[u] = VISITED;
		}

};

//Driver Programm
int main() {
	int V, E;
	cin >> V >> E;
	Graph g(V);
	for (int i = 0; i < E; ++i) {
		int u, v;
		cin >> u >> v;
		g.addEdge(u, v);
	}

	vector<int> path;
	if (g.cycle(path)) {
		cout << "CYCLE: ";
		for (int i = 0; i < path.size(); ++i) {
			cout << path[i] << (i == path.size() - 1? "\n" : " ");
		}
	} else {
		cout << "NO CYCLE" << endl;

		return 0;
	}
