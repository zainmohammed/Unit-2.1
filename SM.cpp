#include <iostream>;
#include<iomanip>;
#include <string>;

using namespace std;

// NodeType Class for creating node object in the linked list
// Integer info is used to store the value of the node
// Column is used to store the node index column in the linkedList
// NodeType *next is used to point to the next node generating a linear linked linkedList
class NodeType{
public:
	int info;
	int column;
	NodeType *next;	
public:
	NodeType(){
		info = 0;
		column = 0;
		next = NULL;
	}
};

// LinkedList Class for creating a linked list of NodeType objects
// It contains NodeType objects called head and a tail which store the head (first node) and linkedList (last node) in the linkedList
// The integer size is used to store the number of nodes in the linked list
class LinkedList{
public:
	NodeType * head;
	NodeType * tail;	

public:
	LinkedList();
	~LinkedList();
	void insertAtBeginning(int column, int value);
	void insertAtEnd(int column, int value);
	void insertItemAt(int column, int value);
	void insertRow(NodeType *other);
};

// Constructor of the LinkedList Class 
// Initialize the variables 
LinkedList::LinkedList(){
	head = NULL;
	tail = NULL;
}

// Destructor used to delete/clear the all node objects in the linked linkedList from the heap memory
LinkedList::~LinkedList(){
	NodeType * current = head;
	while (current != NULL){
		current = current->next;
		delete head;
		head = current;
	}
	head = NULL;
	tail = NULL;
}

void LinkedList::insertAtBeginning(int column, int value){
	// Create a new node and store the column and value in it
	NodeType * newNode = new NodeType;
	newNode->info = value;
	newNode->column = column;

	// Check if the linkedList is empty		
	// Then point head & tail to new node

	if (head == NULL){
		head = tail = newNode;
	}

	// Else if the linkedList is not empty						
	else{
		newNode->next = head;				// Point the new node to the first node (which the head is pointing)	
		head = newNode;						// Then change the head to point to the new node
	}
}

void LinkedList::insertAtEnd(int column, int value){
	// Create a new node and store the column and value in it		
	NodeType * newNode = new NodeType;
	newNode->column = column;
	newNode->info = value;

	// If the linkedList is empty then assign the new node to head & tail
	if (head == NULL)
		head = tail = newNode;
	// Else point the current last node to the new node, then change the tail to new node
	else{
		tail->next = newNode;
		tail = newNode;
	}

}

void LinkedList::insertItemAt(int column, int value){
	// Check if the linkedList is empty OR the first node's column is bigger than the new node's column
	// If any of the condition is triggered than call insertAtBeginning method to insert new node at the beginning of the linkedList		
	if (head == NULL || head->column > column){
		insertAtBeginning(column, value);

	}
	// If the new node's column is bigger than the last node's column
	// Then call the insertAtEnd method to insert the new node at the end of the linkedList
	else if (tail->column < column){
		insertAtEnd(column, value);

	}

	// Else means the new node's column is in the middle of the linkedList
	// Then it will check the index of the new node
	else{
		// Create a node type to store the first node
		NodeType * prevNode = head;

		// Loop until the current nodetype's column is smaller than the input column
		while (prevNode->column < column && prevNode != NULL){
			// Check if the next node column is greater than input column
			if (prevNode->next->column > column)
				// If YES then break out of the loop
				break;
			prevNode = prevNode->next;
		}

		// If the prevNode's column is same as input column,
		if (prevNode->column == column){
			// then change the info directly
			prevNode->info = value;
		}
		// Else means input column is after prevNode column
		else {
			// Create a new node type and store the value and column
			NodeType * newNode = new NodeType;
			newNode->info = value;
			newNode->column = column;
			newNode->next = prevNode->next;
			prevNode->next = newNode;
		}

	}
}

// This method is for inserting the matrix's row into another matrix row
void LinkedList::insertRow(NodeType *other){
	// Loop through all node in other linkedList,
	// and make a "deep copy" of other nodes
	while (other != NULL){
		insertAtEnd(other->column, other->info);
		other = other->next;
	}
}

class SM{
public:
	LinkedList *linkedList;
	int n, m;

public:
	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void addSM(SM &other);
};

SM::SM(int rows, int columns){	
	n = rows;
	m = columns;
	linkedList = new LinkedList[n];
}
	
SM::~SM(){	
	delete[] linkedList;
}

void SM::readElements(){
	// Initialize array linkedList
	

	cout << "Please follow the sequence of element when enter the data for the matrix. " << endl;
	cout << "The sequence is as follow : \nrow >> column >> value " << endl;
	cout << "*Using a space or enter to separate the elements." << endl;
	cout << "*Enter 0 0 0 to finish.\n" << endl;

	int row=1, column=1, value=1;
	int count = 1;
	do{
		cout << "Data (" << count << ") >> ";
		cin >> row;
		cin >> column;
		cin >> value;
		
		if (row == 0 && column == 0 && value == 0)
			break;

		// If the input index of row is greater than size of row then show error message
		if (row >= n ){
			cout << "\nInvalid data found!\nThe maximum number of row is " << n << "! Please enter a valid number of row!\n" << endl;
		}
		// Else if the input index of column is greater than size of column then show error message
		else if (column >= m){
			cout << "\nInvalid data found!\nThe maximum number of column is " << m << "! Please enter a valid number of column!\n" << endl;
		}
		// Else the insert the data into the linkedList
		else{
			count++;			
			linkedList[row].insertItemAt(column, value);
		}

	} while ((row != 0 || column != 0 || value != 0));
	
	cout << endl;
}

