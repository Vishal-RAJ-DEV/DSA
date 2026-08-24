/*
================================================================================
              GET WATCHED VIDEOS BY YOUR FRIENDS - EXPLANATION
================================================================================

PROBLEM:
--------
There are n people with IDs from 0 to n-1.
Each person has watched some videos (given in watchedVideos array).
There is an undirected friendship graph.

Given:
  - watchedVideos[i] = list of videos watched by person i
  - friends[i] = list of friends of person i
  - id = the person whose friends' videos we want
  - level = we want videos from people at EXACTLY this level

Return: List of videos watched by people at 'level' distance from 'id'
        Sorted by frequency (ascending), then alphabetically

EXAMPLE:
--------
  watchedVideos = [["A","B"], ["C"], ["B","D"], []]
  friends = [[1,2], [0,3], [0,3], [1,2]]
  id = 0, level = 1
  
  Friendship Graph:
    Person 0 is friends with: 1, 2
    Person 1 is friends with: 0, 3
    Person 2 is friends with: 0, 3
    Person 3 is friends with: 1, 2
  
  Level 0: Person 0 (starting point)
  Level 1: Persons 1, 2 (direct friends of 0)
  Level 2: Person 3 (friend of friend, not direct friend of 0)
  
  People at level 1: [1, 2]
  Videos by person 1: ["C"]
  Videos by person 2: ["B"]
  
  Frequencies: {"C": 1, "B": 1}
  Sorted: ["B", "C"] (alphabetical since same frequency)


================================================================================
                    LEVEL LOGIC - HOW LEVELS WORK
================================================================================

WHAT IS LEVEL?
--------------
  Level = number of edges (hops) from the starting person
  
  Level 0: The person themselves (0 hops)
  Level 1: Direct friends (1 hop)
  Level 2: Friends of friends (2 hops)
  Level k: k hops away

VISUAL:
-------
  Person 0 (Level 0)
      |
      +--- Person 1 (Level 1)
      |        |
      |        +--- Person 3 (Level 2)
      |
      +--- Person 2 (Level 1)
               |
               +--- Person 3 (Level 2)
  
  Level 1 means: exactly 1 hop from person 0
  Level 2 means: exactly 2 hops from person 0
  
  IMPORTANT: Level 2 does NOT include Level 1 people!
             We want EXACTLY level, not <= level

BFS LEVEL-BY-LEVEL:
-------------------
  BFS naturally explores level by level:
  
  Step 0: Queue = [0]              -> Level 0
  Step 1: Queue = [1, 2]           -> Level 1
  Step 2: Queue = [3]              -> Level 2
  
  Each step = one more hop = one more level


================================================================================
                    HOW CODE WORKS - STEP BY STEP
================================================================================

PART 1: BFS TO FIND PEOPLE AT EXACT LEVEL
-------------------------------------------
  
  1. Start BFS from person `id`
  2. Use level-by-level processing:
     - Process all people at current level
     - Add their unvisited friends to queue
     - Increment currentLevel
  3. Stop when currentLevel == level
  4. Queue now contains people at EXACTLY `level`
  
  Key Insight:
  -----------
  After the while loop finishes, the queue contains
  people at exactly `level` distance.
  
  Why?
  -----
  The loop stops when currentLevel reaches level.
  At that point, queue has people we added in the PREVIOUS iteration,
  which are exactly at `level` distance.


PART 2: COUNT VIDEO FREQUENCIES
---------------------------------
  
  After BFS, queue has people at level `level`.
  
  Process each person in queue:
  - Get their watched videos
  - Count frequency of each video
  
  Example:
    Queue has persons [1, 2]
    Person 1 watched ["C"]
    Person 2 watched ["B"]
    
    freq["C"] = 1
    freq["B"] = 1


PART 3: SORT AND CREATE ANSWER
--------------------------------
  
  1. Convert freq map to vector of pairs
  2. Sort by:
     - Frequency (ascending) - less frequent first
     - Alphabetical order - if same frequency
  3. Extract video names from sorted pairs
  4. Return as answer


================================================================================
                    DETAILED CODE WALKTHROUGH
================================================================================

STEP 1: BFS SETUP
------------------
  queue<int> q;
  vector<bool> visited(n, false);
  
  q.push(id);           // Start from given person
  visited[id] = true;   // Mark as visited
  
  currentLevel = 0;     // Start at level 0


STEP 2: BFS LEVEL-BY-LEVEL
----------------------------
  while (!q.empty() && currentLevel < level) {
      
      int size = q.size();   // People at current level
      
      // Process ALL people at current level
      while (size--) {
          
          int person = q.front();
          q.pop();
          
          // Add all unvisited friends
          for (int friendId : friends[person]) {
              if (!visited[friendId]) {
                  visited[friendId] = true;
                  q.push(friendId);
              }
          }
      }
      
      currentLevel++;   // Move to next level
  }
  
  // When loop ends:
  // - currentLevel == level
  // - Queue contains people at exactly `level`


STEP 3: COUNT VIDEO FREQUENCIES
---------------------------------
  unordered_map<string, int> freq;
  
  // Process all people at level `level`
  while (!q.empty()) {
      
      int person = q.front();
      q.pop();
      
      // Count each video watched by this person
      for (string video : watchedVideos[person]) {
          freq[video]++;
      }
  }
  
  // freq now contains: {video_name: count}


STEP 4: SORT VIDEOS
---------------------
  vector<pair<string, int>> videos;
  
  // Convert map to vector for sorting
  for (auto& it : freq) {
      videos.push_back({it.first, it.second});
  }
  
  // Sort by:
  // 1. Frequency (ascending) - less frequent first
  // 2. Alphabetical order - if same frequency
  sort(videos.begin(), videos.end(),
      [](auto& a, auto& b) {
          if (a.second != b.second) {
              return a.second < b.second;  // Frequency ascending
          }
          return a.first < b.first;        // Alphabetical
      });


STEP 5: CREATE ANSWER
-----------------------
  vector<string> ans;
  
  // Extract video names from sorted pairs
  for (auto& video : videos) {
      ans.push_back(video.first);
  }
  
  return ans;


================================================================================
                    VISUAL EXAMPLE
================================================================================

  watchedVideos = [["A","B"], ["C"], ["B","D"], ["E"]]
  friends = [[1,2], [0,3], [0,3], [1,2]]
  id = 0, level = 2
  
  Friendship Graph:
    0 --- 1
    |     |
    2 --- 3
  
  BFS from person 0:
  ==================
  
  Level 0:
    Queue: [0]
    Processing 0: add friends 1, 2
  
  Level 1:
    Queue: [1, 2]
    Processing 1: add friend 3 (0 already visited)
    Processing 2: add friend 3 (already added)
  
  Level 2:
    Queue: [3]
    currentLevel (2) == level (2) -> STOP!
  
  Queue contains: [3] (person at level 2)
  
  Count videos:
  ==============
    Person 3 watched: ["E"]
    freq["E"] = 1
  
  Sort:
  ======
    Only one video, no sorting needed
  
  Answer: ["E"]


================================================================================
                    WHY BFS STOPS AT EXACT LEVEL
================================================================================

  The while loop condition is:
    while (!q.empty() && currentLevel < level)
  
  This ensures:
  - We STOP when currentLevel reaches level
  - Queue at that point has people at EXACTLY `level`
  
  Why not process further?
  -----------------------
  We only want people at EXACTLY `level`, not less or more.
  
  Example: level = 2
  - Level 0: person 0 (not wanted)
  - Level 1: persons 1, 2 (not wanted)
  - Level 2: person 3 (WANTED!)
  - Level 3: ... (not wanted)
  
  The loop stops when currentLevel = 2.
  Queue has person 3 (added when currentLevel was 1).


================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<string> watchedVideosByFriends(
        vector<vector<string>>& watchedVideos,
        vector<vector<int>>& friends,
        int id,
        int level
    ) {
        
        int n = friends.size();
        
        // ================================================================
        // STEP 1: BFS TO FIND PEOPLE AT EXACTLY 'level' DISTANCE
        // ================================================================
        // Use BFS to explore friends level by level
        // Stop when we reach the target level
        // Queue will contain people at exactly 'level' distance
        //
        queue<int> q;
        vector<bool> visited(n, false);
        
        q.push(id);           // Start from given person
        visited[id] = true;   // Mark as visited
        
        int currentLevel = 0;  // Track current BFS level
        
        // BFS LOOP: Process level by level
        // Stop when currentLevel reaches target 'level'
        //
        while (!q.empty() && currentLevel < level) {
            
            // Get number of people at current level
            // Process ALL of them before moving to next level
            //
            int size = q.size();
            
            // Process all people at current level
            while (size--) {
                
                int person = q.front();
                q.pop();
                
                // Add all unvisited friends to queue
                // These friends will be at currentLevel + 1
                //
                for (int friendId : friends[person]) {
                    
                    if (!visited[friendId]) {
                        visited[friendId] = true;
                        q.push(friendId);
                    }
                }
            }
            
            // Move to next level
            currentLevel++;
        }
        
        // When loop ends:
        // - currentLevel == level
        // - Queue contains people at EXACTLY 'level' distance from 'id'
        
        
        // ================================================================
        // STEP 2: COUNT VIDEO FREQUENCIES
        // ================================================================
        // Process all people at level `level`
        // Count how many times each video was watched
        //
        unordered_map<string, int> freq;
        
        while (!q.empty()) {
            
            int person = q.front();
            q.pop();
            
            // Count each video watched by this person
            for (string video : watchedVideos[person]) {
                freq[video]++;
            }
        }
        
        
        // ================================================================
        // STEP 3: CONVERT MAP TO VECTOR FOR SORTING
        // ================================================================
        // We need to sort videos, so convert map to vector of pairs
        //
        vector<pair<string, int>> videos;
        
        for (auto& it : freq) {
            videos.push_back({it.first, it.second});
        }
        
        
        // ================================================================
        // STEP 4: SORT VIDEOS
        // ================================================================
        // Sort by:
        //   1. Frequency (ascending) - less frequent videos come first
        //   2. Alphabetical order - if two videos have same frequency
        //
        sort(videos.begin(), videos.end(),
            [](auto& a, auto& b) {
                
                // First compare by frequency (ascending)
                if (a.second != b.second) {
                    return a.second < b.second;
                }
                
                // Same frequency -> compare alphabetically
                return a.first < b.first;
            });
        
        
        // ================================================================
        // STEP 5: CREATE ANSWER
        // ================================================================
        // Extract video names from sorted pairs
        //
        vector<string> ans;
        
        for (auto& video : videos) {
            ans.push_back(video.first);
        }
        
        return ans;
    }
};


// ============================================================================
//                           MAIN FUNCTION
// ============================================================================
//
// TEST CASE:
// ----------
// watchedVideos = [["A","B"], ["C"], ["B","D"], ["E"]]
// friends = [[1,2], [0,3], [0,3], [1,2]]
// id = 0, level = 2
//
// Friendship Graph:
//   0 --- 1
//   |     |
//   2 --- 3
//
// BFS from person 0:
//   Level 0: [0]
//   Level 1: [1, 2]
//   Level 2: [3]
//
// People at level 2: [3]
// Videos by person 3: ["E"]
// Answer: ["E"]
//
// ============================================================================
int main(){
    return 0;
}
