#include "SearchTree.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Node::Node(int key, int ind)
{
    this->lowerKey = key;
    this->lowerBinIndex = ind;
}

Node::Node() 
{ 
}

void Node::printTree(int lvl)
{
    if (this == nullptr) 
    {
        return;
    }
    for (int i = 0; i < lvl; i++) cout << "  ";
    if (this->parent != nullptr)
        cout << this->lowerKey << " " << this->greaterKey << endl;
    else
        cout << this->lowerKey << " " << this->greaterKey << endl;

    this->leftNode->printTree(lvl + 1);
    this->midNode->printTree(lvl + 1);
    this->rightNode->printTree(lvl + 1);

}

Node* Node::searchElem(int key)
{
    if (this->lowerKey == key || this->greaterKey == key)
    {
        return this;
    }
    if (this->lowerKey > key)
    {
        if (this->leftNode == nullptr) return nullptr;
        return this->leftNode->searchElem(key);
    }
    else if ((this->greaterKey == -1 || this->greaterKey > key) && this->lowerKey < key)
    {
        if (this->midNode == nullptr) return nullptr;
        return this->midNode->searchElem(key);
    }
    else 
    {
        if (this->rightNode == nullptr) return nullptr;
        return this->rightNode->searchElem(key);
    }
}

Node* Node::addElem(int key, int ind, int*pres)
{
    Node* forAdding = this->searchAddableNode(key);
    if (forAdding == nullptr) 
    {
        return nullptr;
    }

    Node* newData = new Node(key, ind);
    return forAdding->keepBalance(newData, pres);
    
}

Node* Node::keepBalance(Node* newData, int* pres)
{
    if (this->lowerBinIndex == -1)
    {
        this->lowerBinIndex = newData->lowerBinIndex;
        this->lowerKey = newData->lowerKey;
        this->leftNode = newData->leftNode;
        this->midNode = newData->midNode;
        return nullptr;
    }

    if (this->greaterBinIndex == -1) 
    {
        if (newData->lowerKey > this->lowerKey) {
            this->greaterBinIndex = newData->lowerBinIndex;
            this->greaterKey = newData->lowerKey;

            this->midNode = newData->leftNode;
            this->rightNode = newData->midNode;

            if (newData->leftNode != nullptr) newData->leftNode->parent = this;
            if (newData->midNode != nullptr) newData->midNode->parent = this;   
        }
        else 
        {
            this->greaterKey = this->lowerKey;
            this->greaterBinIndex = this->lowerBinIndex;
            this->lowerKey = newData->lowerKey;
            this->lowerBinIndex = newData->lowerBinIndex;

            this->rightNode = this->midNode;
            this->midNode = newData->midNode;
            this->leftNode = newData->leftNode;

            if (newData->leftNode != nullptr) newData->leftNode->parent = this;
            if (newData->midNode != nullptr) newData->midNode->parent = this;
        }

        return nullptr;
    }

    int excessKey;
    int excessBinInd;
    *pres = *pres + 1;
    if (this->lowerKey > newData->lowerKey) 
    {
        excessKey = this->lowerKey;
        excessBinInd = this->lowerBinIndex;
        
        Node* NewRoot = new Node(excessKey, excessBinInd);
        NewRoot->leftNode = newData;
        newData->parent = NewRoot;
        
        NewRoot->midNode = new Node(this->greaterKey, this->greaterBinIndex);
        NewRoot->midNode->parent = NewRoot;

        NewRoot->midNode->midNode = this->rightNode;
        if (this->rightNode != nullptr) this->rightNode->parent = NewRoot->midNode;

        NewRoot->midNode->leftNode = this->midNode;
        if (this->midNode != nullptr) NewRoot->midNode->leftNode->parent = NewRoot->midNode;

        if (this->parent == nullptr)
        {
            return NewRoot;
        }
        else return this->parent->keepBalance(NewRoot, pres);
    }
    if (this->lowerKey < newData->lowerKey && this->greaterKey > newData->lowerKey)
    {
        excessKey = newData->lowerKey;
        excessBinInd = newData->lowerBinIndex;
        
        Node* NewRoot = new Node(excessKey, excessBinInd);

        NewRoot->leftNode = new Node(this->lowerKey, this->lowerBinIndex);
        NewRoot->leftNode->leftNode = this->leftNode;
        NewRoot->leftNode->midNode = newData->leftNode;

        NewRoot->leftNode->parent = NewRoot;
        if (NewRoot->leftNode->leftNode != nullptr) NewRoot->leftNode->leftNode->parent = NewRoot->leftNode;
        if (NewRoot->leftNode->midNode != nullptr) NewRoot->leftNode->midNode->parent = NewRoot->leftNode;

        NewRoot->midNode = new Node(this->greaterKey, this->greaterBinIndex);    
        NewRoot->midNode->leftNode = newData->midNode;
        NewRoot->midNode->midNode = this->rightNode;

        NewRoot->midNode->parent = NewRoot;
        if (NewRoot->midNode->leftNode != nullptr) NewRoot->midNode->leftNode->parent = NewRoot->midNode;
        if (NewRoot->midNode->midNode != nullptr) NewRoot->midNode->midNode->parent = NewRoot->midNode;


        if (this->parent == nullptr)
        {
            return NewRoot;
        }
        else return this->parent->keepBalance(NewRoot, pres);
    }
    if (this->greaterKey < newData->lowerKey)
    {
        excessKey = this->greaterKey;
        excessBinInd = this->greaterBinIndex;
        
        Node* NewRoot = new Node(excessKey, excessBinInd);

        NewRoot->leftNode = new Node(this->lowerKey, this->lowerBinIndex);
        NewRoot->leftNode->leftNode = this->leftNode;
        NewRoot->leftNode->midNode = this->midNode;

        NewRoot->leftNode->parent = NewRoot;
        if (this->leftNode != nullptr) this->leftNode->parent = NewRoot->leftNode;
        if (this->midNode != nullptr) this->midNode->parent = NewRoot->leftNode;

        NewRoot->midNode = newData;
        newData->parent = NewRoot;

        if (this->parent == nullptr)
        {
            return NewRoot;
        }
        else return this->parent->keepBalance(NewRoot, pres);
    }
}

