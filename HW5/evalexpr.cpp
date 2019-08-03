#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <cassert>

#include "ArgumentManager.h"
#define MAX 100
using namespace std;


template <class Type>
struct nodeType {
    Type info;
    nodeType<Type> *link;
    
};

template <class Type>
class Stack {
    private:
        nodeType<Type> *stackTop;
    public: 
        Stack();
        Stack(const Stack<Type> &otherStack);
        ~Stack();
        void initializeStack();
        bool isEmpty() const;
        bool isFull() const;
        void push(const Type& newItem);
        char pop();
        Type top() const;
        void reverseStack(const Stack<Type> &stack);
};

template <class Type>
Stack<Type>::Stack() {
    stackTop = NULL;
}

template <class Type>
bool Stack<Type>::isEmpty() const {
    return (stackTop == NULL);
}

template <class Type>
bool Stack<Type>::isFull() const {
    return false;
}

template <class Type>
Stack<Type>::Stack(const Stack<Type> &otherStack) {
 nodeType<Type> *newNode, *current, *last;
    if (stackTop != NULL) //if stack is nonempty, make it empty
        initializeStack();
    if (otherStack.stackTop == NULL)
        stackTop = NULL;
    else {
        current = otherStack.stackTop; //set current to point
        //to the stack to be copied
        //copy the stackTop element of the stack
        stackTop = new nodeType<Type>; //create the node
        stackTop->info = current->info; //copy the info
        stackTop->link = NULL; //set the link field to NULL
        last = stackTop; //set last to point to the node
        current = current->link; //set current to point to the
        //next node 
        while (current != NULL) {
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->link = NULL;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }//end while
    }//end else
} //end copyStack

template <class Type>
void Stack<Type>::initializeStack() {
    /*reset the stack back to empty*/
    nodeType<Type> *temp;
    while (stackTop != NULL) {
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
}

template <class Type>
Stack<Type>::~Stack() {
    initializeStack();
}//end destructor

template <class Type>
void Stack<Type>::push(const Type& newElement) {
    nodeType<Type> *newNode; //pointer to create the new node
    newNode = new nodeType<Type>; //create the node
    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode; //set stackTop to point to the
    //top node
} //end push

template <class Type>
Type Stack<Type>::top() const {
    assert(stackTop != NULL); //if stack is empty,
    //terminate the program
    return stackTop->info; //return the top element
}//end top

template <class Type>
char Stack<Type>::pop() {
    nodeType<Type> *temp; //pointer to deallocate memory
    if (stackTop != NULL) {
        temp = stackTop; //set temp to point to the top node
        stackTop = stackTop->link; //advance stackTop to the
        //next node
        return temp->info;
        delete temp; //delete the top node
    } else {
        cout << "Cannot remove from an empty stack." << endl;
    }
}//end pop


int precedence(char op){ 
	/*Code credit to Nikhil Jindal, geeksforgeeks.org*/
    if(op == '+'||op == '-') 
    return 1; 
    if(op == '*'||op == '/') 
    return 2; 
    return 0; 
} 

int applyOp(int a, int b, char op){ 
	/*Code credit to Nikhil Jindal, geeksforgeeks.org*/
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b; 
    } 
} 

