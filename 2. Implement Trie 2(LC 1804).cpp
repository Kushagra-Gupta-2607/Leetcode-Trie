// Probelem Link:
// Leetcode 1804. Implement Trie II (Prefix Tree): https://leetcode.com/problems/implement-trie-ii-prefix-tree/

class TrieNode{
public:
    TrieNode *links[26] = {NULL};
    int cntEndsWith = 0;
    int cntPrefix = 0;
    
    bool containsKey(char ch){
        return links[ch-'a'] != NULL;
    }
    void put(char ch){
        links[ch-'a'] = new TrieNode();
    }
    TrieNode *get(char ch){
        return links[ch-'a'];
    }
    
    void increaseEnd(){
        cntEndsWith++;
    }
    void increasePrefix(){
        cntPrefix++;
    }
    void deleteEnd(){
        cntEndsWith--;
    }
    void deletePrefix(){
        cntPrefix--;
    }
    
    int getEnd(){
        return cntEndsWith;
    }
    int getPrefix(){
        return cntPrefix;
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
            if(node->containsKey(ch) == false){
                node->put(ch);
            }
            node = node->get(ch);
            node->increasePrefix();
        }
        node->increaseEnd();
    }
    
    int countWordsEqualTo(string& word) {
        TrieNode *node = root;
        for(char ch: word){
            if(node->containsKey(ch))
                node = node->get(ch);
            else return 0;
        }
        return node->getEnd();
    }
    
    int countWordsStartingWith(string& word) {
        TrieNode *node = root;
        for(char ch: word){
            if(node->containsKey(ch))
                node = node->get(ch);
            else return 0;
        }
        return node->getPrefix();
    }
    
    void erase(string& word){
        TrieNode *node = root;
        for(char ch: word){
            if(node->containsKey(ch)){
                node = node->get(ch);
                node->deletePrefix();
            }
            else return;
        }
        node->deleteEnd();
    }
};