Node* Node::searchAddableNode(int key) 
{
    if (this->leftNode == nullptr && this->midNode == nullptr && this->rightNode == nullptr)
    {
        return this;
    }
    if (this->greaterKey == -1) 
    {
        if (this->lowerKey > key)  return this->leftNode->searchAddableNode(key);
        if (this->lowerKey < key) return this->midNode->searchAddableNode(key);

        return nullptr;
    }
    if (this->greaterKey != -1)
    {
        if (this->lowerKey > key) return this->leftNode->searchAddableNode(key);
        if (this->greaterKey < key) return this->rightNode->searchAddableNode(key);
        if (this->greaterKey > key && this->lowerKey < key) return this->midNode->searchAddableNode(key);

        return nullptr;
    }
}

int** getConnectedInt(Node* removingNode, Node* brother)
{
    int** res = new int* [2];
    if (removingNode->parent->leftNode == removingNode || brother == removingNode->parent->leftNode)
    {
        res[0] = &removingNode->parent->lowerKey;
        res[1] = &removingNode->parent->lowerBinIndex;
    }
    else
    {
        res[0] = &removingNode->parent->greaterKey;
        res[1] = &removingNode->parent->greaterBinIndex;
    }
    return res;
}

Node** getBrothers(Node* removingNode)
{
    Node** res = new Node * [2];
    Node* rightBrother = nullptr;
    Node* leftBrother = nullptr;
    if (removingNode->parent->leftNode == removingNode)
    {
        rightBrother = removingNode->parent->midNode;
    }
    else if (removingNode->parent->rightNode == removingNode)
    {
        leftBrother = removingNode->parent->midNode;
    }
    else
    {
        leftBrother = removingNode->parent->leftNode;
        rightBrother = removingNode->parent->rightNode;
    }
    res[0] = leftBrother;
    res[1] = rightBrother;

    return res;
}

