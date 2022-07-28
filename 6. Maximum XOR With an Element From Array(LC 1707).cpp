// Problem Link:
// Leetcode 1707. Maximum XOR With an Element From Array: https://leetcode.com/problems/maximum-xor-with-an-element-from-array/


// TC => O( N * logN + Q * logQ + (N + Q) * 32) = O( K * logK) where K = max(N, Q)
class TrieNode{
    public:
    TrieNode *links[2] = {NULL};
    
    bool containsKey(int bit){
        return links[bit] != NULL;
    }
    void put(int bit){
        links[bit] = new TrieNode();
    }
    TrieNode *get(int bit){
        return links[bit];
    }
};

class Trie{
    private: TrieNode *root = new TrieNode();
    public:
    void insert(int num){
        TrieNode *node = root;
        for(int i = 31; ~i; --i){
            int bit = (num >> i) & 1;
            if(node->containsKey(bit) == false)
                node->put(bit);
            node = node->get(bit);
        }
    }
    
    int getMax(int num){
        TrieNode *node = root;
        int maxNum = 0;
        for(int i = 31; ~i; --i){
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
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), q = queries.size();
        sort(nums.begin(), nums.end()); // O(n*logn)
        vector<vector<int>> v(q);
        vector<int> ans(q);
        for(int i = 0; i<q; i++){
            v[i] = {queries[i][1], queries[i][0], i};
        }
        sort(v.begin(), v.end()); // O(q*logq)
        
        Trie trie;
        int idx = 0;
        // O(q*32 + n*32)
        for(int i = 0; i<q; i++){
            // till we insert all the elements of the array in trie which are less than given query
            while(idx<n && nums[idx]<=v[i][0])
                trie.insert(nums[idx++]);
            // if idx == 0 => this means trie is empty and thus -1 as a result
            // else we check for the max possible xor vapue with the elements present in the trie
            ans[v[i][2]] = idx == 0 ? -1 : trie.getMax(v[i][1]);
        }
        return ans;
    }
};
