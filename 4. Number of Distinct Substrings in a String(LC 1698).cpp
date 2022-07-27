// Problem Link:
// Leetcode 1698. Number of Distinct Substrings in a String: https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/

#include<bits/stdc++.h>

// Unordered_Set ( TC -> O(n^2 * log(n)), SC-> O(n^3) )
// 
// int countDistinctSubstrings(string &s)
// {
//     //    Write your code here.
//     unordered_set<string> us;
//     for(int i = 0; i<s.size(); i++){
//         string k;
//         for(int j = i; j<s.size(); j++){
//             k+=s[j];
//             us.insert(k);
//         }
//     }
//     return us.size() + 1;
// }

// Method-2 (Trie)
class TrieNode{
    public:
    TrieNode *links[26] = {NULL};
    
    bool containsKey(char ch){
        return links[ch-'a']  != NULL;
    }
    void put(char ch){
        links[ch-'a'] = new TrieNode();
    }
    TrieNode* get(char ch){
        return links[ch-'a'];
    }
};

class Trie{
    private: TrieNode *root = new TrieNode();
    public:
    int insert(string s){
        TrieNode *node = root;
        int cnt = 0;
        for(char ch: s){
            if(node->containsKey(ch) == false){
                cnt++;
                node->put(ch);
            }
            node = node->get(ch);
        }
        return cnt;
    }
};

int countDistinctSubstrings(string &s)
{
    //    Write your code here.
    Trie virtualTrie;
    int ans = 1;
    for(int i = 0; i<s.size(); i++){
        string curr = s.substr(i);
        ans+= virtualTrie.insert(curr);
    }
    return ans;
}
