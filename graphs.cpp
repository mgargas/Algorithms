#include <iostream>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

struct graph{
    int size;
    bool** E;
};

struct path_tree{
    int parent;
    int d;
};


path_tree* bfs(graph G, int s){
    path_tree* bfs_path_three = new path_tree[G.size];
    for(int i=0;i<G.size;i++){
        bfs_path_three[i].parent = -1;
        bfs_path_three[i].d = -1;
    }
    bfs_path_three[s].d = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v=0;v<G.size;v++){
            if(bfs_path_three[v].d < 0 and G.E[u][v]){
                bfs_path_three[v].d = bfs_path_three[u].d + 1;
                bfs_path_three[v].parent = u;
                q.push(v);
            }
        }
    }
    return bfs_path_three;
}


struct vertex{
    bool visited;
    int time;
};



void dfs_visit(graph G, int u, vertex* vertexes, int &time){
    vertexes[u].visited = true;
    time = time + 1;
    for(int v=0; v<G.size; v++){
        if(G.E[u][v] && !vertexes[v].visited){
            dfs_visit(G, v, vertexes, time);
        }
    }
    vertexes[u].time = time;
}

vertex* dfs(graph G){
    vertex* vertexes = new vertex[G.size];
    for(int i=0;i<G.size;i++){
        vertexes[i].visited = false;
        vertexes[i].time = INT_MIN;
    }
    int time = 0;
    for(int i=0; i<G.size; i++){
        if(!vertexes[i].visited){
            dfs_visit(G, i, vertexes, time);
        }
    }

}


void dfs_visit_topological(graph G, int u, stack<int> &s, bool* &visited){
    visited[u] = true;
    for(int v=0;v<G.size;v++){
        if(G.E[u][v] && !visited[v]){
            dfs_visit_topological(G, v, s, visited);
        }
    }
    s.push(u);
}


stack<int> topological_sort(graph G){
    bool* visited = new bool[G.size];
    for(int i=0;i<G.size;i++)visited[i]={false};
    stack<int>s;
    for(int u=0; u<G.size; u++){
        if(!visited[u]){
            dfs_visit_topological(G, u, s, visited);
        }
    }
    return s;
}


graph transpose(graph g){
    graph transposed_graph;
    transposed_graph.E = {false};
    for(int i=0;i<g.size;i++){
        for(int j=0;j<g.size;j++){
            if(g.E[i][j]){
                transposed_graph.E[j][i] = true;
            }
        }
    }
    return transposed_graph;
}


int* strongly_connected_components(graph g){
    stack<int> vertexes = topological_sort(g);
    graph transposed_graph = transpose(g);
    bool visited[g.size] = {false};
    int parent[g.size] = {-1};
    while(!vertexes.empty()){
        int u = vertexes.top();
        vertexes.pop();
        if(!visited[u]){
            dfs_visit_scc(transposed_graph, u, parent);
        }
    }
    return parent;
}

void dfs_visit_scc(graph g, int u, int* parent, bool* visited){
    visited[u] = true;
    for(int v=0; v<g.size; v++){
        if(g.E[u][v] && !visited[v]){
            parent[v] = u;
            dfs_visit_scc(g, v, parent, visited);
        }
    }
}




int main() {
    return 0;
}