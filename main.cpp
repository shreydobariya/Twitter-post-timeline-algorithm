
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "max_heap.h"

class Post {
public:
    int user_id;
    int post_id;
    int timestamp;
    std::string text;

    Post(int user_id, int post_id, int timestamp, const std::string& text)
        : user_id(user_id), post_id(post_id), timestamp(timestamp), text(text) {}

    bool operator<(const Post& other) const {
        return timestamp < other.timestamp; 
    }
    
    bool operator>(const Post& other) const {
        return timestamp > other.timestamp; 
    }
    
    friend std::ostream& operator<< (std::ostream& out, const Post& p) ;
};

std::ostream& operator<< (std::ostream& out, const Post& p) {
    out << p.user_id << "," << p.post_id << "," << p.timestamp << "," << p.text ;
    return out;
}

std::vector<Post> getPLatestPosts(std::vector<std::vector<Post>>& userPosts, int p) {
    std::vector<Post> latestPosts;
    MaxHeap<Post> maxHeap;
    
    // Provide your implementation here
     int n=userPosts.size();
    for (int i = 0; i < n; i++) {
        for (const Post& post : userPosts[i]) {
            maxHeap.insert(post);
        }
    }
    for (int j = 0; j < p; j++) 
    {
        if (!maxHeap.isEmpty()) {
            latestPosts.push_back(maxHeap.extractMax());
        } else {
            break;  
        }
    }
    return latestPosts;
}
    // End of your implementation
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " numUsers numLatestPosts" << std::endl;
        return 1; 
    }

    int numUsers = std::atoi(argv[1]); // Number of users to consider
    int numPosts = std::atoi(argv[2]); // Number of posts to include in the "timeline"
    
    std::vector<std::vector<Post>> userPosts(numUsers); 

    for (int user_id = 0; user_id < numUsers; user_id++) {
        std::string filename = "user" + std::to_string(user_id);
        std::ifstream inputFile(filename);

        if (inputFile.is_open()) {
            std::string line;

            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string token;
                int post_id;
                int timestamp;
                std::string text;

                std::getline(iss, token, ','); // user_id
                std::getline(iss, token, ','); // post_id
                post_id = std::stoi(token);
                std::getline(iss, token, ','); // post_timestamp
                timestamp = std::stoi(token);
                std::getline(iss, text); // post_text

                userPosts[user_id].push_back(Post(user_id, post_id, timestamp, text));
            }

            inputFile.close();
        } else {
            std::cerr << "Error: Unable to open " << filename << std::endl;
            return 1;
        }
    }

    std::vector<Post> latestPosts = getPLatestPosts(userPosts, numPosts); 

    std::cout << "Beginning of the timeline:" << std::endl;
    if (latestPosts.size() == 0) {
        std::cout << "The timeline is empty." << std::endl;
    }
    else {
        for (const Post& p : latestPosts) {
            std::cout << p << std::endl;
        }
    }

    std::cout << "End of the timeline." << std::endl;

    return 0;
}

// Example tests
/*
Test 1 
Command line input: 1 5
Expected output:
Beginning of the timeline:
0,16,1695708735,Post 16 by User 0
0,15,1695707339,Post 15 by User 0
0,14,1695705433,Post 14 by User 0
0,13,1695703484,Post 13 by User 0
0,12,1695700800,Post 12 by User 0
End of the timeline.
*/

/*
Test 2 
Command line input: 2 5
Expected output:
Beginning of the timeline:
1,12,1695709203,Post 12 by User 1
0,16,1695708735,Post 16 by User 0
1,11,1695707608,Post 11 by User 1
0,15,1695707339,Post 15 by User 0
0,14,1695705433,Post 14 by User 0
End of the timeline.
*/

/*
Test 3
Command line input: 3 10
Expected output: 
Beginning of the timeline:
1,12,1695709203,Post 12 by User 1
0,16,1695708735,Post 16 by User 0
1,11,1695707608,Post 11 by User 1
0,15,1695707339,Post 15 by User 0
0,14,1695705433,Post 14 by User 0
1,10,1695704258,Post 10 by User 1
1,9,1695704206,Post 9 by User 1
0,13,1695703484,Post 13 by User 0
2,10,1695702315,Post 10 by User 2
2,9,1695701265,Post 9 by User 2
End of the timeline.
*/

/*
Test 4
Command line input: 5 5
Expected output: 
Beginning of the timeline:
4,17,1695709787,Post 17 by User 4
4,16,1695709480,Post 16 by User 4
1,12,1695709203,Post 12 by User 1
0,16,1695708735,Post 16 by User 0
1,11,1695707608,Post 11 by User 1
End of the timeline.
*/

/*
Test 5
Command line input: 10 10
Expected output: 
Beginning of the timeline:
9,16,1695715599,Post 16 by User 9
9,15,1695714135,Post 15 by User 9
9,14,1695711790,Post 14 by User 9
9,13,1695711133,Post 13 by User 9
9,12,1695710718,Post 12 by User 9
4,17,1695709787,Post 17 by User 4
4,16,1695709480,Post 16 by User 4
1,12,1695709203,Post 12 by User 1
0,16,1695708735,Post 16 by User 0
9,11,1695708208,Post 11 by User 9
End of the timeline.
*/