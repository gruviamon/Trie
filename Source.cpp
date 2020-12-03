#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];
	bool isLeaf;
};

//Cấp phát bộ nhớ cho TrieNode mới
TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isLeaf = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie 
// If the key is prefix of trie node, just marks leaf node 
void insert(TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root; // con trỏ dùng để duyệt cây

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (pCrawl->children[index] == NULL)
        {
            pCrawl->children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf 
    pCrawl->isLeaf = true;
}

// Returns true if key presents in trie, else false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (pCrawl->children[index] == NULL)
        {
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isLeaf); // ??????
}

// A recursive function to print all possible valid 
// words present in array 
void searchWord(TrieNode* root, int hash[], string str, vector<string> &res)
{
    // if we found word in trie / dictionary 
    if (root->isLeaf == true)
    {
        res.push_back(str);
    }


    // traverse all child's of current root 
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (hash[i] != 0 && root->children[i] != NULL)
        {
            hash[i] --;

            // add current character 
            char c = i + 'a';

            // Recursively search reaming character of word in trie 
            searchWord(root->children[i], hash, str + c, res);
            hash[i] ++;
        }
    }
}

// return a vector include all words present in dictionary. 
vector<string> PrintAllWords(char Arr[], TrieNode* root, int n)
{
    vector <string> res;
    // mảng hash lưu các kí tự có trong mảng đầu vào
    int hash[ALPHABET_SIZE] = {};

    for (int i = 0; i < n; i++)
    {
        hash[Arr[i] - 'a'] ++;
    }

    // tempary node 
    TrieNode* pChild = root;

    // string to hold output words 
    string str = "";

    // Traverse all matrix elements. There are only 26 
    // character possible in char array 
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        // we start searching for word in dictionary 
        // if we found a character which is child of Trie root 
        if (hash[i] != 0 && pChild->children[i] != NULL)
        {
            hash[i] --;
            str += (i + 'a');
            searchWord(pChild->children[i], hash, str, res);
            hash[i] ++;
            str = "";
        }
    }
    return res;
}

string deleteSpace(string str)
{
    string res = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ') continue;
        res += str[i];
    }
    return res;
}

int main()
{
    ifstream inFile("Dic.txt");
    if (!inFile)
    {
        cout << "no";
        return 0;
    }

    string key;
    TrieNode* trie = getNode();
    while (!inFile.eof())
    {
        getline(inFile, key);
        if (!search(trie, key))
        {
            insert(trie, key);
        }
    }
    inFile.close();
    
    string temp;
    getline(cin, temp);

    temp = deleteSpace(temp);

    int in_size = temp.length();
    char* in = new char[in_size];
    for (int i = 0; i < in_size; i++)
    {
        in[i] = (char)temp[i];
    }

    vector<string> res = PrintAllWords(in, trie, in_size);

    for (int i = 0; i < res.size(); i++)
    {
        if (res[i].length() < 3)
        {
            res.erase(res.begin() + i);
            i--;
        }
    }

    cout << res.size() << endl;
    for (string i : res)
    {
        cout << i << endl;
    }
    return 0;
}

