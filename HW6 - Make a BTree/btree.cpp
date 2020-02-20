#include <iostream>
#include <string>
#include <cstring>
#include "ArgumentManager.h"
#include <fstream>
using namespace std;

// Page 695
template <class recType>
struct bTreeNode{
    int recCount;
    recType *list;
    bTreeNode **children;
public:
    bTreeNode(int bTreeOrder){
        list = new recType[bTreeOrder - 1];
        children = new bTreeNode*[bTreeOrder]();
    }
};

template <class recType>
class bTree{
public:
    bool search(const recType& searchItem);
    void searchNode(bTreeNode<recType> *current, const recType &item, bool &found, int &loc);
    void insert(const recType& insertItem);
    void insertBtree(bTreeNode<recType> *current, const recType& insertItem, recType &median, bTreeNode<recType>* &rightChild, bool &isTaller);
    void insertNode(bTreeNode<recType> *current,const recType& insertItem,bTreeNode<recType>* &rightChild, int insertPostion);
    
    void print(int level_n, ofstream &outFS);
    void inOrder(ofstream &outFS);
    void recInorder(bTreeNode<recType> *current, ofstream &outFS);
    void levelPrint(bTreeNode<recType> *current, int level, int &levelCount, bool &isEmpty, ofstream &outFS);
    
    void splitNode(bTreeNode<recType> *current,const recType& insertItem,bTreeNode<recType>* rightChild, int insertPostion, bTreeNode<recType>* &rightNode, recType &median);
    bTree(int degree);
protected:
    bTreeNode<recType> *root;
    int bTreeOrder;
    
};


template <class recType>
bTree<recType>::bTree(int degree){
    root = NULL;
    bTreeOrder = degree;
}

template <class recType>
void bTree<recType>::print(int level, ofstream &outFS) {
    bool isEmpty = true;
    int levelCount = 1;
    levelPrint(root, level, levelCount, isEmpty, outFS);
    if (isEmpty == true) {
        outFS << "empty";
        cout << "empty";
    } 
    // levelPrint(this->root, level_n, 1, isEmpty);
}

template <class recType>
void bTree<recType>::levelPrint(bTreeNode<recType> *current, int level, 
    int &levelCount, bool &isEmpty, ofstream &outFS) {
    if (levelCount == level) {
        isEmpty = false;
        for (int i = 0; i < current->recCount; i++) {
            outFS << current->list[i] << " ";
            cout << current->list[i] << " ";
        }
    } else {
        levelCount += 1;
        for (int i = 0; i < current->recCount + 1; i++) {
            if (current->children[i] == NULL) 
                continue;
            levelPrint(current->children[i], level, levelCount, isEmpty, outFS);
        }
        levelCount -= 1;
    }

    //if (current == NULL) return;
    //if (level == 1) {
    //  for (int i = 0; i < current->recCount; ++i) {
    //      cout << current->list[i] << " ";
    //  }
    //}
    //if (levelCount != level) {
    //  // cout << "not there yet! level: " << levelCount << endl;
    //  levelCount += 1;
    //  levelPrint(current, level, levelCount);
    //}
    //else {
    //  current = current->children[levelCount];
    //  for (int i = 0; i < current->recCount; ++i) {
    //      cout << current->list[i] << " ";
    //  }
    //  // cout << "we're here! welcome to level " << levelCount << endl;
    //}
}

template <class recType>
void bTree<recType>::recInorder (bTreeNode<recType> *current, ofstream &outFS) {
    if (current != NULL) {
        recInorder(current->children[0], outFS);
        for (int i = 0; i < current->recCount; i++)
        {
            outFS << current->list[i] << " ";
            cout << current->list[i] << " ";
            recInorder(current->children[i + 1], outFS);
        }
    }
} //end recInorder


template <class recType>
void bTree<recType>::inOrder(ofstream &outFS)
{
    
    // cout << "Level of BTree: " << level << endl;
    recInorder(root, outFS);
} // end inOrder

//search in tree
template <class recType>
bool bTree<recType>::search(const recType& searchItem)
{
    bool found = false;
    int location;
    bTreeNode<recType> *current;
    current = root;
    while (current != NULL && !found) {
        searchNode(current, searchItem, found, location);
        if(!found)
            current = current->children[location];
    }
    return found;
}



template <class recType>
void bTree<recType>::insert(const recType& insertItem)
{
    bool isTaller = false;
    recType median;
    bTreeNode<recType> *rightChild;
    insertBtree(root, insertItem, median, rightChild, isTaller);
    
    if(isTaller){
        bTreeNode<recType> *tempRoot;
        tempRoot = new bTreeNode<recType>(bTreeOrder);
        tempRoot->recCount = 1;
        tempRoot->list[0] = median;
        tempRoot->children[0] = root;
        tempRoot->children[1] = rightChild;
        
        root = tempRoot;
    }
}
//search inside a node
template <class recType>
void bTree<recType>::searchNode(bTreeNode<recType> *current, const recType &item, bool &found, int &location)
{
    location = 0;
    while (location < current->recCount && item > current->list[location]) {
        location++;
    }
    
    if (location < current->recCount && item == current->list[location]) {
        found = true;
    }
    else{
        found = false;
    }
}