Node* Node::removeElem(int key)
{
    Node* removingNode = this->searchElem(key);
    if (removingNode == nullptr) 
    {
        return nullptr;
    }
    if (removingNode->leftNode == nullptr && removingNode->midNode == nullptr && removingNode->rightNode == nullptr)
    {
        if (removingNode->lowerKey == key)
        {
            removingNode->lowerKey = removingNode->greaterKey;
            removingNode->lowerBinIndex = removingNode->greaterBinIndex;

            removingNode->greaterKey = -1;
            removingNode->greaterBinIndex = -1;
        }
        else
        {
            removingNode->greaterKey = -1;
            removingNode->greaterBinIndex = -1;
        }
        if (removingNode->lowerKey != -1 || removingNode->parent == nullptr) return nullptr;
        Node** brothers = getBrothers(removingNode);
        Node* brother = brothers[1];
        int value = brother->lowerKey;
        int ind = brother->lowerBinIndex;
        if (brothers[0] != nullptr && (brothers[1] == nullptr || brothers[1]->greaterKey == -1))
        {
            brother = brothers[0];
            value = brother->greaterKey;
            ind = brother->greaterBinIndex;
        }

        if (brother->greaterKey != -1)
        {
            int** interracted = getConnectedInt(removingNode, brother);
            int* parentKey = interracted[0];
            int* parentInd = interracted[1];

            removingNode->lowerKey = *parentKey;
            removingNode->lowerBinIndex = *parentInd;

            *parentKey = value;
            *parentInd = ind;

            if (brothers[1] == brother) {
                brother->lowerKey = brother->greaterKey;
                brother->lowerBinIndex = brother->greaterBinIndex;
            }
            brother->greaterKey = -1;
            brother->greaterBinIndex = -1;

            return nullptr;
        }

        else 
        {
            while (removingNode->greaterKey != -1 || removingNode->parent != nullptr) 
            {
                Node** brothers = getBrothers(removingNode);
                Node* leftBrother = brothers[0];
                Node* rightBrother = brothers[1];

                if (leftBrother != nullptr) removingNode->lvlMerge(leftBrother);
                else removingNode->lvlMerge(rightBrother);

                removingNode = removingNode->parent;
            }

            if (removingNode->parent == nullptr && removingNode->lowerKey == -1) 
            {
                if (removingNode->leftNode != nullptr) 
                {
                    removingNode->leftNode->parent = nullptr;
                    return removingNode->leftNode;
                }
                if (removingNode->rightNode != nullptr)
                {
                    removingNode->rightNode->parent = nullptr;
                    return removingNode->rightNode;
                }
                else 
                {
                    removingNode->midNode->parent = nullptr;
                    return removingNode->midNode;
                }
            }
            return nullptr;
        }
    }
    else 
    {
        Node* rightest;
        if (key == removingNode->lowerKey) rightest = removingNode->leftNode;
        else rightest = removingNode->midNode;
        while (rightest->rightNode != nullptr) 
        {
            rightest = rightest->rightNode;
        }
        while (rightest->midNode != nullptr)
        {
            rightest = rightest->midNode;
        }


        int* value = &rightest->greaterKey;
        int* ind = &rightest->greaterBinIndex;
        if (*value == -1) 
        {
            value = &rightest->lowerKey;
            ind = &rightest->lowerBinIndex;
        }

        int bufferVal = *value;
        int bufferInd = *ind;

        Node* res = this->removeElem(*value);


        *value = bufferVal;
        *ind = bufferInd;
        return res;
    }
}

void Node::lvlMerge(Node* brother)
{
    Node* removingNode = this;
    if (removingNode->parent->leftNode == removingNode)
    {
        removingNode->lowerKey = removingNode->parent->lowerKey;
        removingNode->lowerBinIndex = removingNode->parent->lowerBinIndex;

        removingNode->greaterKey = brother->lowerKey;
        removingNode->greaterBinIndex = brother->lowerBinIndex;

        removingNode->parent->lowerKey = removingNode->parent->greaterKey;
        removingNode->parent->lowerBinIndex = removingNode->parent->greaterBinIndex;

        removingNode->parent->greaterKey = -1;
        removingNode->parent->greaterBinIndex = -1;

        brother->parent->midNode = nullptr;
        return;
    }
    if (removingNode->parent->rightNode == removingNode) 
    {
        removingNode->greaterKey = removingNode->parent->greaterKey;
        removingNode->greaterBinIndex = removingNode->parent->greaterBinIndex;

        removingNode->lowerKey = brother->lowerKey;
        removingNode->lowerBinIndex = brother->lowerBinIndex;

        removingNode->parent->greaterKey = -1;
        removingNode->parent->greaterBinIndex = -1;

        brother->parent->midNode = nullptr;
        return;
    }
    if (removingNode->parent->midNode == removingNode && removingNode->parent->leftNode == brother) 
    {   
        removingNode->lowerKey = brother->lowerKey;
        removingNode->lowerBinIndex = brother->lowerBinIndex;

        removingNode->greaterKey = removingNode->parent->lowerKey;
        removingNode->greaterBinIndex = removingNode->parent->lowerBinIndex;

        removingNode->parent->lowerKey = removingNode->parent->greaterKey;
        removingNode->parent->lowerBinIndex = removingNode->parent->greaterBinIndex;

        removingNode->parent->greaterKey = -1;
        removingNode->parent->greaterBinIndex = -1;

        removingNode->parent->leftNode = removingNode->parent->midNode;
        removingNode->parent->midNode = removingNode->parent->rightNode;
        removingNode->parent->rightNode = nullptr;

        return;
    }
    if (removingNode->parent->midNode == removingNode && removingNode->parent->rightNode == brother)
    {
        removingNode->lowerKey = removingNode->parent->lowerKey;
        removingNode->lowerBinIndex = removingNode->parent->lowerBinIndex;

        removingNode->greaterKey = brother->lowerKey;
        removingNode->greaterBinIndex = brother->lowerBinIndex;

        removingNode->parent->lowerKey = removingNode->parent->greaterKey;
        removingNode->parent->lowerBinIndex = removingNode->parent->greaterBinIndex;

        removingNode->parent->greaterKey = -1;
        removingNode->parent->greaterBinIndex = -1;

        removingNode->parent->rightNode = removingNode->parent->midNode;
        removingNode->parent->midNode = removingNode->parent->rightNode;
        removingNode->parent->leftNode = nullptr;
        return;
    }
}