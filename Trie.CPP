#include<iostream>
#include<string>

using namespace std;

struct Node
{
    struct Node *links[26];
    int wordEndCount;
    struct Node *parent;
};

class Trie
{
private:
    struct Node* head;
public:
    Trie(); 
    void insertWord(string &s);
    int countWordsEqualTo(string &s);
    int countWordsStartingWith(string &s);
    int countWordEnds(struct Node *);
    void EraseWord(string &s);
};

int getChoice()
{
    int c;
    cout<<"Enter choice \n";
    cout<<"1 : Insert string || 2 : Count Words Equal to || 3 : Count Prefixes || 4 : Erase Word\n";
    cin>>c;
    return c;
}
int main()
{
    class Trie myTrie;
    string s;
    int choice;
    choice = getChoice();
    while(choice)
    {
        cout<<"Enter string : ";
        cin>>s;
        switch(choice)
        {
            case 1 :    myTrie.insertWord(s);
                        break;
            case 2 :    cout<<myTrie.countWordsEqualTo(s);
                        break;
            case 3 :    cout<<myTrie.countWordsStartingWith(s);
                        break;
            case 4 :    myTrie.EraseWord(s);
                        break;
            default:    break;
        }
        choice = getChoice();
    }
    return 0;
}

Trie::Trie()
{
    head = new Node;
    for(int i = 0; i < 26; ++i)
        head->links[i] = NULL;
    head->parent = NULL;
    head->wordEndCount = 0;
}

void Trie::insertWord(string &s)
{
    struct Node *ptr = head, *temp;
    int index, i = 0;

    while(i < s.size())
    {
        index = s[i] - 'a';
        if(ptr->links[index] == NULL)
        {
            ptr->links[index] = new Node;
            temp = ptr->links[index];
            temp->wordEndCount = 0;
            temp->parent = ptr;
            for(int i = 0; i < 26; ++i)
                temp->links[i] = NULL;
        }
        ptr = ptr->links[index];

        ++i;            
    }
    (ptr->wordEndCount)++;
}

int Trie::countWordsEqualTo(string &s)
{
    struct Node *ptr = head;
    int index, i = 0;

    while(i < s.size())
    {
        index = s[i] - 'a';
        if(ptr->links[index] == NULL)
            return 0;
        ptr = ptr->links[index];
        ++i;
    }
    return ptr->wordEndCount;
}

int Trie::countWordEnds(struct Node *ptr)
{
    if(ptr == NULL)
        return 0;
    int i, sumVal = 0;
    for(i = 0; i < 26; ++i)
        sumVal += countWordEnds(ptr->links[i]);
    
    return sumVal + ptr->wordEndCount;
}

int Trie::countWordsStartingWith(string &s)
{
    struct Node *ptr = head;
    int index, i = 0;

    while(i < s.size())
    {
        index = s[i] - 'a';
        if(ptr->links[index] == NULL)
            return 0;
        ptr = ptr->links[index];
        ++i;
    }
    return countWordEnds(ptr);
}

void Trie::EraseWord(string &s)
{
    struct Node *ptr = head, *child;
    int index, i = 0, sumVal;

    while(i < s.size())    
    {
        index = s[i] - 'a';
        if(ptr->links[index] == NULL)
            return ;
        ptr = ptr->links[index];
        ++i;
    }
    ptr->wordEndCount = max(0, ptr->wordEndCount - 1);
    sumVal = 0;
    for(i = 0; i < 26; ++i)
        if(ptr->links[i] != NULL)
            sumVal += 1;
    while(ptr != head && ptr->wordEndCount == 0 && sumVal == 0)
    {
        child = ptr;
        ptr = ptr->parent;
        for(i = 0; i < 26; ++i)
        {
            if(ptr->links[i] == child)
                ptr->links[i] = NULL;
            else if(ptr->links[i] != NULL)
                ++sumVal;                
        }
        delete(child);
    }
}