template <class recType>
void bTree<recType>::insertBtree(bTreeNode<recType> *current, const recType& insertItem, recType &median, bTreeNode<recType>* &rightChild, bool &isTaller) {
    int position;
    isTaller = false;

    if (current == NULL)
    {
        median = insertItem;
        rightChild = NULL;
        isTaller = true;
    }
    else {
        bool found = false;

        searchNode(current, insertItem, found, position);

        if (found)
            cout << "Cannot insert duplicate (" << insertItem << ")." << endl;
        else {
            recType newMedian;

            bTreeNode<recType> *newChild;

            insertBtree(current->children[position], insertItem, newMedian, newChild, isTaller);

            if (isTaller) {
                if (current->recCount < bTreeOrder - 1) {
                    isTaller = false;
                    insertNode(current, newMedian, newChild, position);
                }
                else {
                    splitNode(current, newMedian, newChild, position, rightChild, median);
                }
            }
        }
    }
} //insertBtree

template <class recType>
void bTree<recType>::insertNode(bTreeNode<recType> *current,const recType& insertItem, bTreeNode<recType>* &rightChild, int insertPostion){
    
    int index;
    for (index = current->recCount; index > insertPostion; index--) {
        current->list[index] = current->list[index - 1];
        current->children[index + 1] = current->children[index];
    }
    
    current->list[index] = insertItem;
    current->children[index + 1] = rightChild;
    current->recCount++;
}
template <class recType>
void bTree<recType>::splitNode(bTreeNode<recType> *current, const recType& insertItem, bTreeNode<recType>* rightChild, int insertPostion, bTreeNode<recType>* &rightNode, recType &median)
{
    rightNode = new bTreeNode<recType>(bTreeOrder);
    int mid = (bTreeOrder - 1) / 2;
    
    if (insertPostion <= mid)
    {
        int index = 0;
        int i = mid;
        while(i < bTreeOrder - 1)
        {
            rightNode->list[index] = current->list[i];
            rightNode->children[index + 1] = current->children[i+1];
            index++;
            i++;
        }
        
        current->recCount = mid;
        insertNode(current, insertItem, rightChild, insertPostion);
        //decrement the rcount of current
        (current->recCount)--;
        
        median = current->list[current->recCount];
        rightNode->recCount = index;
        rightNode->children[0] = current->children[current->recCount + 1];
        
    }
    else{
        int i = mid + 1;
        int index = 0;
        
        while (i<bTreeOrder - 1)
        {
            rightNode->list[index] = current->list[i];
            rightNode->children[index + 1] = current->children[i+1];
            index++;
            i++;
        }
        
        current->recCount = mid;
        rightNode->recCount = index;
        
        median = current->list[mid];
        insertNode(rightNode, insertItem, rightChild, insertPostion - mid - 1);
        rightNode->children[0] = current->children[current->recCount + 1];
    }
    
}

string get_str_between_two_str(const std::string &s,const std::string &start_delim,const std::string &stop_delim) {
        unsigned first_delim_pos = s.find(start_delim);
        unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
        unsigned last_delim_pos = s.find(stop_delim);
    
        return s.substr(end_pos_of_first_delim,
                last_delim_pos - end_pos_of_first_delim);
} //end get_str_between_two_str

bool substring(string big_string, string small_string) {
    // returns true if small string in big string
    if (big_string.find(small_string) != string::npos) return true;
    else return false;
}

int main(int argc, char * argv[]) {
    /*Manual IO*/
    // string a = "73";
    // string input = "input"+a+".txt", command = "command"+a+".txt", output = "output"+a+".txt";

    /*Argument Manager IO*/
    ArgumentManager am(argc, argv);
    string input = am.get("input"), command = am.get("command"), output = am.get("output");

    /*Variable Declaration*/
    string s[1000], line, commands[1000];
    int arr[1000], counter_of_input=0, counter_of_commands = 0, temp_int;
    ifstream inFS(input.c_str()), commandFS(command.c_str());
    ofstream outFS(output.c_str());
    string x;

    /*Gathering input integers*/
    while (inFS >> x) {
        arr[counter_of_input++] = stoi(x);
    }

    /*Gathering commands from command file*/
    while (getline(commandFS, line)) {
        if (line == "") continue;
        commands[counter_of_commands++] = line;
        cout << counter_of_commands << ": " << line << endl;
    }
    

    cout << endl;
    string dwag = get_str_between_two_str(commands[0], "Degree=", "");
    cout << "Degree of Tree: " << dwag << endl;
    bTree<int> b(stoi(dwag));
    for (int i = 0; i < counter_of_input; ++i) {
        b.insert(arr[i]);
    }
    string lev = "Level ";
    for (int i = 1; i < counter_of_commands; ++i) {
        if (commands[i] == "Inorder Traversal" || commands[i] == "inorder traversal") {
            cout << "inorder travel\n";
            b.inOrder(outFS);
            outFS << endl;
        }
        if (substring(commands[i], lev)) {
            temp_int = stoi(get_str_between_two_str(commands[i], "Level ", ""));       
            cout << "printing level: " << temp_int << endl;
            b.print(temp_int, outFS);                                                       
            outFS << endl;
        }

    }

    cout << endl << endl;


    inFS.close();
    commandFS.close();
    outFS.close();
    return 0;
}