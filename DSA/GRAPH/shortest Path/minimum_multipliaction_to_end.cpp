#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minSteps(vector<int>& arr, int start, int end) {
        /*
            Algorithm: Minimum Multiplications to Reach End

            We can think of this problem as a graph shortest path problem.

            Node:
            - Every number from 0 to 999 is treated as one node.
            - We only keep numbers from 0 to 999 because every new number is:
                  (current_number * arr[i]) % 1000

            Edge:
            - From one number, we can go to another number by multiplying it
              with any value from arr and taking modulo 1000.
            - Every multiplication counts as exactly 1 step.

            Goal:
            - Find the minimum number of multiplications needed to reach end
              from start.

            Why this works like Dijkstra:
            - dist[num] stores the minimum steps needed to reach num.
            - We relax neighbours just like Dijkstra:
                  if newstep < dist[newnum], update dist[newnum].

            Why normal queue is used instead of priority_queue:
            - In normal Dijkstra, edge weights can be different, so we need
              a priority_queue to always process the smallest distance first.
            - Here every edge has the same weight = 1 multiplication.
            - When all edges have equal weight, BFS using a normal queue
              already processes nodes level by level:
                  step 0, then step 1, then step 2, and so on.
            - So priority_queue is not needed.

            Why we return inside the loop:
                if(newnum == end) return dist[newnum];

            - Because BFS explores by increasing number of steps.
            - The first time we update end, that is the minimum possible step.
            - Returning immediately saves extra work.
            - We do not need to wait until the last return after the loop.

            If end is never reached, then the queue becomes empty and we return -1.

            Time Complexity: O(1000 * arr.size())
            Space Complexity: O(1000)
        */
        
        // If start is already equal to end, no multiplication is needed.
        if( start == end) return 0;

        int n = arr.size();
        
        // dist[x] stores the minimum number of steps needed to reach number x.
        // There are only 1000 possible numbers: 0 to 999.
        vector<int>dist(1000 , INT_MAX);
        
        // Queue stores {steps taken so far, current number}.
        // Normal queue works because every multiplication has cost 1.
        queue<pair<int , int>> q;
        
        //put the start and 0th step as the inital configuraion 
        q.push({0 , start});
        dist[start] = 0;
        
        //now g throught the all the element in the quque 
        while( !q.empty()){
            auto it = q.front();
            q.pop();
            int step = it.first;
            int num = it.second;
            
            // If this queue entry is old and we already reached num
            // in fewer steps, skip it.
            if( dist[num] < step)continue;
            
            // Try multiplying current number with every value in arr.
            for( int & it : arr){

                // This creates the next node in the graph.
                int newnum = ( num * it) % 1000;

                // Each multiplication increases the step count by 1.
                int newstep = step + 1;
                
                // Relaxation condition:
                // If we found a smaller number of steps to reach newnum,
                // update its distance.
                if(newstep  < dist[newnum]){
                    dist[newnum] = newstep;
                    
                    //now return we get the end as the newnum then reutrn and end the this loop 
                    //ottherwise this will go till end 
                    // This early return is safe because BFS reaches nodes
                    // in increasing step order when every edge weight is 1.
                    
                    if( newnum == end) return dist[newnum];
                    
                    // Push this new number so its neighbours can be explored.
                    q.push({dist[newnum] , newnum});
                }
            }
        }
        
        // If the queue is empty and end was not reached, it is impossible.
        return -1;
    }
};

int main(){
    Solution s;
    vector<int> arr = {2, 5, 7};
    int start = 3, end = 30;
    int ans = s.minSteps(arr, start, end);
    cout << "Minimum multiplications needed to reach " << end << " from " << start << " is: " << ans << "\n";
    
    return 0;
}
