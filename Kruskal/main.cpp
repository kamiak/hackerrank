/*
Given an undirected weighted connected graph, find the Really Special SubTree in it. 
The Really Special SubTree is defined as a subgraph consisting of all the nodes in the graph and:

    There is only one exclusive path from a node to every other node.
    The subgraph is of minimum overall weight (sum of all edges) among all such subgraphs.
    No cycles are formed

To create the Really Special SubTree, always pick the edge with smallest weight. 
Determine if including it will create a cycle. If so, ignore the edge. If there are edges of equal weight available:

    Choose the edge that minimizes the sum 

where and are vertices and

    is the edge weight.
    If there is still a collision, choose any of them.

Print the overall weight of the tree formed using the rules.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */

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
            return from < o.from;
        }
        return weight < o.weight;
    }
};

using tGraph = map<int,set<int>>;
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

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    tEdgesSortedByWeight edges;
    for(size_t i=0;i<g_from.size();i++) {
        edges.insert(Node(g_from[i],g_to[i],g_weight[i]));
    }

    int ret=0;
    tGraph graph;
    for(auto const & edge : edges) {
        if(canAdd(graph,edge.from,edge.to)) {
            graph[edge.from].insert(edge.to);
            graph[edge.to].insert(edge.from);
            ret += edge.weight;
        }    
    }

    return ret;
}

int main()
{
    std::ifstream ifs;
    ifs.open ("input.txt", std::ifstream::in);

    string g_nodes_edges_temp;
    getline(ifs, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(ifs, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
    cout << res;

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
