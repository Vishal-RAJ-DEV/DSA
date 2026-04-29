#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        //first store the frequecy of the task in the hashmap 
        //letter will store as the num value ch - 'A' like this 
        vector<int>mpp( 26 , 0 );
        for( char &ch : tasks){
            mpp[ch - 'A']++;
        }
        //now store all in the max heap for at top max frequency task will there 
        priority_queue<int>pq;
        for( int i = 0 ; i < 26 ; i++){
            if(mpp[i] > 0){
                pq.push(mpp[i]);
            }

        }
        int time = 0 ;
        //now traverse in the prioriy queue and schedule the task by poping it 
        while(!pq.empty()){
            vector<int>temp;//this temp will store the current task performed 
            
            for( int i =1 ; i <= n + 1 ; i++){
                if( !pq.empty()){
                    int freq = pq.top();
                    pq.pop();
                    freq--; //decrese the frequecy of that task when poped(it use in one time)
                    temp.push_back(freq);
                }
            }

            //now if the temp task frequency is still greater than 0 then push in the pq
            for( int &f : temp){
                if( f > 0){
                    pq.push(f);
                }
            }

            //now calcaulete the time taken by the current task 
            //->if the pq is empty then only remaming task will performed in the temp
            if( pq.empty()){
                time += temp.size();
            }else{
                //otherwise the n + 1 time will take along with the idle time
                // n for the gap after first task and 1 for current taks 
                //like AB_|AB_  A is 1st task and n is other task with idle time 
                time += n + 1;
            }
        }

        return time;
    }
};


int main(){
    Solution sol;
    vector<char>tasks = {'A','A','A','B','B','B'};
    int n = 2;
    cout << sol.leastInterval(tasks, n) << endl;

    return 0;
}

/*
⚡ Algorithm: Task Scheduler (Heap Approach)
🔹 Step 1: Count Frequency
Create an array of size 26
For each task:
Increment freq[task - 'A']

🔹 Step 2: Build Max Heap
Insert all non-zero frequencies into a max heap
Purpose: always pick the task with highest remaining count

🔹 Step 3: Initialize Time
time = 0

🔹 Step 4: Process in Cycles (n + 1)
While heap is not empty:
➤ Create a temporary list
temp = [] → stores remaining frequencies after execution

➤ Run a cycle of size (n + 1)
For i = 1 to n + 1:
If heap not empty:
Pop top frequency
Decrease it by 1 (task executed)
Store updated value in temp

➤ Reinsert Remaining Tasks
For each value in temp:
If > 0 → push back into heap

➤ Update Time
If heap is empty:
time += temp.size() (no idle needed)
Else:
time += (n + 1) (full cycle including idle)

🔹 Step 5: Return Result
Return time

🧠 One-Line Memory Trick
👉 “Pick max tasks → run (n+1) cycle → reduce → reinsert → repeat”
*/