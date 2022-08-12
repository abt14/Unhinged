// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// RadixTree.h

#ifndef RadixTree_h
#define RadixTree_h

#include "provided.h"
#include <string>
#include <iostream>

template <typename ValueType>
class RadixTree{
public:
    RadixTree()
    {
        root = new Node;
    }
    ~RadixTree()
    {
        delete root;
    }
    
    void insert(std::string key, const ValueType& value)
    {
        if (search(key) != nullptr) //word has already been inserted
        {
            ValueType* valueptr = search(key);
            *valueptr = value;
        }
        else
        {
            int caseType;
            std::string targetKey;
            Node* target = insertSearch(key, caseType, targetKey, root);   //node where key needs work with
            if (caseType == 0)
            {
                target->endOfWord = true;         //case 0 = key has no more letters that it matches a prefix
                target->m_value = value;        //set the value
            }
            else if (caseType == 1)             //case 1 = leftover letters that must be added to a new node
            {
                int firstLetter = targetKey[0];
                Node* child = new Node;
                child->word = targetKey;
                child->endOfWord = true;
                child->m_value = value;
                target->edges[firstLetter] = child;
            }
            else if (caseType == 2)         //case 2 = words match but prefix has  leftover so must split
            {
                int firstLetter = targetKey[0];
                Node* originalChild = target->edges[firstLetter];
                std::string leftOverLetters = originalChild->word.substr(targetKey.length()); //get the remaining letters in the prefix
                //create a new child node
                Node* child = new Node;
                child->word = targetKey;
                child->endOfWord = true;
                child->m_value = value;
                target->edges[firstLetter] = child;     //new child node to current node
                //deal with the original child
                originalChild->word = leftOverLetters;
                int firstLetterLeftover = leftOverLetters[0];
                child->edges[firstLetterLeftover] = originalChild;
            }
            else if (caseType == 3)     //case 3 = mismatch
            {
                std::string matchingLetters="";
                std::string leftoverKey;
                std::string leftoverCurr;
                int firstLetterTargetKey = targetKey[0];
                Node* originalChild = target->edges[firstLetterTargetKey];
                for (int i=0; i < originalChild->word.length(); i++)
                {
                    if (originalChild->word[i]!=targetKey[i]) //if there is a mismatch of letters
                    {
                        leftoverKey = targetKey.substr(i);
                        leftoverCurr = originalChild->word.substr(i);
                        break;
                    }
                    matchingLetters=matchingLetters+targetKey[i]; //letters in common
                }
                //dealing with the new current child
                Node* currChild = new Node;
                int firstLetterCurr = matchingLetters[0]; //get first letter of matchingLetters
                target->edges[firstLetterCurr] = currChild; //link target node to this new child
                currChild->word = matchingLetters;
                //dealing with the original child
                originalChild->word = leftoverCurr;     //replace original child word with what's leftover
                int firstLetterOld = leftoverCurr[0];
                currChild->edges[firstLetterOld] = originalChild; //link original to current
                //dealing with the key child
                Node* keyChild = new Node;
                keyChild->word = leftoverKey;
                keyChild->endOfWord = true;
                keyChild->m_value = value;
                int firstLetterKey = leftoverKey[0]; //get first letter of matchingLetters
                currChild->edges[firstLetterKey] = keyChild; //link target node to this new child
            }
        }
    }

    ValueType* search (std::string key) const
    {
        int caseType = 0;
        std::string targetKey;
        Node* tempNode = insertSearch(key, caseType, targetKey, root);
        if (caseType==0)    //base case
        {
            if (tempNode->endOfWord == true) //must check if flag is true -> then it means word exists
            {
                ValueType* valueptr = (&(tempNode->m_value));
                return valueptr;
            }
            else
                return nullptr;
        }
        else
            return nullptr;
    }
private:
    struct Node{
        std::string word;
        bool endOfWord;
        Node* edges[128];
        ValueType  m_value;                 //only set the ValueType when the endOfWord is true
        Node()
        {
            word = "";
            endOfWord = false;
            for (int i=0; i<128; i++)
                edges[i] = nullptr;         //each node can have 128 pointers
        }
    };
    Node* root;
    
    Node* insertSearch(std::string key, int& caseType, std::string& targetKey, Node* currNode) const//returns pointer to the node that we need to work with - third parameter is the key as it gets reduced
    {
        if (key.length()==0) //base case
        {
            caseType = 0;
            targetKey = "";
            return currNode;        //will set this flag to true - case 0
        }
        int firstLetter = key[0];
        if (currNode->edges[firstLetter]==nullptr)  //key does not exist
        {
            caseType = 1;
            targetKey = key;
            return currNode;    //create new node and set word equal to key/rest of key - case 1 and 2
        }
        else
        {
            Node* child;
            child = currNode->edges[firstLetter];
            for (int i=0; i<child->word.length(); i++)
            {
                if (child->word[i]!=key[i]) //if there is a mismatch of letters
                {
                    caseType = 3;
                    targetKey = key;
                    return currNode;   //case 4 - mismatch - return current node so that it is easier to do insertion
                }
                if (i+1 == key.size()) //if key is shorter than node word but has matched up everything this is case 2 - prefix has leftover
                {
                    if (child->word.length() > key.length())
                    {
                        caseType=2;
                        targetKey = key;
                        return currNode;  //since the child node is longer, then it means key does not match - case 3
                    }
                }
            }
            currNode = child;   //set the child node as the new root
            return insertSearch(key.substr(child->word.length()),caseType,targetKey, currNode);   //returns key starting at wherever was left off;
        }
    }
};
#endif /* RadixTree_h */
