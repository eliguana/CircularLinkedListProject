// CircularLinkedListProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Part 1: Build Your Own Linked List
Implement and test a linked list that supports adding, searching, removing, and printing items. Do not use std::list.

Part 2: Monopoly Game
Use your linked list to build a circular board with at least 10 properties.

Each property stores its name, cost, owner, and next pointer.

Players move around the board, wrapping back to the beginning.

Players can buy unowned properties, but cannot buy owned properties.

Simulate at least 10 turns and print the results

BONUS POINTS IF YOU CREATE A GUI
Briefly explain the time complexity of adding, searching, removing, moving, and traversing.

====== NOTES =====
	- Resources:
	- https://www.youtube.com/watch?v=hQFIAUQbYT0&list=PLLhBy6YSIT0AObjhfXVn2wHR4PqyS9s_y&index=5
	-

	- In a circular linked list, last node points to the first node, creating a loop.
	- Traversal continues indefinitely until a stopping condition is met.
	- nullptr is used to indicate the end of the list, but in a circular linked list, it is not used for traversal.
	- Insertion in circular linked list can be done at the beginning, end, or a specific position.
	- time complexity of adding, searching, removing, moving, and traversing in a circular linked list is O(n) in the worst case,
	where n is the number of nodes in the list. However, if we have a pointer to the last node, we can perform insertion at the end in O(1) time.


*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Part 1: Circular Linked List
class Node {
public:
	int data;
	Node* next;
	Node(int val) : data(val), next(nullptr) {}
};

//traversal circular linked list
void traversal(Node* head) {
	Node* current = head;
	do {
		cout << current->data << " ";
		current = current->next;
	} while (current != head);
	cout << endl;
}

