#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
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
};
int main(){
    Graph g;
    g.addEdge("Delhi","Jaipur",280);
    g.addEdge("Delhi","Bikaner",330);
    g.displayGraph();
}

