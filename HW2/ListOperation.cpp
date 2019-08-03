// Code credit and work cited at the end of file.
#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;


string get_str_between_two_str(const std::string &s,const std::string &start_delim,const std::string &stop_delim) {
	/*Code credit goes to imfa, stackoverflow.com*/
	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
	unsigned last_delim_pos = s.find(stop_delim);

	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
} //end get_str_between_two_str

struct Node {
	string book_id;
	string book_name;
	string book_author;
	struct Node *next;
	struct Node *prev;
}; //end struct Node

struct Node *head;
struct Node *tail;

int size() {
	Node *current = head;
	int counter = 0;
	while (current != NULL) {
		counter++;
		current = current->next;
	}
	return counter;
} //end size

void removeDuplicates(struct Node *start)  { 
	struct Node *ptr1, *ptr2, *dup; 
	ptr1 = start;
	while (ptr1 != NULL && ptr1->next != NULL) { 
		ptr2 = ptr1;
		while (ptr2->next != NULL) { 
			if (ptr1->book_id == ptr2->next->book_id) { 
				dup = ptr2->next; 
				ptr2->next = ptr2->next->next; 
				delete(dup); 
			} 
			else {
				ptr2 = ptr2->next; 
            } //end if-else
		} //end while 
		ptr1 = ptr1->next; 
	} //end while
} //end removeDuplicates

void print() {
	/*Printing to terminal*/
	if (size() == 0) {
		cout << "can't print from empty list" << endl;
		return;
	}
	Node *temp = head;
	while (temp != NULL) {
		cout << "book_id:" << temp->book_id;
		cout << ", book_name:" << temp->book_name;
		cout << ", book_author:" << temp->book_author << endl;
		temp = temp->next;
	}
} //end print

void print(string outFile) {
	/*Printing to output file*/
	ofstream outFS(outFile.c_str());
	if (size() <= 0) {
		outFS << "";
		outFS.close();
	} else {
		Node *temp = head;
		removeDuplicates(temp);
		while (temp != NULL) {
			outFS << "book_id:" << temp->book_id;
			outFS << ", book_name:" << temp->book_name;
			outFS << ", book_author:" << temp->book_author << endl;
			temp = temp->next;
		}
		outFS.close();
	}

}

void add_in_position(string id, string name, string author, int n) {
	if (n > size()) {
		n = size();
	}
	Node *newNode = new Node, *nodePtr, *prevNode = NULL;
	newNode->book_id = id;
	newNode->book_name = name;
	newNode->book_author = author;
	nodePtr = head;

	for (int i = 0; i < n; ++i) {
		prevNode = nodePtr;
		nodePtr = nodePtr->next;
	}

	if (prevNode) {
		prevNode->next = newNode;
		newNode->next = nodePtr;
	} else {
		head = newNode;
		newNode->next = nodePtr;
	}
	removeDuplicates(newNode);

} //end add

void add_at_end(string id, string name, string author) {
	Node *temp = new Node;
	
	temp->book_id = id;
	temp->book_name = name;
	temp->book_author = author;
	temp->next = NULL;
	Node *ptr = head;

	if (head == NULL) {
		head = temp;
	} else {
		Node *temp1 = new Node;
		temp1 = head;
		while (temp1->next != NULL) {
			temp1 = temp1->next;
		}
		temp1->next = temp;
	}
}


void deleteKey(string attribute, string key) {
	if (size() == 0) {
		cout << "can't delete from empty list" << endl;
		return;
	}

	struct Node *temp = head, *prev;
	// cout << "attribute: " << attribute << endl << "key: " << key << endl << endl;
	if (attribute == "book_id") {
		while (temp != NULL && temp->book_id == key) {
		    head = temp->next;
		    free(temp);
		    temp =head;
		}
		while (temp != NULL) {
			while (temp != NULL && temp->book_id != key) {
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL) return;
			prev->next = temp->next;

			free(temp);
			temp = prev->next;
		}
	} else if (attribute == "book_name") {
		while (temp != NULL && temp->book_name == key) {
			head = temp->next;
			free(temp);
			temp =head;
		}
		while (temp != NULL) {
			while (temp != NULL && temp->book_name != key) {
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL) return;
			prev->next = temp->next;

			free(temp);
			temp = prev->next;
		}
	} else {
		while (temp != NULL && temp->book_author == key) {
			head = temp->next; 
			free(temp); 
			temp =head; 
		}
		while (temp != NULL) {
			while (temp != NULL && temp->book_author != key) {
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL) return;
			prev->next = temp->next;

			free(temp); 
			temp = prev->next;
		}
	}
	removeDuplicates(temp);
} //end deleteKey

