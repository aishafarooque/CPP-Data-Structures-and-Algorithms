#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstring> 
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

struct Node { int data; Node *next; };
struct Node *head;
string get_str_between_two_str(const std::string &s,const std::string &start_delim,const std::string &stop_delim);
void push(struct Node** head_ref, int new_data);
struct Node *getTail(struct Node *cur);
void print(struct Node *node);
struct Node *partition(struct Node *head, struct Node *end, struct Node **newHead, struct Node **newEnd);
void quick_sort(int a[],int l,int u);
int partition(int a[],int l,int u);
void swap(int* a, int* b);
struct Node* SortedMerge(struct Node* a, struct Node* b); 
void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef); 
void MergeSort(struct Node** headRef);
int shellSort(int arr[], int n);
void convertStrtoArr(string x);
long stoi(const char *s);
void linkedtoarray(struct Node *head, int arr[], int size);
void reverseArray(int arr[], int start, int end);

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string input = am.get("input"), command = am.get("command"), output = am.get("output");

    // string input = "input34.txt", command = "command34.txt", output = "output33.txt";
    
    struct Node *head = NULL;
    string instruction, order, numbers, commands[100], line, str, str2 = " ascending ", str3 = " descending ";
    int arr[100000], size = sizeof(arr)/sizeof(arr[0]), counter_of_input = 0, counter_of_commands = 0, nu;
    int i = 0, index_to_extract[100000];


    ifstream inFile(input.c_str()), commandFile(command.c_str());
    ofstream outFile(output.c_str());

    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        cout << "warning: input file is empty, nothing will be added to list" << endl;
        // return 0;
    }

    if (commandFile.peek() == std::ifstream::traits_type::eof()) {
        cout << "warning: command file is empty, no commands will be performed" << endl;
        // return 0;
    }

    
    while (!inFile.eof()) {
        inFile >> arr[counter_of_input++];
    }

    if (counter_of_input == 1) {
        outFile << arr[0];
        return 0;
    }
    
    while (getline(commandFile, line)) {
        if (line == "") continue;
        commands[counter_of_commands++] = line;
        cout << counter_of_commands << ": " << line << endl;
    }

  
    for (int i = 0; i < counter_of_input; i++) {
        push(&head, arr[i]);
    }

    int n = sizeof(arr)/sizeof(arr[0]); 

    /*Checking if there's an order in command*/
    for (int i = 0; i < counter_of_commands; ++i) {
        str = commands[i];
        if (str.find(str2) != string::npos || str.find(str3) != string::npos) {
            // cout << "found\n";
            //do something
        } else {
            str.insert(10, str2);
            cout << str << endl;
        }
        commands[i] = str;
    }

    for (int i = 0; i < counter_of_commands; ++i) {
        instruction = get_str_between_two_str(commands[i], "", " sort"); /*Get name of sort*/
        numbers = get_str_between_two_str(commands[i], "ing ", "");
        order = get_str_between_two_str(commands[i], "sort ", "ing");
        // cout << numbers;
        // cout << order;
        if (instruction == "quick" || instruction == "Quick" || instruction == "QUICK") {
            cout << "Quick sort:" << endl;
            // print(head);
            // quickSort(&head);
            // linkedtoarray(head, arr, counter_of_input);
            quick_sort(arr, 0, counter_of_input-1);
        } else if (instruction == "merge" || instruction == "Merge" || instruction == "MERGE") {
            cout << "Merge sort:" << endl;
            MergeSort(&head);
            linkedtoarray(head, arr, counter_of_input);
        } else {
            cout << "Shell sort:" << endl;
            shellSort(arr, counter_of_input);
        }


        if (order == "descend") {
            // cout << "Reversing arr\n";
            reverseArray(arr,0, counter_of_input-1);
        }

        stringstream ssin(numbers);
        // cout << "Extracting array\n";
        while (ssin.good() && i < numbers.size()-1){
            ssin >> nu;
            if (nu > counter_of_input || nu < 0) continue;
            // cout << arr[i] << " ";
            index_to_extract[i] = arr[nu];
            ++i;
        }
        cout << "\nPrinting out extracted array\n";
        for (int j=0; j<i; j++) {
            cout << index_to_extract[j] << " "; 
            outFile << index_to_extract[j] << " ";
        }
        // delete(head);
        // head = NULL;
    }

    inFile.close();
    commandFile.close();
    outFile.close();
    
    return 0;
} //end main




