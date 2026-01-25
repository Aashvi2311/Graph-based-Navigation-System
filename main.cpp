#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <fstream>
#include <algorithm>
using namespace std;

struct Route{
    string to;
    int distance;
};
class Graph{
    public:
    //vector<vector<Route>> adj; -> Works only with numbers
    unordered_map<string,vector<Route>> adj; //will work directly with string

    void addEdge(string from, string to, int distance){
        Route r1;
        r1.to = to;
        r1.distance = distance;
        adj[from].push_back(r1);

        Route r2;
        r2.to = from;
        r2.distance = distance;
        adj[to].push_back(r2);
    }
    void loadEdgesFromFile(){
        ifstream file("distance.txt");
        if (!file) cout<<"File not found";
        string from;
        string to;
        int dist;
        while (file>>from>>to>>dist){
            Route r1;
            r1.to = to;
            r1.distance = dist;
            adj[from].push_back(r1);

            Route r2;
            r2.to = from;
            r2.distance = dist;
            adj[to].push_back(r2);
        }

    }
    void displayGraph(){
        for (auto &p : adj){
            string city = p.first;
            cout<<city<<"->";
            for (Route r : p.second){
                cout<<"("<<r.to<<","<<r.distance<<")";
            }
            cout<<endl;
        }
    }
    void BFS(string startCity){
        //No need to push route. Just push next city to visit
        unordered_map<string,bool>visited; //cant use vector<bool> as it works only with integers. city is string
        queue <string> q;

        visited[startCity] = true;
        q.push(startCity);

        while (!q.empty()){
        string current = q.front();
        q.pop();

        cout<<current<<" ";

        for (Route neighbor : adj[current]){
            if(!visited[neighbor.to]){
                visited[neighbor.to] = true;
                q.push(neighbor.to);
            }
        }
        } 
    }
    void DFS(string startCity){
        unordered_map<string,bool> visited;
        stack<string>st;

        //visited[startCity] = true; Dont mark any true without visiting them
        st.push(startCity);

        while(!st.empty()){
            string current = st.top();
            st.pop();

            if(visited[current]) continue;

            visited[current] = true; //mark when popping
            cout<<current<<" ";

            for (Route neighbor : adj[current]){
                if(!visited[neighbor.to]){
                    //visited[neighbor.to] = true; Not needed
                    st.push(neighbor.to);
                }
            }
        }
    }
    void dijkstra(string startCity,string endCity){
        unordered_map<string,int>dist; //stores city name and distance from start city
        unordered_map<string,string> parent;
        for (auto &p : adj){
            dist[p.first] = INT_MAX;
        }
        dist[startCity] = 0;
        priority_queue<
        pair<int,string>,             //city name and distance
        vector<pair<int,string>>,     //storing container
        greater<pair<int,string>>     //comparator - shortest first
        >pq ;
        pq.push({0,startCity});      //push only start city
        while (!pq.empty()){
            auto current = pq.top();
            pq.pop();

            int currDist = current.first;
            string currCity = current.second;

            if(currDist > dist[currCity]) continue;
        
        for (Route r : adj[currCity]){
            int newDist = currDist + r.distance;

            if (newDist<dist[r.to]){
                dist[r.to] = newDist;
                parent[r.to] = currCity;
                pq.push({newDist,r.to});
            }
        }
    }
        if (dist[endCity]==INT_MAX){
            cout<<"No path exists\n";
            return;
        }
        vector <string> path;
        string curr = endCity;
        while (curr!=startCity){
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(startCity);

        reverse(path.begin(),path.end());

        cout<<"Shortest path: ";
        for (string city : path){
            cout<<city<<" ";
        }
        cout<<endl;
    }
};
int main(){
    Graph g;
    g.loadEdgesFromFile();
    
    g.BFS("Jaipur");
    cout<<endl;
    g.DFS("Jaipur");
    cout<<endl;
    g.dijkstra("Delhi","Udaipur");
}

