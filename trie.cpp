#include <iostream>
using namespace std;

class trie
{
public:
    trie *children[26];
    bool isEnd;

    trie()
    {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;

        isEnd = false;
    }
};

void insert(trie *root, string str)
{
    trie *pcrawl = root;
    int index;
    for (int i = 0; i < str.size(); i++)
    {
        index = str[i] - 'a';
        if (!pcrawl->children[index])
            pcrawl->children[index] = new trie();
        pcrawl = pcrawl->children[index];
    }
    pcrawl->isEnd = true;
}

bool search(trie *root, string str)
{
    trie *pcrawl = root;

    int index;
    for (int i = 0; i < str.size(); i++)
    {
        index = str[i] - 'a';
        if (!pcrawl->children[index])
            return false;
        pcrawl = pcrawl->children[index];
    }
    return pcrawl->isEnd;
}

int main(int argc, char const *argv[])
{

    trie *root = new trie();

    string keys[] = {"the", "a", "there",
                     "answer", "any", "by",
                     "bye", "their"};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    search(root, "ther") ? cout << "Yes\n" : cout << "No\n";
    search(root, "there") ? cout << "Yes\n" : cout << "No\n";

    return 0;
}
