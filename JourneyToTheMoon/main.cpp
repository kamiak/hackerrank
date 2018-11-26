/*
The member states of the UN are planning to send people to the moon. 
They want them to be from different countries. You will be given a list of pairs of astronaut ID's. 
Each pair is made of astronauts from the same country. 
Determine how many pairs of astronauts from different countries they can choose from.
For example, we have the following data on 2 pairs of astronauts, and 4 astronauts total, numbered
 0 through 3.

1   2
2   3

Astronauts by country are [0]
and [1,2,3]. There are 3 pairs to choose from:[0,1],[0,2] and [0,3]

Function Description

Complete the journeyToMoon function in the editor below. 
It should return an integer that represents the number of valid pairs that can be formed.

journeyToMoon has the following parameter(s):

    n: an integer that denotes the number of astronauts
    astronaut: a 2D array where each element is a element integer array that represents the ID's of two astronauts from the same country

Input Format

The first line contains two integers and , the number of astronauts and the number of pairs.
Each of the next lines contains

space-separated integers denoting astronaut ID's of two who share the same nationality.

Constraints

Output Format

An integer that denotes the number of ways to choose a pair of astronauts from different coutries.

*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

using tGraph = map<int, set<int>>;
using tQueue = queue<int>;
using tSet = set<int>;
using tVector = vector<int>;

// Complete the journeyToMoon function below.
long journeyToMoon(int n, vector<vector<int>> astronaut) {
    tGraph gr;
    tQueue qu;
    tSet toVisit;
    tVector groups;
    
    for(const auto & pair : astronaut) {
        gr[pair[0]-1].insert(pair[1]-1);
        gr[pair[1]-1].insert(pair[0]-1);
        toVisit.insert(pair[0]-1);
        toVisit.insert(pair[1]-1);
    }
    int rest = n - toVisit.size();
    
    while(!toVisit.empty()) {
        int gc = 0;
        qu.push(*toVisit.begin());
        toVisit.erase(toVisit.begin());
        
        while(!qu.empty()) {
            gc++;
            int as = qu.front();
            qu.pop();
            
            for(const auto& ass : gr[as]) {
                auto it = toVisit.find(ass);
                if(it == toVisit.end()) {
                    continue;
                }
                qu.push(ass);
                toVisit.erase(it);
            }
        }
        groups.push_back(gc);
    }
    long result = 0;
    int nn = n;
    for(int i=0; i<rest; i++) {
        nn -= 1;
        result += nn;
    }
    for(size_t i=0; i<groups.size()-1; i++) {
        nn -= groups[i];
        result += groups[i] * nn;
    }
    
    return result;
}

int main()
{
    std::ifstream ifs;
    ifs.open ("input.txt", std::ifstream::in);

    string np_temp;
    getline(ifs, np_temp);

    vector<string> np = split_string(np_temp);

    int n = stoi(np[0]);

    int p = stoi(np[1]);

    vector<vector<int>> astronaut(p);
    for (int i = 0; i < p; i++) {
        astronaut[i].resize(2);

        for (int j = 0; j < 2; j++) {
            ifs >> astronaut[i][j];
        }

        ifs.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = journeyToMoon(n, astronaut);

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