void remove_key(string keyword) {
	if (size() == 0) {
		cout << "can't delete from empty list" << endl;
		return;
	}
	string first = "", last = ":";
	string attribute = get_str_between_two_str(keyword, first, last);
	string key = get_str_between_two_str(keyword, last, first);
	deleteKey(attribute, key); //index to be removed
	cout << "To be removed, " << attribute << " " << key << endl;
	Node *temp;

	/*EXAMPLE remove_key("book_id:32452"); */
} //end remove_key


void remove_at_position(int position) {
	if (size() == 0) {
		cout << "can't delete from empty list" << endl;
		return;
	}
	Node *temp = head;
	cout << "Removing node number " << position << endl;
	if (head == NULL || position > size()) {
		cout << "ERROR!" << endl;
		return; 
	} 

	if (position == 0) {
		head = temp->next;
		free(temp);
		return;
	}

	for (int i = 0; temp != NULL && i < position - 1; ++i) {
		temp = temp->next;
	}
	if (temp == NULL || temp->next == NULL) {
		return;
	}

	Node *next = temp->next->next;
	free(temp->next);
	temp->next = next;
	/*EXAMPLE remove_at_position(3); */
} 

void sort(string keyword) { //bubble sort
	int swapped;
	Node *temp;

    /* Checking for empty list */
	if (size() == 0) {
		cout << "can't sort from empty list" << endl;
		return;
	}
	do {
		swapped = 0;
		temp = head;

		while (temp->next != NULL) {
			if (keyword == "book_id") {
				if (temp->book_id > temp->next->book_id) {
					swap(temp->book_id, temp->next->book_id);
					swap(temp->book_name, temp->next->book_name);
					swap(temp->book_author, temp->next->book_author);
					swapped = 1;
				}
			} else if (keyword == "book_name") {
				if (temp->book_name > temp->next->book_name) {
					swap(temp->book_id, temp->next->book_id);
					swap(temp->book_name, temp->next->book_name);
					swap(temp->book_author, temp->next->book_author);
					swapped = 1;
				}
			} else if (keyword == "book_author") {
				if (temp->book_author > temp->next->book_author) {
					swap(temp->book_id, temp->next->book_id);
					swap(temp->book_name, temp->next->book_name);
					swap(temp->book_author, temp->next->book_author);
					swapped = 1;
				}
			}

			temp = temp->next;
		}
	}
	while (swapped);
}

