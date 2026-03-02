#include <bits/stdc++.h>
using namespace std;
/*
There are a total of n tasks you have to pick, labeled from 0 to n-1. Some tasks may have prerequisites tasks, for example, to pick task 0 you have to first finish tasks 1, which is expressed as a pair: [0, 1]
Given the total number of tasks and a list of prerequisite pairs, is it possible for you to finish all tasks?

Example 1:
Input: N = 4, P = 3,  array[] = {{1,0},{2,1},{3,2}}
Output: Yes
Explanation: It is possible to finish all the tasks in the order : 3 2 1 0.
First, we will finish task 3. Then we will finish task 2, task 1, and task 0. 
Input: N = 4, P = 4,  array[] = {{1,2},{4,3},{2,4},{4,1}}
Output: No
Explanation: It is impossible to finish all the tasks. Let’s analyze the pairs:
For pair {1, 2} -> we need to finish task 1 first and then task 2. (order : 1 2).
For pair{4, 3} -> we need to finish task 4 first and then task 3. (order: 4 3).
For pair {2, 4} -> we need to finish task 2 first and then task 4. (order: 1 2 4 3).
But for pair {4, 1} -> we need to finish task 4 first and then task 1 but this pair contradicts the previous pair. So, it is not possible to finish all the tasks. 
*/


//this is the course schedule 1 
// here we only return true if we can finish all the courses and return false if we cannot finish all the courses
//time complexity: O(V + E) as we are traversing all the nodes and edges of the graph
//space complexity: O(V) for the in-degree array and O(V) for the queue
class Solution {
public:
    // Function to verify if all courses can be finished
    bool canFinish(int numCourses, 
                   vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> adj(numCourses);
        // Build in-degree array
        vector<int> inDegree(numCourses, 0);

        // Fill adjacency and in-degree
        //if the given is {a, b} then we need to finish course b first and then course a so we will add an edge from b to a in the graph and we will increase the in-degree of a by 1
        for (auto& pre : prerequisites) {
            int a = pre[0], b = pre[1];
            adj[b].push_back(a);
            inDegree[a]++; // a has the incooming edge from b so we will increase the in-degree of a by 1
        }

        // Initialize queue with zero in-degree nodes
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Count processed nodes
        int count = 0;

        // Process queue
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;

            // Reduce in-degree of neighbors
            for (int nei : adj[node]) {
                inDegree[nei]--;
                if (inDegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        // Return true if all nodes processed
        return count == numCourses;
    }
};


//this is the course schedule 2
// here we return the order of courses if we can finish all the courses and return an empty array if we cannot finish all the courses
//time complexity: O(V + E) as we are traversing all the nodes and edges of the graph
//space complexity: O(V) for the visited array and O(V) for the recursive stack space in the worst case when there is a cycle in the graph
class Solution1 {
public:
    // Function to find ordering of courses
    vector<int> findOrder(int numCourses, 
                          vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> adj(numCourses);
        // Build in-degree array
        vector<int> inDegree(numCourses, 0);

        // Fill adjacency and in-degree
        for (auto& pre : prerequisites) {
            int a = pre[0], b = pre[1];
            adj[b].push_back(a);
            inDegree[a]++;
        }

        // Initialize queue with zero in-degree nodes
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Create result list that stores the all the courses in the order they can be taken
        vector<int> order;

        // Process queue
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);

            // Reduce in-degree of neighbors
            for (int nei : adj[node]) {
                inDegree[nei]--;
                if (inDegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        // Return order if valid, else empty
        if ((int)order.size() == numCourses) {
            return order;
        }
        return {};
    }
};


int main() {
    Solution sol;
    vector<vector<int>> prerequisites = {{1, 0}, {0, 1}};
    int numCourses = 2;
    cout << (sol.canFinish(numCourses, prerequisites) 
             ? "true" : "false");
    return 0;
}