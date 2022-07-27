// Problem Link:
// Leetcode 1858. Longest Word With All Prefixes: https://leetcode.com/problems/longest-word-with-all-prefixes/

class TrieNode{
public:
    TrieNode *links[26] = {NULL};
    bool flag = false;
    
    bool containsKey(char ch){
        return links[ch-'a'] != NULL;
    }
    void put(char ch){
        links[ch-'a'] = new TrieNode();
    }
    TrieNode* get(char ch){
        return links[ch-'a'];
    }
    void setEnd(){
        flag = true;
    }
};

class Trie{
    private: TrieNode *root = new TrieNode();
    public:
    void insert(string word){
        TrieNode *node = root;
        for(char ch: word){
            if(node->containsKey(ch) == false){
                node->put(ch);
            }
            node = node->get(ch);
        }
        node->setEnd();
    }
    
    bool checkIfPrefixExist(string word){
        TrieNode *node = root;
        bool flag = true;
        for(char ch: word){
            if(node->containsKey(ch) == false || node->get(ch)->flag == false){
                return false;
            }
            else node = node->get(ch);
        }
        return true;
    }
};

string completeString(int n, vector<string> &a){
    // Write your code here.
    Trie* virtualTrie = new Trie();
    for(string s: a){
        virtualTrie->insert(s);
    }
    string ans;
    for(string s: a){
        if(virtualTrie->checkIfPrefixExist(s)){
            if(s.size()>ans.size() || s.size() == ans.size() && s<ans)
                ans = s;
        }
    }
    delete virtualTrie;
    return ans == "" ? "None" : ans;
}
