/*
A clique in a graph is set of nodes such that there is an edge between any two distinct nodes in the set. 
Finding the largest clique in a graph is a computationally difficult problem. 
Currently no polynomial time algorithm is known for solving this. 
However, you wonder what is the minimum size of the largest clique in any graph with n nodes and m edges.

*/

#include <bits/stdc++.h>
#include <math.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'clique' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */

int clique(int n, int m) {
    const int n2 = n*n;
    int tnk;
    int ndivkcell;
    int ndivkfloor;
    int i=2;
    for(; i<=n; i++) {
        //tnk = (i-1) * n2/(2 * i);
        ndivkcell = ceil(n*1.0/i);
        ndivkfloor = floor(n*1.0/i);
        tnk = (n2 - (n%i) * ndivkcell * ndivkcell - (i - (n%i))* ndivkfloor * ndivkfloor)/2;
        if(tnk >= m) {
            break;
        }
    }
    return i;
}

int main()
{
    std::ifstream ifs;
    ifs.open ("input.txt", std::ifstream::in);

    string t_temp;
    getline(ifs, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(ifs, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = clique(n, m);

        cout << result << "\n";
    }

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