int evaluate(string tokens) { 
    int i;
    Stack <int> values;
    Stack <char> ops; 
      
    for(i = 0; i < tokens.length(); i++){
        if(tokens[i] == ' ') 
            continue;
        else if(tokens[i] == '('){ 
            ops.push(tokens[i]); 
        }
        else if(isdigit(tokens[i])) { 
            int val = 0; 
            while(i < tokens.length() && isdigit(tokens[i])) { 
                val = (val*10) + (tokens[i]-'0'); 
                i++; 
            } 
              
            values.push(val); 
        } 

        else if(tokens[i] == ')') { 
            while(!ops.isEmpty() && ops.top() != '(') { 
                int val2 = values.top(); 
                values.pop(); 
                  
                int val1 = values.top(); 
                values.pop(); 
                  
                char op = ops.top(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
            ops.pop(); 
        } 
        else { 
            while(!ops.isEmpty() && precedence(ops.top()) >= precedence(tokens[i])){ 
                int val2 = values.top(); 
                values.pop(); 
                  
                int val1 = values.top(); 
                values.pop(); 
                  
                char op = ops.top(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
            ops.push(tokens[i]); 
        } 
    } 
     
    while(!ops.isEmpty()) { 
        int val2 = values.top(); 
        values.pop(); 
                  
        int val1 = values.top(); 
        values.pop(); 
                  
        char op = ops.top(); 
        ops.pop(); 
                  
        values.push(applyOp(val1, val2, op)); 
    } 
    return values.top();
}

bool areThereParenthesis(string str) {
	/*Check if there are parenthesis*/
	string temp;
	for (int i = 0; i < 5; ++i) {
		if (str.find("(") != string::npos) {
			return true;
		} else if (str.find("[") != string::npos) {
			return true;
		} else if (str.find("{") != string::npos) {
			return true;
		} else if (str.find(")") != string::npos) {
			return true;
		} else if (str.find("]") != string::npos) {
			return true;
		} else if (str.find("}") != string::npos) {
			return true;
		} else {
			return false;
		}
	}
}

string simplify(string str) {
	// Removes ++, +-, -+ and --
	// and simplify -() to 0-()
	// example A++B ===> A+B

	string pp = "++", pn = "+-", np = "-+", nn = "--";
	string temp;
	for (int i = 0; i < 5; ++i) {
		if (str.find(pp) != string::npos) {
			str.replace(str.find(pp),pp.length(),"+");
		}
		if (str.find(pn) != string::npos) {	
			str.replace(str.find(pn),pn.length(),"-");
		}
		if (str.find(np) != string::npos) {
			str.replace(str.find(np),np.length(),"-");
		}
		if (str.find(nn) != string::npos) {
			str.replace(str.find(nn),nn.length(),"+");
		}

		temp = "++(";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length(),"(");
		}
	}
	return str;
}	

string put_spaces(string str) {
	string temp;
	for (int i = 0; i < 5; ++i){
		temp = "+";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length(),' ' + temp + ' ');
		}
		temp = "-";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," - ");
		}
		temp = "(";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," ( ");
		}
		temp = ")";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," ) ");
		}
		temp = "{";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," { ");
		}
		temp = "}";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," } ");
		}
		temp = "[";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," [ ");
		}
		temp = "]";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length()," ] ");
		}
	}
	return str;
}

string switch_brackets(string str) {
	string temp;
	for (int i = 0; i < 10; ++i){
		temp = "{";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length(),"(");
		}
		temp = "[";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length(),"(");
		}		
		temp = "}";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length(),")");
		}		
		temp = "]";
		if (str.find(temp) != string::npos) {
			str.replace(str.find(temp),temp.length(),")");
		}
	}
	return str;
}

string indexOf(char no) {
	// returns string index of no, A = 27, a = 1
    ostringstream c; 
    const char alphabets[53] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't','u', 'v', 'w', 'x','y', 'z', 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    int pos;
    for (int i = 0; i < 53; i++) {
        if (alphabets[i] == no && i%2==0) {
            pos = (i+1)*2;
            break;
        } else {
        	pos = (i+1)*3;
        }
    }
    c << pos;
    string temp = c.str();
    return temp;
}

string convert_alpha_to_num(string str) {
    // A+B-C = 27+28-29
    string str1, str2;
    int n = str.length();
    char temp, arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = str[i];
        if (isalpha(str[i])) {
        	if (i%2==0) {
            	str1 = indexOf(arr[i]);
        	} else {
        		str1 = indexOf(arr[i]);
        	}
        } else {
            str1 = str[i];
        }        
        str2 += str1;
    }
    str = str2;
    return str;
}

bool ArePair(char opening,char closing) {
	// Returns true if the brackets are pairs
	if(opening == '(' && closing == ')') return true;
	else if(opening == '{' && closing == '}') return true;
	else if(opening == '[' && closing == ']') return true;
	return false;
}

