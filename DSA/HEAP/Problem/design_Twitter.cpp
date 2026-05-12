#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Twitter {
private:
    // instalize all the variable and data structure for this
    int timeStamp; // this keep track of tweets by time

    // userId -> list of {timestamp , tweetId}
    unordered_map<int, vector<pair<int, int>>> userTweets;

    // userId -> set of followees
    unordered_map<int, unordered_set<int>> followMap;

public:
    Twitter() { timeStamp = 0; }

    void postTweet(int userId, int tweetId) {
        userTweets[userId].push_back({timeStamp++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> result; // to store the final 10 top news

        // Max heap: {time, tweetId, userId, index}
        priority_queue<vector<int>>
            maxheap; // give the top tweets according to the timestamp

        // get all the users of the userId and also ensure follow themselves
        followMap[userId].insert(userId);

        // Push latest tweet of each followed user
        for (int user : followMap[userId]) {
            if (userTweets.count(user) && !userTweets[user].empty()) {
                // here user -> list of {timestamp , tweetId}
                // so idx is index in the usertweetes where here we takes the
                // last index one
                int idx = userTweets[user].size() - 1;
                auto& tweet = userTweets[user][idx];
                maxheap.push({tweet.first, tweet.second, user, idx});
            }
        }

        // Get top 10 tweets
        while (!maxheap.empty() && result.size() < 10) {
            auto top = maxheap.top();
            maxheap.pop();

            int time = top[0];
            int tweetId = top[1];
            int user = top[2];
            int idx = top[3];

            result.push_back(tweetId);

            // Push next older tweet of same user
            if (idx > 0) {
                auto& nextTweet = userTweets[user][idx - 1];
                maxheap.push(
                    {nextTweet.first, nextTweet.second, user, idx - 1});
            }
        }

        return result;
    }

    void follow(int followerId, int followeeId) {
        followMap[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        if (followMap.count(followerId)) {
            followMap[followerId].erase(followeeId);
        }
    }
};




int main(){
    Twitter twitter;
    twitter.postTweet(1, 5); // User 1 posts a tweet (id = 5).
    vector<int> feed1 = twitter.getNewsFeed(1); // User 1's news feed should return a list with tweet id -> [5].
    cout << "User 1's news feed: ";
    for (int id : feed1) {
        cout << id << " ";
    }
    cout << endl;
    twitter.follow(1, 2); // User 1 follows user 2.
    twitter.postTweet(2, 6); // User 2 posts a tweet (id = 6).
    vector<int> feed2 = twitter.getNewsFeed(1); // User 1's news feed should return a list with tweet ids -> [6, 5].
    cout << "User 1's news feed after following user 2: ";
    for (int id : feed2) {
        cout << id << " ";
    }
    cout << endl;
    twitter.unfollow(1, 2); // User 1 unfollows user 2.
    vector<int> feed3 = twitter.getNewsFeed(1); // User 1's
    // news feed should return a list with tweet id -> [5], since user 1 unfollowed user 2.
    cout << "User 1's news feed after unfollowing user 2: ";
    for (int id : feed3) {
        cout << id << " ";
    }
    cout << endl;
    
    return 0;
}