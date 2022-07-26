// Problem Link:
// Leetcode 208. Implement Trie (Prefix Tree): https://leetcode.com/problems/implement-trie-prefix-tree/

class TrieNode{
public:
    TrieNode *links[26] = {NULL};
    bool end = false;
    
    bool containsKey(char ch){
        return links[ch-'a'] != NULL;
    }
    void put(char ch){
        links[ch-'a'] = new TrieNode();
    }
    
    TrieNode *get(char ch){
        return links[ch-'a'];
    }
};

class Trie {
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode *node = root;
        for(char ch: word){
            if(node->containsKey(ch) == false){ // checking whethere the character exists in the node or not
                node->put(ch);                  // inserting the required character in node
            }
            node = node->get(ch);               // getting the required character
        }
        node->end = true;                      // Marking the node of the last character as false
    }
    
    bool search(string word) {
        TrieNode *node = root;
        for(char ch: word){
            if(node->containsKey(ch))
                node = node->get(ch);
            else return false;
        }
        return node->end == true;
    }
    
    bool startsWith(string prefix) {
        TrieNode *node = root;
        for(char ch: prefix){
            if(node->containsKey(ch))
                node = node->links[ch-'a'];
            else return false;
        }
        return true;
    }
};
