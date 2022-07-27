// Problem Description:
// Q. Given an array of numbers and a number 'x'. Find the maximum value of (arr[i] ^ x).

// 1. Insert all the numbers into the trie in the form of bits.
// 2. Take x and find required no. from array where (arr[i]^x) is max.

typedef long long ll;
using vi = vector<int>;
using vvi = vector<vi>;

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
        for(int i = 31; i>=0; i--){ // Inserting the bits value of the number starting from left.
            int bit = (num >> i) & 1;
            if(node->containsKey(bit) == false){ // if the bit is not present then we add a link to that bit in the trie from the given node.
                node->put(bit);
            }
            node = node->get(bit);
        }
    }
    
    int getMax(int num){
        TrieNode *node = root;
        int maxNum = 0;
        for(int i = 31; i>=0; i--){ // checking the bits value of the number starting from left.
            int bit = (num >> i) & 1, newBit = bit;
            if(node->containsKey(1-bit)){ // if we found a bit which is opposite to the current bit of the number.
                maxNum += (1 << i);
                newBit = 1 - bit;
            }
            node = node->get(newBit);
        }
        return maxNum;
    }
};

int findMaximumXOR(int& x, vector<int>& nums) {
    Trie virtualTrie; // Forming a trie.
    for(int num: nums){
        virtualTrie.insert(num); // adding all the elements of the vector to the trie in bits based form.
    }
    return virtualTrie.getMax(x); // finding the maximum value which we could get by traversing the trie after giving a value 'x'.
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);

  
    int n, x;
    cin >> n >> x;
    vi arr(n);
    for(int i = 0; i<n; i++) cin >> arr[i];
    
    cout << findMaximumXOR(x, arr) << endl;


    return 0;
}