bool areParanthesisBalanced(string exp) {
	Stack<char>  S;
	for(int i =0;i<exp.length();i++) {
		if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			S.push(exp[i]);
		else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
			if(S.isEmpty() || !ArePair(S.top(),exp[i])) {
				return false;
			}
			else {
				S.pop();
			}
		}
	}
	return S.isEmpty() ? true:false;
}

std::string findAndReplace(std::string str, const std::string& from, const std::string& to) {
	/*Find string from and replaces with string to*/
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

bool areSame(int a[],int n) { 
	// Returns false if elements in an array are different
	for (unsigned i = 0; i < n; i++) {
		if (a[i] != a[0]) {
			return false;
		}
	}
	return true;
} 

int main(int argc, char *argv[]) {

	/*File IO*/
    ArgumentManager am(argc, argv);
    string input = am.get("input"), output = am.get("output");

    if (argc != 3 && argc != 2) {
        cout << "Insufficient Arguments" << endl;
        return 1;
    }

  	/*Manual IO*/
	// string aa = "2.txt";
	// string input = "input"+aa, output = "output"+aa;
  	ifstream inFS(input.c_str());
    ofstream outFS(output.c_str());

	/*Variable Declaration*/
	string lines[1000], line;
	int number_of_lines = 0, result = 0, temp_int, counter_of_results = 0;
	bool isValid = true, isEqual = false;	

	/*Getting input lines*/
	while (getline(inFS, line)) {
		if (line == "") continue;
		lines[number_of_lines++] = line;
		// cout << line << endl; 
	} //end while
	
	cout << endl << endl;


	/*If the file is empty*/
	if (number_of_lines == 0) {
    	cout << "warning: file is empty, nothing will be added to the stack" << endl;
    	outFS << "";
    	return 0;
	}

	string str, newString;
	int resultsArray[number_of_lines];

	/*Cleaning the input*/
	for (int i = 0; i < number_of_lines; ++i) {
		newString = lines[i];
		string temp = "0";
		if (newString[0] == '+' || newString[0] == '-') {
			newString = temp + newString;
		}

		newString = findAndReplace(newString, "(-", "(0-");
		newString = findAndReplace(newString, "{-", "{0-");
		newString = findAndReplace(newString, "[-", "[0-");
		newString = findAndReplace(newString, "(+", "(0+");
		newString = findAndReplace(newString, "{+", "{0+");
		newString = findAndReplace(newString, "[+", "[0+");
		// cout << newString << endl;
    newString = simplify(newString);
		lines[i] = newString;
		newString = "";
	}

	/*For loop to calculate if input is valid and equal or incorrect*/
	for (int j = 0; j < number_of_lines; ++j) {
		str = lines[j];

		// cout << j << endl;
		for (int i = 0; i < str.length(); ++i) {
			if (isalpha(str[i])) {
				newString += indexOf(str[i]);
			} else {
				newString += str[i];
			}
			newString += " ";
		}
		// cout << j+1 << ": " << convert_alpha_to_num(newString) << endl;
		// cout << j+1 << ": " << evaluate(convert_alpha_to_num(newString)) << endl;
		/*Find out error or else compute the result*/
		if (areThereParenthesis(newString)) {
			if (areParanthesisBalanced(newString)) {
				newString = switch_brackets(newString);
				temp_int = evaluate(newString);
				// cout << temp_int << endl;
			} else {
				outFS << "Error at: " << j+1 << endl;
				cout << "Error at: " << j+1 << endl;
				isValid = false;
			} 
		} else {
			newString = switch_brackets(newString);
			temp_int = evaluate(newString);
		}
		resultsArray[counter_of_results++] = temp_int;
		newString = "";
	}

	/*Checks if all equations yield equal results iff the equation is valid*/
	if (areSame(resultsArray, counter_of_results) == true && isValid == true) {
		outFS << "Yes" << endl;
		cout << "Yes";
	} else if (isValid == true) {
		outFS << "No" << endl;
		cout << "No";
	}

	inFS.close();
	outFS.close();
	return 0;
}