/*
Consider an undirected graph containing nodes and edges. Each edge has an integer cost,

, associated with it.

The penalty of a path is the bitwise OR of every edge cost in the path between a pair of nodes,
and . In other words, if a path contains edges , then the penalty for this path is OR OR ... OR

.

Given a graph and two nodes,
and , find the path between and having the minimal possible penalty and print its penalty; if no such path exists, print to indicate that there is no path from to

.

Note: Loops and multiple edges are allowed. The bitwise OR operation is known as or in Pascal and as | in C++ and Java.
*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Node {
    int n;
    int w;
    int p;

    Node()
        :n(0), w(0), p(0) {}
    Node(int nn, int ww, int pp)
        :n(nn), w(ww), p(pp) {}
    
    bool operator < (const Node& o) const{
        if(w == o.w) {
            return n < o.n;
        }
        return w < o.w;
    }

    bool operator > (const Node& o) const{
        if(w == o.w) {
            return n > o.n;
        }
        return w > o.w;
    }
};
using tGraph = map<int,set<Node>>;
using tSet = set<int>;
using tMap = map<int,tSet>;

// Complete the beautifulPath function below.
int beautifulPath(vector<vector<int>> edges, int A, int B) {
    tGraph graph;
    for(const auto & edge : edges) {
        graph[edge[0]].insert(Node(edge[1],edge[2], -1));
        graph[edge[1]].insert(Node(edge[0],edge[2], -1));
    }

    priority_queue<Node,std::vector<Node>,std::greater<Node>> tovisit;
    tovisit.push(Node(A,0, A));
    tMap visited;

    while(!tovisit.empty()) {
        Node no = tovisit.top();        
        tovisit.pop();

        if(no.n == B) {
            return no.w;
        }

        auto it = visited[no.n].find(no.w);
        if(it != visited[no.n].end()) {
            continue;
        }
        visited[no.n].insert(no.w);
        
        const auto & edgesno = graph[no.n];
        for(const auto& nn : edgesno) {
            if(no.p == nn.n) {
                continue;
            }
            const int cost = no.w | nn.w;
            auto it = visited[nn.n].find(cost);
            if(it != visited[nn.n].end()) {
                continue;
            }

            tovisit.push(Node(nn.n,cost, no.n));
        }
    }
      
    return -1;
}

int main()
{
    std::ifstream ifs;
    ifs.open ("input.txt", std::ifstream::in);

    string nm_temp;
    getline(ifs, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        for (int j = 0; j < 3; j++) {
            ifs >> edges[i][j];
        }

        ifs.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string AB_temp;
    getline(ifs, AB_temp);

    vector<string> AB = split_string(AB_temp);

    int A = stoi(AB[0]);

    int B = stoi(AB[1]);

    int result = beautifulPath(edges, A, B);

    cout << result << "\n";

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
