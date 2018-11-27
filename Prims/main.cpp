/*
Given a graph which consists of several edges connecting its nodes, find a subgraph of the given graph with the following properties:

    The subgraph contains all the nodes present in the original graph.
    The subgraph is of minimum overall weight (sum of all edges) among all such subgraphs.
    It is also required that there is exactly one, exclusive path between any two nodes of the subgraph.

One specific node

is fixed as the starting point of finding the subgraph using Prim's Algorithm.
Find the total weight or the sum of all edges in the subgraph.

image
For example, consider a graph with
nodes. Possible edges are weight , weight and weight . Starting from node 
, we select the lower weight path, i.e. , weight . From node , there is only one path left, weight .
 We have all nodes connected at a cost of

.

Function Description

Complete the prims function in the editor below. 
It should return and integer that represents the minimum weight to connect all nodes in the graph provided.

prims has the following parameter(s):

    n: an integer that represents the number of nodes in the graph
    edges: a two-dime

and

, the number of nodes and edges in the graph.

Each of the next
lines contains three space-separated integers , and , the end nodes of , and the edge's weight.
The last line has an integer

, denoting the starting node.

Constraints




There may be multiple edges between two nodes.

Output Format

Print a single integer denoting the total weight of the subgraph. 
*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Node {
    int from;
    int to;
    int weight;

    Node()
        :from(0), to(0), weight(0) {}
    Node(int f, int t, int w)
        :from(f), to(t), weight(w) {}

    bool operator < (const Node& o) const {
        if(weight == o.weight) {
            if(from == o.from) {
                return to < o.to;
            }
            return from < o.from;
        }
        return weight < o.weight;
    }
};

using tGraph = map<int,set<int>>;
using tGraphWiyhNodes = map<int,set<Node>>;
using tEdgesSortedByWeight = set<Node>;
using tNodes = set<int>;
using tQueue = queue<int>;

bool canAdd(tGraph & g, int f, int t) {
    if(g.empty() || g[f].empty() || g[t].empty()) {
        return true;
    }

    tQueue q;
    tNodes visited;
    q.push(f);
    while(!q.empty()) {
        int n = q.front();
        visited.insert(n);
        q.pop();

        for(auto const & nn : g[n]) {
            if(nn == t) {
                return false;
            }
            if(visited.find(nn) != visited.end()) {
                continue;
            }
            q.push(nn);
        }
    }
    return true;
}

// Complete the prims function below.
int prims(int n, vector<vector<int>> edges, int start) {
    tGraphWiyhNodes g1;
    tGraph g2;
    tEdgesSortedByWeight edgesToVisit;
    tNodes visited;

    for(const auto & edge : edges) {
        Node n1(edge[0],edge[1],edge[2]);
        g1[edge[0]].insert(n1);
        Node n2(edge[1],edge[0],edge[2]);
        g1[edge[1]].insert(n2);
        if(edge[0] == start) {
            edgesToVisit.insert(n1);
            visited.insert(edge[0]);
        }
        if(edge[1] == start) {
            edgesToVisit.insert(n2);
            visited.insert(edge[1]);
        }
    }

    int ret = 0;
    while(!edgesToVisit.empty()) {
        Node nn = *edgesToVisit.begin();
        edgesToVisit.erase(edgesToVisit.begin());

        if(!canAdd(g2, nn.from, nn.to)) {
            continue;
        }

        g2[nn.from].insert(nn.to);
        g2[nn.to].insert(nn.from);
        visited.insert(nn.from);
        visited.insert(nn.to);
        ret += nn.weight;

        if((int)visited.size() == n) {
            break;
        }

        for(auto const & node : g1[nn.to]) {
            if(node.to == nn.from) {
                continue;
            }

            edgesToVisit.insert(node);
        }
    }
    
    return ret;
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

    int start;
    ifs >> start;
    ifs.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = prims(n, edges, start);

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