int main(int argc, char *argv[]) {
	ArgumentManager am(argc, argv);
	string input = am.get("input"), command = am.get("command"), output = am.get("output");

	// string input = "input28.txt", command = "command28.txt", output = "output28.txt";
	ifstream inFS(input.c_str());
	ifstream commandFS(command.c_str());

	cout << "Input file: " << input << ". Command File: " << command << endl;

	string line, lines[1000], book_id, book_name, book_author, str, commands[100], ids[1000];
	string first = "book_id:";
	string middle = ", book_name:";
	string last = ", book_author:";
	int counter = 0, position, size = 0, id_array_size = 0;

	if (inFS.peek() == std::ifstream::traits_type::eof()) {
    	cout << "warning: file is empty, nothing will be added to list" << endl;
    	// return 0;
	}
	/*Getting input*/
	while (getline(inFS, line)) {		
		//loading all data into line array
		if (line == "") continue;
		lines[counter++] = line;
	} //end while loop


	for (int i = 0; i < counter; ++i) {
		str = lines[i];
		book_id = get_str_between_two_str(str, first, middle);
		book_name = get_str_between_two_str(str, middle, last);
		book_author = get_str_between_two_str(str, last, last);
		if (std::find(std::begin(ids), std::end(ids), book_id) != std::end(ids)) {
			cout << "book_id already exists and will not be added!" << endl;
		}
		else {
			ids[i] = book_id;	
			id_array_size++;
			add_at_end(book_id, book_name, book_author);
			size++;
		}
		// cout << lines[i] << endl; 					/*Printing*/
	}

	/*Printing values in linked list*/
	cout << "==================" << endl;
	cout << "Saved in linked list: " << endl;
	print();
	cout << "==================" << endl;

	/*Getting commands*/
	counter = 0;

	while (getline(commandFS, line)) {
		if (line == "") continue;
		commands[counter++] = line;
	}

	for (int i = 0; i < counter; i++) {
		string instruction = get_str_between_two_str(commands[i], "", " ");

		if (instruction == "sort") {
			// if (i == 0) {
			// 	continue;
			// } else {
				str = get_str_between_two_str(commands[i], "sort ", "");
				cout << i+1 << ". Sorting by: " << str << endl;
				sort(str);
			// }
			// print();
		}

		if (instruction == "add") {
			position = stoi(get_str_between_two_str(commands[i], " pos:", " book_id:"));
			book_id = get_str_between_two_str(commands[i], first, ", book_name:");
			book_name = get_str_between_two_str(commands[i], " book_name:",  last);
			book_author = get_str_between_two_str(commands[i], last, "");

			if (find(begin(ids), end(ids), book_id) != end(ids)) {
				cout << "Error: book_id already exists!" << endl;
			} else {
				if (position > size || position < 0 || position == 0) {
					position = size;
				}
				cout << i+1 << ". Adding in position: " << position << endl;
				add_in_position(book_id, book_name, book_author, position);
				ids[id_array_size++] = book_id;
				size++;
			}
			// print();
		}

		if (instruction == "remove") {
			string str2 = "remove pos:";
			if (commands[i].find(str2) != std::string::npos) {
				position = stoi(get_str_between_two_str(commands[i], "pos:", ""));
				if (position < 0) {
					cout << "incorrect position" << endl;
					continue;
				} else {
					remove_at_position(position);
				}

			} else {
				str = get_str_between_two_str(commands[i], "remove ", "");
				remove_key(str);
			}
			size--;
			if (size <= 0) {
				print();
			}
			// print();
		}
	}

	cout << "==================" << endl;
	  print();									/*to command prompt*/
	  print(output);							/*to outfile*/
	cout << "Output saved to: " << output << endl;
	cout << "==================" << endl;

	inFS.close();
	commandFS.close();
	return 0;	
} //end main

/*Work Cited: 

1. Delimiters: imfa, https://stackoverflow.com/questions/18800796/c-get-string-between-two-delimiter-string
2. removeDuplicates: https://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-linked-list/
3. deleteKey: https: geeksforgeeks, //www.geeksforgeeks.org/delete-occurrences-given-key-linked-list/
4. Delete key at n-th position: https://www.youtube.com/watch?v=Y0n86K43GO4&t=329s
4. Delete node from given position: https://www.youtube.com/watch?v=FR-3fn5l1bA
5. Insert node at n-th position: mycodeschool, https://www.youtube.com/watch?v=IbvsNF22Ud0&t=747s
6. Sorting a Linked List: BB Barters, https://www.youtube.com/watch?v=S0anUxnLgA8
7. Check for duplicate values in arrays: Post Self, https://stackoverflow.com/questions/45679999/find-if-an-element-exists-in-c-array
8. Sorting: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/

Compiling:
g++ -std=c++11 -o ListOperation ListOperation.cpp
./ListOperation input=input24.txt command=command24.txt output=output24.txt

g++ -std=c++11 -o ListOperation ListOperation.cpp
ListOperation.exe

g++ ListOperation.cpp -o ListOperation
ListOperation.exe input=input24.txt command=command24.txt output=output24.txt

*/