//traversal circular linked list in a loop
void traversalInLoop(Node* head) {

	Node* current = head;
	int k = 10;
	while (current != nullptr && k--) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

// Insertion at the start of a circular linked list
void insertAtStart(Node*& head, int value) {	//reads from right to left, so head is passed by reference to update the head pointer in the calling function
	Node* newNode = new Node(value);
	if (head == nullptr) {
		newNode->next = newNode; // Point to itself if the list is empty
		head = newNode;
		return;
	}
	Node* current = head;
	while (current->next != head) {
		current = current->next;
	}
	current->next = newNode; //changing the link from the last node to the head node
	newNode->next = head; //making the new node point to the head node
	head = newNode; //updating the head pointer to point to the new node
}

// Insertion at the end of a circular linked list
void insertAtEnd(Node*& head, int value) {
	Node* newNode = new Node(value);
	if (head == nullptr) {
		newNode->next = newNode; // Point to itself if the list is empty
		head = newNode;
		return;
	}
	Node* current = head;
	while (current->next != head) {
		current = current->next;
	}
	current->next = newNode; //changing the link from the last node to the head node
	newNode->next = head; //making the new node point to the head node
}

// Deletion at the start of a circular linked list
void deleteAtStart(Node*& head) {
	if (head == nullptr) {
		return; 
	}
	if (head->next == head) {
		delete head;
		head = nullptr;
		return;
	}
	Node* tail = head;
	while (tail->next != head) {
		tail = tail->next;
	}
	tail->next = head->next;
	Node* oldHead = head;
	head = head->next;
	delete oldHead;
}

// Deletion at the end of a circular linked list
void deleteAtEnd(Node*& head) {
	if (head == nullptr) {
		return; // List is empty, nothing to delete
	}
	if (head->next == head) {
		delete head;
		head = nullptr;
		return;
	}
	Node* prev = head;
	while (prev->next->next != head) {
		prev = prev->next;
	}
	Node* lastNode = prev->next;
	prev->next = head;
	delete lastNode;
}

//Part 2: Monopoly Game

struct ListNode {
	int cost;
	string name;
	string owner;
	ListNode* nextptr;

	ListNode(int propCost, string propName) {
		cost = propCost;
		name = propName;
		owner = "None";
		nextptr = nullptr;

	}
};

// Function to add a new property to the circular linked list
void addProperty(ListNode*& head, int cost, string name) {
	ListNode* newProperty = new ListNode(cost, name);
	if (head == nullptr) {
		newProperty->nextptr = newProperty; // Point to itself if the list is empty
		head = newProperty;
		return;
	}
	ListNode* current = head;
	while (current->nextptr != head) {
		current = current->nextptr;
	}
	current->nextptr = newProperty; //changing the link from the last node to the head node
	newProperty->nextptr = head; //making the new node point to the head node
}

// Function to print the properties in the circular linked list
void printProperties(ListNode* head) {
	if (head == nullptr) 
	{
		cout << "No properties available." << endl;
		return;
	}

	ListNode* current = head;
	do 
	{
		cout << "Property Name: " << current->name << ", Cost: " << current->cost << ", Owner: " << current->owner << endl;
		current = current->nextptr;
	} 
	while (current != head);

}

// Function to search for a property by name in the circular linked list
ListNode* searchProperty(ListNode* head, string name) {
	if (head == nullptr) {
		return nullptr; // List is empty
	}
	ListNode* current = head;
	do {
		if (current->name == name) {
			return current; // Property found
		}
		current = current->nextptr;
	} 
	while (current != head);
	return nullptr; // Property not found
}

// Function to remove a property from the circular linked list
bool removeProperty(ListNode*& head, string propertyName) {

	if (head == nullptr)
	{
		return false;
	}
	if (head->nextptr == head) 
	{
		if (head->name == propertyName) 
		{

			delete head;
			head = nullptr;

			return true;
		}

		return false;
	}

	ListNode* current = head;
	if (head->name == propertyName) {

		ListNode* tail = head;

		while (tail->nextptr != head) {

			tail = tail->nextptr;
		}

		tail->nextptr = head->nextptr;

		ListNode* oldHead = head;
		head = head->nextptr;

		delete oldHead;

		return true;
	}

	// Traverse the list to find the property to delete
	while (current->nextptr != head) {

		if (current->nextptr->name == propertyName) {

			ListNode* propertyToDelete = current->nextptr;
			current->nextptr = propertyToDelete->nextptr;
			delete propertyToDelete;

			return true;

		}

		current = current->nextptr;
	}

	return false;
}

// Class to represent the player
class Player {

public:
	string name;
	ListNode* position;
	Player(string playerName, ListNode* startPosition) {
		name = playerName;
		position = startPosition;
	}
	// Function to move the player a certain number of spaces around the board
	void move(int spaces) {
		cout << name << " spaces moved: " << spaces << endl;
		for (int i = 0; i < spaces; i++) {
			position = position->nextptr;
		}
		cout << name << " landed on " << position->name << endl;
	}

	// Function to buy the property the player is currently on
	void buyProperty() {
		if (position->owner != "None")
		{
			cout << position->name << " is already owned by " << position->owner << "." << endl;
			cout << name << " cannot buy this property." << endl;

			return;
		}

		// If the property is unowned, the player can buy it
		position->owner = name;
		cout << name << " bought " << position->name << " for $" << position->cost << "." << endl;
	}
};


int main() {

	//Testing:
	cout << "Testing cases: " << endl;

	// Create a circular linked list with two nodes
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);

	// Link the nodes to form a circular linked list
	n1->next = n2;
	n2->next = n1;

	// Set the head of the list
	Node* head = n1;

	// Test traversal
	traversal(head);
	traversalInLoop(head);

	// Test insertion at the start
	insertAtStart(head, 4);
	traversal(head);

	// Test insertion at the end
	insertAtEnd(head, 5);
	traversal(head);

	// Test deletion at the start
	deleteAtStart(head);
	traversal(head);

	// Test deletion at the end
	deleteAtEnd(head);
	traversal(head);

	//Part 2: Monopoly Game
	
	cout << "\n\nSpongebob Themed Monopoly Sim: " << endl;
	srand(time(0)); // Seed for random number generation

	ListNode* board = nullptr;

	addProperty(board, 0, "JAIL");
	addProperty(board, 10000, "Krusty Krab Ave");
	addProperty(board, 500, "Patrick's Rock Pt");
	addProperty(board, 100, "The Clarinet Shack Ln");
	addProperty(board, 670, "Weenie Hut Juniors St");
	addProperty(board, 800, "Cozy Pineapple Ave");
	addProperty(board, 300, "Driving School Lane");
	addProperty(board, 5000, "Bikini Bottom Ln");
	addProperty(board, 200, "Goo Lagoon Ave");
	addProperty(board, 50, "Chum Bucket St");

	printProperties(board);

	Player player1("Player 1", board);
	Player player2("Player 2", board);

	for (int move = 0; move < 10; move++)
	{
		cout << "\nMove # " << move << endl;
		int dice = rand() % 6 + 1; // Simulate a six sided dice roll (1-6)

		if (move % 2 == 0) 
		{
			player1.move(dice);
			player1.buyProperty();
		}
		else 
		{
			player2.move(dice);
			player2.buyProperty();
		}

		cout << "\n\nOwnership Status: " << endl;

		printProperties(board);

		cout << "\nSearching for Bikini Bottom	Ln..." << endl;

		ListNode* foundProperty =
			searchProperty(board, "Bikini Bottom Ln");

		if (foundProperty != nullptr) {

			cout << "Found: " << foundProperty->name
				<< " | Cost: $" << foundProperty->cost
				<< " | Owner: " << foundProperty->owner << endl;
		}
		else 
		{
			cout << "Property not found." << endl;
		}
	}
}

