// Problem Link:
// Leetcode 421. Maximum XOR of Two Numbers in an Array: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/


// TC => O(n*32) + O(n*32)
class TrieNode{
    public:
    TrieNode *links[2] = {NULL};
    
    bool containsKey(int bit){
        return links[bit] != NULL;
    }
    void put(int bit){
        links[bit] = new TrieNode();
    }
    TrieNode* get(int bit){
        return links[bit];
    }
};

class Trie{
    private: TrieNode *root;
    public:
    Trie(){
        root = new TrieNode();
    }
    
    void insert(int num){
        TrieNode *node = root;
        for(int i = 31; i>=0; i--){
            int bit = (num >> i) & 1;
            if(node->containsKey(bit) == false){
                node->put(bit);
            }
            node = node->get(bit);
        }
    }
    
    int getMax(int num){
        TrieNode *node = root;
        int maxNum = 0;
        for(int i = 31; i>=0; i--){
            int bit = (num >> i) & 1;
            if(node->containsKey(1-bit)){
                maxNum += (1 << i);
                bit = 1 - bit;
            }
            node = node->get(bit);
        }
        return maxNum;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie virtualTrie;
        for(int num: nums){
            virtualTrie.insert(num);
        }
        int ans = 0;
        for(int num: nums){
            ans = max(ans, virtualTrie.getMax(num));
        }
        return ans;
    }
};
