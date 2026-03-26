/*Example 1:
Input:
  
N = 4, Jobs = {(1, 4, 20), (2, 1, 10), (3, 1, 40), (4, 1, 30)}  
Output:
 2 60  
Explanation:
  
- The 3rd job with a deadline of 1 is performed during the first unit of time.  
- The 1st job is performed during the second unit of time as its deadline is 4.  
Profit = 40 + 20 = 60.  
So, the result is 2 jobs with a total profit of 60.
*/
/*Key Greedy Insight
->Always pick highest profit first
->Place it as late as possible
->This ensures:
->More jobs fit
->Maximum profit is achieved

⚡ Interview One-Liner
"Sort jobs by profit descending, then assign each job to the latest available slot before its deadline."
*/

#include<bits/stdc++.h>

using namespace std;

// A structure to represent a job 
struct Job {
   // Job Id
   int id; 
   // Deadline of job
   int dead;
   // Profit if job is completed before or on the deadline 
   int profit; 
};

class Solution {
   public:
      // Comparator function to sort jobs in decreasing order of profit
      bool static comparison(Job a, Job b) {
          // Sort by profit in descending order
         return (a.profit > b.profit); 
      }

   // Function to find the maximum profit and the number of jobs done
   pair < int, int > JobScheduling(Job arr[], int n) {

      // Sort the jobs based on decreasing profit
      //now we will sort the jobs in decreasing order of profit so that we can try to schedule the most profitable jobs first and then move to the less profitable jobs and so on
      sort(arr, arr + n, comparison);

      // Find the maximum deadline among all jobs
      //maximum deadline will be the maximum time slot we need to consider for scheduling jobs
      //jobs more than the maximum deadline will not be considered because they cannot be scheduled within their deadlines
      int maxi = arr[0].dead;
      for (int i = 1; i < n; i++) {
        // Get the latest deadline
        maxi = max(maxi, arr[i].dead);  
      }

      // Initialize the slot array to track which time slots are taken
      int slot[maxi + 1];
      for (int i = 0; i <= maxi; i++)
        // Mark all slots as unoccupied initially
        slot[i] = -1;  

      int countJobs = 0, jobProfit = 0;

      //at first we have the jobs with the max profit and we will try to schedule them first and then move to the less profitable jobs and so on
      // Iterate through all jobs to find the best possible schedule
      for (int i = 0; i < n; i++) {
         // Find a slot for the current job (starting from its deadline)

         //place job on the its deadline if it is free, otherwise check for earlier slots until we find a free slot or we reach the beginning of the slot array
         for (int j = arr[i].dead; j > 0; j--) {
            // If the slot is available
            if (slot[j] == -1) {  
                // Assign the job to the slot
                slot[j] = i;  
                // Increment the number of jobs done
                countJobs++;  
                // Add the profit of the job
                jobProfit += arr[i].profit;  
               break;
            }
         }
      }

      // Return the number of jobs done and the total profit
      return make_pair(countJobs, jobProfit);
   }
};

int main() {
   // Driver code
   int n = 4;
   // Define jobs with id, deadline, and profit
   Job arr[n] = {{1,4,20},{2,1,10},{3,2,40},{4,2,30}};

   Solution ob;
   // Function call to find the number of jobs done and total profit
   pair < int, int > ans = ob.JobScheduling(arr, n);

   // Output the number of jobs and the total profit
   cout << ans.first << " " << ans.second << endl;

   return 0;
}
//in the outer loop we are iterating through the jobs from the most profitable to least profitable 
//for each job , we place it on the their max deadline if it is free , otherwise palce in the slot before the deadline if it is free and so on until we find a free slot or we reach the beginning of the slot array 
//-> this is done in the inner loop by iterating from the job's deadline to 1 and checking if the slot is free or not ( to 1 because we cannot place a job in slot 0 as time starts from 1)
//if we have two jobs with the same profit , we can place any of them first as they will both give the same profit and we will try to place the most profitable jobs first to maximize the total profit