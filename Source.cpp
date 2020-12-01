#include <iostream>
#include <fstream>
#include <string>
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
void searchWord(TrieNode* root, bool hash[], string str)
{
    // if we found word in trie / dictionary 
    if (root->isLeaf == true)
    {
        cout << str << endl;
    }


    // traverse all child's of current root 
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (hash[i] == true && root->children[i] != NULL)
        {
            hash[i] = false;

            // add current character 
            char c = i + 'a';

            // Recursively search reaming character of word in trie 
            searchWord(root->children[i], hash, str + c);
            hash[i] = true;
        }
    }
}

// Prints all words present in dictionary. 
void PrintAllWords(char Arr[], TrieNode* root, int n)
{
    // mảng hash lưu các kí tự có trong mảng đầu vào
    bool hash[ALPHABET_SIZE];

    for (int i = 0; i < n; i++)
    {
        hash[Arr[i] - 'a'] = true;
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
        // if we found a character which is child 
        // of Trie root 
        if (hash[i] == true && pChild->children[i] != NULL)
        {
            hash[i] = false;
            str += (i + 'a');
            searchWord(pChild->children[i], hash, str);
            hash[i] = true;
            str = "";
        }
    }
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
    char in[] = { 'a', 'e' , 'l', 'p', 'p' };
    int n = sizeof(in) / sizeof(in[0]);
    PrintAllWords(in, trie, n);
    return 0;
}

