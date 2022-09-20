// FILE: sequence.h
// CLASS PROVIDED: Sequence
//
// TYPEDEFS the sequence class:
//   typedef value_type
//     Sequence::value_type is the data type of values in the sequence. Any primative C++ data type
//     (int, double, bool, char, etc.), or a class with a default constructor, a destructor, an assignment operator,
//		and a copy constructor can be used.
//
//   typedef size_type
//     Sequence::size_type is the data type of any variable the number of items in a sequence.
//
// CONSTRUCTORS for the sequence class:
//	Sequence( size_type numElts = 0 )
//		Postcondition: Creates an empty sequence (numElts == 0) or
//		a sequence of numElts items indexed from 0 ... (numElts - 1).
//
//	Sequence( const Sequence& seq )
//		Postcondition: Creates a (deep) copy of sequence seq.
//
// DESTRUCTOR for the Sequence class
//		Postcondition: Destroys all items in the sequence and release the memory associated with the sequence
//
// INFORMATIONAL / ACCESSOR MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool empty( ) const
//     Postcondition: A true return value indicates size of the sequence is zero.
//
//   const int& front() const
//     Precondition: The size of the sequence is greater than zero.
//     Postcondition: The return value is a reference to the first item in the sequence.
//
//   const int& back() const
//     Precondition: The size of the sequence is greater than zero.
//     Postcondition: The return value is a reference to the last item in the sequence.
//
// MUTATOR MEMBER FUNCTIONS for the sequence class:
//	Sequence& operator=( const Sequence& seq )
//		Postcondition: The current sequence is released and replaced by a (deep) copy of sequence (seq).
//		A reference to the copied sequence is returned.
//
//	value_type& operator[]( size_type position )
//		Precondition: The position satisfies ( position >= 0 && position <= last_index( ) ).
//		Postcondition: The return value is a reference to the item at index position in the sequence.
//
//	void push_back( const value_type& item )
//		Postcondition: The value of item is append to the sequence.
//
//	void pop_back( )
//		Precondition: The size of the sequence is greater than zero.
//		Postcondition: The item at the end of the sequence is deleted and size of the sequence is reduced by one.
//
//	void insert( size_type position, value_type item )
//		Precondition: The position satisfies ( position >= 0 && position <= last_index( ) ).
//		Postcondition: The value of item is inserted at position and the size of sequence is increased by one.
//
//	void erase( size_type position, size_type count = 1 )
//		Precondition: The position satisfies ( position >= 0 && position + count - 1 <= last_index( ) ).
//		Postcondition: The positions / items in the sequence at ( position ... (position + count - 1) ) are deleted.
//
//	void clear()
//		Postcondition: All items in the sequence deleted and the memory associated with the sequence is released.
//
// I/O MEMBER FUNCTION
//	ostream& operator<< ( ostream& os, const Sequence& theSequence )
//		Postcondition: The updated ostream object is returned.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
// ERROR CONDITIONS
//  1.	All member functions that allocate memory for a sequence should throw bad_alloc if the memory allocation fails (this should happen automatically so no action is required on your part).
//	2.	All members function that access sequence items by position should throw and exception
//		if the position is outside the bounds of the sequence
#pragma once

#include <iostream>
#include <exception>

using namespace std;

class Sequence
{

	// The following declarations describe the functions that you must implement.
	// You SHOULD NOT CHANGE any of the following PUBLIC declarations.
public:
	typedef int value_type;			  // data type of sequence items
	typedef unsigned int size_type; // data type of sequence counts and / or sizes

	Sequence(size_type sz = 0); // creates a sequence indexed from 0 ... sz

	Sequence(const Sequence &s); // create a sequence from the existing sequence s
	~Sequence();					  // destroys the sequence

	Sequence &operator=(const Sequence &s); // assign sequence s to the sequence

	value_type &operator[](size_type p); // return a reference to the item at index position p

	void push_back(const value_type &v); // add v to the end of the sequence
	void pop_back();							 // remove item at the end of the sequence

	void insert(size_type p, value_type v); // insert the item v in the sequence at index position p

	const value_type &front() const; // returns a reference to the first item in the sequence
	const value_type &back() const;	// returns a reference to the last item in the sequence

	bool empty() const; // returns true if the sequence is empty
	size_type size() const;

	void clear();										// clears the sequence returning it to the empty state
	void erase(size_type p, size_type n = 1); // deletes n number items starting a index position p
	bool traverser();
	// YOU CAN MODIFY the following private declarations as needed to implement your sequence class
private:
	// If you choose to use a linked list, use the following
	// private inner class for linked list nodes
	// All data elements are public, since only class sequence can see SequenceNodes
	class SequenceNode
	{
	public:
		SequenceNode *next;
		SequenceNode *prev;
		value_type elt;

		SequenceNode()
		{
			next = nullptr;
			prev = nullptr;
		}

		SequenceNode(value_type item)
		{
			next = nullptr;
			prev = nullptr;
			elt = item;
		}

		~SequenceNode(){};
	};

	// MEMBER DATA.  These are the data items that each sequence object will contain.  For a
	// doubly-linked list, each sequence will have a head and tail pointer, and numElts
	SequenceNode *head;
	SequenceNode *tail;
	size_type numElts; // Number of elements in the sequence

}; // End of class Sequence

// You must also implement the << operator.  Do not change this declaration:
ostream &operator<<(ostream &, Sequence &);