void SM::printMatrix(){
	// Loop through the rows of matrix
	for (int i = 0; i < n; i++){
		// Set the field width to 7
		cout << setw(7);
		NodeType *current = linkedList[i].head;		
		// Loop through the columns of matrix
		for (int j = 0; j < m; j++){		
			// Check if the linkedList is empty,
			// if not empty then check the nodes in the linkedList
			if (current != NULL){			
				// Check if the node's column is the same as current column index
				// if yes then print the node's info in the matrix
				if (current->column == j){					
					cout << current->info << setw(7) ;					
					current = current->next;
				}
				// Else then print 0
				else
					cout << "0" << setw(7);
			}
			// Else if it is empty then print 0
			else{
				cout << "0" << setw(7);
			}
		}		
		cout << endl;
	}
}

void SM::addSM(SM &matrixB){	

	// =============================================
	// ** ACurrent is used to travel through the linkedList nodes in matrix A
	// ** BCurrent is used to travel through the linkedList nodes in matrix B
	// =============================================


	// Loop through the rows in the matrix
	for (int i = 0; i < n; i++){
	
		NodeType *ACurrent = NULL;
		
		// If the matrixB's row is empty, then skip to next row.
		if (matrixB.linkedList[i].head != NULL){								
																	
			// Initialize BCurrent and point to the matrixB's row head (first node in the linkedList)
			NodeType *BCurrent = matrixB.linkedList[i].head;

			// Loop through all the nodes in matrixB's particular row
			while (BCurrent != NULL){		

				// Check if matrixA's row is empty
				// If not empty then do some operation to sum up both matrixes' row together
				if (linkedList[i].head != NULL){								
					// If the ACurrent nodetype is not pointing anything,
					// then point it to the matrixA's particular row head
					if (ACurrent == NULL){								
						ACurrent = linkedList[i].head;
					}
					
					// Check if the matrixA's row first node column is bigger than the BCurrent's column,
					// If YES insert the BCurrent node at the beginning of matrixA's linkedList
					if (linkedList[i].head->column > BCurrent->column)							
						linkedList[i].insertAtBeginning(BCurrent->column, BCurrent->info);	
					
					// Else if the matrixA's row tail's column is smaller than BCurrent's column,
					// If YES inset the BCurrent at the end of matrixA's linkedList
					else if (linkedList[i].tail->column < BCurrent->column)					
						linkedList[i].insertAtEnd(BCurrent->column, BCurrent->info);		
					
																			
					else{		
						// Loop when ACurrent's column is smaller than BCurrent's column 
						// OR ACurrent is NOT equal to NULL (still have node in the linkedList)
						while (ACurrent->column < BCurrent->column && ACurrent != NULL){
							// Check if ACurrent next node's column is bigger than BCurrent's column							
							if (ACurrent->next->column > BCurrent->column)
								break;
							ACurrent = ACurrent->next;
						} 
						

						// If both ACurrent and BCurrent column are the same then sum up the info 
						if (ACurrent->column == BCurrent->column){						
							ACurrent->info = BCurrent->info + ACurrent->info;
						}						
						// Else insert the new node after the ACurrent
						else{																
							NodeType * newNode = new NodeType;
							newNode->column = BCurrent->column;
							newNode->info = BCurrent->info;
							newNode->next = ACurrent->next;
							ACurrent->next = newNode;													
						}
					}
				}

				// Insert whole BCurrent's row into AMatrix's row,
				// then break out of the loop and move to next row
				else{
					linkedList[i].insertRow(BCurrent);					
					break;
				}

				// If the BCurrent has next node then point to the next one
				if (BCurrent->next != NULL)							
					BCurrent = BCurrent->next;
				//else break out of the loop and move to next row
				else
					break;												
			}				
		}
	}
}


int main(){	
	int n, m;
	cout << "=================================== Welcome ===================================\n" << endl;
	cout << "This is a console application which will get the input from the user for two \nmatrices and perform an addition of the two matrices.\n";
	cout << "This application is using LINKED LIST data structure to improve the performance and efficiency of matrix handling.\n" << endl;
	cout << "===============================================================================\n" << endl;

	do{
		cout << "Please enter the number of row(s) and column(s) for the matrix " << endl;
		cout << "Row(s) >> ";
		cin >> n;
		cout << "Column(s) >> ";
		cin >> m;
		cout << "\n" << endl;

		if (n <= 0 || m <= 0)
			cout << "The number of row and column must be more than zero!\n" << endl;;
	} while (n <= 0 || m <= 0);

	SM sm = SM(n, m);
	SM sm2 = SM(n, m);

	cout << "First Matrix:" << endl;
	sm.readElements();	
	
	cout << "Second Matrix:" << endl;
	sm2.readElements();

	cout << "First Matrix:" << endl;
	sm.printMatrix();
	cout << endl;
	cout << "Second Matrix:" << endl;
	sm2.printMatrix();
	cout << endl;

	sm.addSM(sm2);
	cout << "After Sum:" << endl;
	sm.printMatrix();
	cout << endl;
	system("PAUSE");
	return 0;
}