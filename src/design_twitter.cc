/**************************************************************************************************/
If Use 1 follows User 2, and User 2 follows User 3. User 1 will only see the tweets
by himself and tweets by User 2. User 1 will not see tweets from User 3.

Table tweets                Table following:
--------------------        --------------------
User Id |  Tweet Id         Follower | Followee
--------------------        -------------------
 u1     | {t1,t2,t3}        u1       | {u2, u3}
 u2     | {t3,t4}a          u3       | {u1}
--------------------        --------------------
**************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Twitter {
private:
    int timestamp = 0;
    unordered_map<int, vector<pair<int, int>>> tweets; // userId -> list of {timestamp, tweetId}
    unordered_map<int, unordered_set<int>> following;  // followerId -> set of followeeIds

public:
    Twitter() {}
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timestamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        // Min-heap to maintain at most 10 most recent tweets: {timestamp, tweetId}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        // Lambda to fetch up to 10 latest tweets from a specific user and add them to the heap
        auto collectTweets = [&](int targetUser) {
            if (!tweets.count(targetUser)) return;
            
            const auto& userTweets = tweets[targetUser];
            int n = userTweets.size();
            // Iterate backwards over the last 10 tweets
            for (int i = n - 1; i >= max(0, n - 10); --i) {
                minHeap.push(userTweets[i]);
                if (minHeap.size() > 10) minHeap.pop(); // Evict the oldest element
            }
        };

        // 1. Collect tweets for the user themselves
        collectTweets(userId);

        // 2. Collect tweets for all directly followed users
        if (following.count(userId)) {
            for (int followeeId : following[userId]) {
                collectTweets(followeeId);
            }
        }
        
        // 3. Extract items from heap and reverse to achieve newest-to-oldest order
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) following[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if (following.count(followerId)) following[followerId].erase(followeeId);
    }
};

int main() {
    Twitter twitter;
    twitter.postTweet(1, 10);
    twitter.postTweet(2, 20);
    
    auto print = [](int uid, vector<int> feed) {
        cout << "User " << uid << "'s Feed: [";
        for (size_t i = 0; i < feed.size(); ++i) cout << feed[i] << (i < feed.size() - 1 ? ", " : "");
        cout << "]\n";
    };

    print(1, twitter.getNewsFeed(1)); 
    twitter.follow(1, 2);
    print(1, twitter.getNewsFeed(1)); 
    twitter.unfollow(1, 2);
    print(1, twitter.getNewsFeed(1)); 
    return 0;
}

