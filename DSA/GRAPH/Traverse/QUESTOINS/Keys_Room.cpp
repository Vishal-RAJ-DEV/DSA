#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// APPROACH 1: Recursive DFS (uses implicit call stack)
// The system's call stack acts as a LIFO structure automatically.
// When dfs() calls itself for a key, it goes DEEP into that chain first
// before returning to try the next key in the previous room's loop.
// In Keys & Rooms: enters room 0, immediately follows key[0] as far as
// possible (depth-first), then backtracks to try remaining keys.
// RISK: stack overflow on very large/deep graphs (recursion depth limit).
class Solution {
public:

    void dfs(int room, vector<vector<int>>& rooms, vector<bool>& visited) {

        visited[room] = true;

        for (int key : rooms[room]) {

            if (!visited[key])
                dfs(key, rooms, visited);
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {

        int n = rooms.size();

        vector<bool> visited(n, false);

        dfs(0, rooms, visited);

        for (bool room : visited) {

            if (!room)
                return false;
        }

        return true;
    }
};


// APPROACH 2: Iterative DFS using explicit stack (LIFO)
// Stack is Last-In-First-Out. The most recently pushed room is always
// processed first. This mimics the recursive DFS behavior manually.
// In Keys & Rooms: when we pop room X and find keys, the LAST key pushed
// gets explored next — so we go deep along one branch before others.
// Same traversal ORDER as Approach 1, but avoids recursion overhead
// and stack overflow risk (heap memory is larger).
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();

        vector<bool> seen(n, false);
        stack<int> st;

        seen[0] = true;
        st.push(0);

        while(!st.empty()){
            int node = st.top();
            st.pop();

            for(int i : rooms[node]){
                if(!seen[i]){
                    seen[i] = true;
                    st.push(i);
                }
            }
        }
        for(bool t : seen){
            if(!t) return false;
        }
        return true;

    }
};


// APPROACH 3: BFS using queue (FIFO)
// Queue is First-In-First-Out. Rooms are processed in the order they
// are discovered — like spreading outward layer by layer.
// In Keys & Rooms: from room 0, ALL directly reachable rooms via its
// keys are enqueued and visited first. Only after all "1-hop" rooms
// are processed do we visit "2-hop" rooms, and so on.
// KEY DIFFERENCE from Stack: BFS explores WIDE (all neighbors at the
// current level) before going deeper. DFS goes DEEP down one path
// first. Both solve the problem correctly (reachability is the same),
// but the visitation ORDER differs. BFS also guarantees shortest path
// in terms of number of keys/edges (not relevant for this problem).
class Solution {
public:
    bool vis[1005];
    void bfs(int src,vector<vector<int>>& rooms)
    {
        queue<int> q;
        q.push(src);
        vis[src] = true;
        while(!q.empty())
        {
            int par = q.front();
            q.pop();
            for(int child : rooms[par])
            {
                if(!vis[child])
                {
                    q.push(child);
                    vis[child] = true;
                }
            }
        }
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        memset(vis,false,sizeof(vis));
        int n = rooms.size();
        bfs(0,rooms);
        for(int i=0;i<n;i++)
            if(vis[i]==false)
                return false;
        return true;
    }
};
int main(){
    return 0;
}
