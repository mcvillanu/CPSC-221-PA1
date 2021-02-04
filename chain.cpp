#include "chain.h"
#include <cmath>
#include <iostream>
#include <limits>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  clear();
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
  Node * newNode = new Node(ndata);
  if (p == NULL) {
    if (this->head_ == NULL) {
      this->head_ = newNode;
      newNode->next = NULL;
      newNode->prev = NULL;
    } 
    else {
      this->head_->prev = newNode;
      newNode->next = this->head_;
      this->head_ = newNode;
      newNode->prev = NULL;
    }
  } else {
    if (p->next == NULL) {
      //if p is the tail
      p->next = newNode;
      newNode->prev = p;
      newNode->next = NULL;
    } else {
      
      Node *next = p->next;
      next->prev = newNode;
      newNode->next = next;
      newNode->prev = p;
      p->next = newNode;
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
  if (first->prev == NULL) {
    //if first is the head node
    Node * temp = second->next;
    first->next = temp;
    temp->prev = first;
    first->prev = second;
    second->next = first;
    second->prev = NULL;
    head_ = second;
    return;
  } else if (second->next == NULL) {
    //if second is the tail
    Node *temp = first->prev;
    second->prev = temp;
    temp->next = second;
    second->next = first;
    first->prev = second;
    first->next = NULL;
    return;
  } else {
    Node *previous_first = first->prev;
    Node *next_second = second->next;

    previous_first->next = second;
    second->prev = previous_first;
    second->next = first;
    first->prev = second;
    first->next = next_second;
    next_second->prev = first;
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
    if (p->prev == NULL) {
      head_ = q;
      q->prev = NULL;
      q->next = p;
      p->next = NULL;
      p->prev = q;
      return;
    } else {
      head_ = p;
      p->prev = NULL;
      p->next = q;
      q->next = NULL;
      q->prev = p;
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
  Node *previous_p = p->prev;
  Node *next_p = p->next;
  Node *previous_q = q->prev;
  Node *next_q = q->next;

  if (previous_p == NULL) {
    //This means p was the head
    q->prev = NULL;
    q->next = next_p;
    next_p->prev = q; 
    head_ = q;
  } else {
    q->prev = previous_p;
    previous_p->next = q;
    q->next = next_p;
    //if p was not the original tail
    if (next_p != NULL) {
      next_p->prev = q;
    }
  }
  if (previous_q == NULL) {
    //This means q was the head
    p->prev = NULL;
    p->next = next_q;
    next_q->prev = p;
    head_ = p;
  } else {
    p->prev = previous_q;
    previous_q->next = p;
    p->next = next_q;
    //if q was not the original tail
    if (next_q != NULL) {
      next_q->prev = p;
    }
  }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  Node * curr = head_;
  if (head_ == NULL) {
    delete head_;
  }
  Node * next = NULL;
  while (curr != NULL) {
    next = curr->next;
    delete curr;
    curr = NULL;
    curr = next;
  }
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
  this->length_ = other.length_;
  Node * curr = other.head_;
  Node * copy = new Node(curr->data);
  this->head_ = copy;
  while (curr != NULL) {
    if (curr->next != NULL) {
      copy->next = new Node(curr->next->data);
    }
    if (curr->prev != NULL) {
      copy->prev = new Node(curr->prev->data);
    }
    copy = copy->next;
    curr = curr->next;
  }
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
  double max = -std::numeric_limits<double>::max();
  Node * leftMost = head_;
  Node * index = head_;
  
  while (index != NULL){
    for (Node * B = index; B != NULL; B = B->next){
      double bMin = std::numeric_limits<double>::max();

      for (Node * other = index; other != NULL; other = other->next){
        if(B != other){
          bMin = min(bMin, (other->data).distanceTo(B->data));
        }
      }

      if(bMin > max){
        max = bMin;
        leftMost = B;
      }
    }

    this->swap(index, leftMost);
    index = leftMost->next;
    max = -std::numeric_limits<double>::max();
  }
}
