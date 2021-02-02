#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  delete head_;
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  /* your code here */
  Node *newNode = new Node(ndata);
  if (p == NULL) {
    Node *temp = head_;
    temp->previous = newNode;
    newNode->next = temp;
    head_= newNode;
    delete temp;
  } else {
    if (p->next == NULL) {
      p->next = newNode;
      newNode->previous = p;
    } else {
      Node *next = p->next;
      next->previous = newNode;
      newNode->next = next;
      newNode->previous = p;
      p->next = newNode;
      delete next;
    }
  }
  length_++;
  return newNode;
}

/**
 * Helper function to swap two nodes that are side by side.
 *
 * @param first = The node that comes first in the chain.         
 * @param second = The node that comes second in the chain.
 */
void Chain::swapSideBySide(Node *first, Node *second) {
  if (head_ == first) {
    Node * temp = second->next;
    first->next = temp;
    temp->previous = first;
    first->previous = second;
    second->next = first;
    second->previous = NULL;
    head_ = second;
    delete temp;
    return;
  } else if (second->next == NULL) {
    //if second is the tail
    Node *temp = first->previous;
    second->previous = temp;
    temp->next = second;
    second->next = first;
    first->previous = second;
    first->next = NULL;
    delete temp;
    return;
  } else {
    Node *previous_p = p->previous;
    Node *next_q = q->next;

    previous_p->next = q;
    q->previous = previous_p;
    q->next = p;
    p->previous = q;
    p->next = next_q;
    next_q->previous = p;

    delete previous_p;
    delete next_q;
    return;
  }
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  /* your code here */
  if (p == NULL || q == NULL || p == q) {
    return;
  }
  //if there is only 1 block in the chain, return immediately
  if (length_ == 1) {
    return;
  }
  //if there are only 2 blocks in the chain
  if (length_ == 2) {
    if (head_ == p) {
      head_ = q;
      q->previous = NULL;
      q->next = p;
      p->next = NULL;
      p->previous = q;
      return;
    } else {
      head_ = p;
      p->previous = NULL;
      p->next = q;
      q->next = NULL;
      q->previous = p;
      return;
    }
  }
  // if the two nodes are side by side
  if (p->next == q){
    swapSideBySide(p, q);
    return;
  } else if (q->next == p) {
    swapSideBySide(q, p);
    return;
  }
  //Otherwise:
  Node *previous_p = p->previous;
  Node *next_p = p->next;
  Node *previous_q = q->previous;
  Node *next_q = q->next;

  if (previous_p == NULL) {
    //This means p was the head
    q->previous = NULL;
    q->next = next_p;
    next_p->previous = q; 
    head_ = q;
  } else {
    q->previous = previous_p;
    previous_p->next = q;
    q->next = next_p;
    //if p was not the original tail
    if (next_p != NULL) {
      next_p->previous = q;
    }
  }
  if (previous_q == NULL) {
    //This means q was the head
    p->previous = NULL;
    p->next = next_q;
    next_q->previous = p;
    head_ = p;
  } else {
    p->previous = previous_q;
    previous_q->next = p;
    p->next = next_q;
    //if q was not the original tail
    if (next_q != NULL) {
      next_q->previous = p;
    }
  }
  delete previous_p;
  delete next_p;
  delete previous_q;
  delete next_q;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  /* your code here */
}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  /* your code here */
}
