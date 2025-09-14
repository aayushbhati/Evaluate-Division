class Solution {
public:
    double dfs(string src, string dst, unordered_map<string,vector<pair<string,double>>>& graph, unordered_map<string,int>& visited) {
        if(src == dst) return 1.0;
        visited[src] = 1;
        for(auto neighbor : graph[src]) {
            string nextNode = neighbor.first;
            double weight = neighbor.second;
            if(!visited[nextNode]) {
                double result = dfs(nextNode, dst, graph, visited);
                if(result > 0) return weight * result;
            }
        }
        return -1.0;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int m = equations.size();
        unordered_map<string,vector<pair<string,double>>> graph;
        unordered_set<string> nodes;
        
        for(int i = 0; i < m; i++) {
            string u = equations[i][0], v = equations[i][1];
            double val = values[i];
            graph[u].push_back({v, val});
            graph[v].push_back({u, 1.0 / val});
            nodes.insert(u);
            nodes.insert(v);
        }
        
        vector<double> results;
        for(auto& q : queries) {
            string start = q[0];
            string end = q[1];
            
            if(nodes.find(start) == nodes.end() || nodes.find(end) == nodes.end()) {
                results.push_back(-1.0);
            } else if(start == end) {
                results.push_back(1.0);
            } else {
                unordered_map<string,int> visited;
                results.push_back(dfs(start, end, graph, visited));
            }
        }
        return results;
    }
};