//======================================================
void linkedtoarray(struct Node *head, int arr[], int size) {
  int i = 0;
  while (head != NULL && i != size) {
    arr[i++] = head->data;
    head = head->next;
  }
}

long stoi(const char *s) {
    /*Code credit to wangyang - stackoverflow*/
    long i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
}

void convertStrtoArr(string x) {
    int newArr[10], i = 0;
    stringstream ssin(x);
    while (ssin.good()) {
        ssin >> newArr[i++];
    }

    for (int i = 0; i < 10; ++i) {
        cout << newArr[i] << " ";
    }
    // return newArr;
}

string get_str_between_two_str(const std::string &s,const std::string &start_delim,const std::string &stop_delim) {
    /*Code credit goes to imfa, stackoverflow.com*/
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);

    return s.substr(end_pos_of_first_delim,
        last_delim_pos - end_pos_of_first_delim);
}

void push(struct Node** head_ref, int new_data) { 
    struct Node* new_node = new Node;  
    new_node->data  = new_data;   
    new_node->next = (*head_ref); 
    (*head_ref)    = new_node; 
} 

struct Node *getTail(struct Node *cur) { 
    while (cur != NULL && cur->next != NULL) 
        cur = cur->next; 
    return cur; 
} 

void print(struct Node *node) { 
    while (node != NULL) { 
        printf("%d  ", node->data); 
        node = node->next; 
    } 
    printf("\n"); 
} 

void swap(int* a, int* b) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 



void quick_sort(int a[],int l,int u) {
    /*Code credit to thecrazyprogrammar.com*/
    int j;
    if(l<u)
    {
        j=partition(a,l,u);
        quick_sort(a,l,j-1);
        quick_sort(a,j+1,u);
    }
}
 
int partition(int a[],int l,int u) {
    int v,i,j,temp;
    v=a[l];
    i=l;
    j=u+1;
    
    do
    {
        do
            i++;
            
        while(a[i]<v&&i<=u);
        
        do
            j--;
        while(v<a[j]);
        
        if(i<j)
        {
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }while(i<j);
    
    a[l]=a[j];
    a[j]=v;
    
    return(j);
}

void MergeSort(struct Node** headRef)  { 
    struct Node* head = *headRef, *a, *b; 
    if ((head == NULL) || (head->next == NULL))  { 
        return; 
    } 
    FrontBackSplit(head, &a, &b);  
    MergeSort(&a); 
    MergeSort(&b); 
    *headRef = SortedMerge(a, b); 
} 
struct Node* SortedMerge(struct Node* a, struct Node* b)  { 
    struct Node* result = NULL; 
    if (a == NULL) 
        return(b); 
    else if (b==NULL) 
        return(a); 
    if (a->data <= b->data)  { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return(result); 
} 

void FrontBackSplit(struct Node* source, 
    struct Node** frontRef, struct Node** backRef) { 
    struct Node* fast; 
    struct Node* slow; 
    slow = source; 
    fast = source->next; 
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 

 int shellSort(int arr[], int n) { 
     for (int gap = n/2; gap > 0; gap /= 2) { 
         for (int i = gap; i < n; i += 1) { 
             int temp = arr[i]; 
             int j;             
             for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                 arr[j] = arr[j - gap]; 
             arr[j] = temp; 
         } 
     }  
     return 0;  
 }

void reverseArray(int arr[], int start, int end) { 
    /*Code credit to stackoverflow*/
    while (start < end) { 
        int temp = arr[start];  
        arr[start] = arr[end]; 
        arr[end] = temp; 
        start++; 
        end--; 
    }  
}      