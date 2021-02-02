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

void Chain::swapHeadTail(Node *first, Node *second) {
  Node * previous_second = second->previous;
  second->previous = NULL;
  second->next = head_->next;
  head_->next->previous = second;
  first->next = NULL;
  first->previous = previous_second;
  previous_second->next = first;
  delete previous_second;
  head_ = second;
}

void Chain::swapHead(Node *head, Node *q) {
  Node *previous_q = q->previous;
  Node *next_q = q->next;
  q->previous = NULL;
  q->next = head_->next;
  head->previous = previous_q;
  previous_q->next = head;
  head->next = next_q;
  next_q->previous = head;
  head_ = q;
  delete previous_q;
  delete next_q;
  return;
}

void Chain::swapTail(Node *tail, Node *q) {
  Node *previous_q = q->previous;
  Node *previous_tail = tail->previous;
  Node *next_q = q->next;
  q->next = NULL;
  q->previous = previous_tail;
  previous_tail->next = q;
  tail->previous = previous_q;
  previous_q->next = tail;
  tail->next = next_q;
  next_q->previous = tail;
  delete previous_tail;
  delete previous_next;
  delete next_q;
  return;
}

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

  if (p->next == q){
    swapSideBySide(p, q);
    return;
  } else if (q->next == p) {
    swapSideBySide(q, p);
    return;
  }
  //if you are swapping the head and tail
  if (head_ == p && q->next == NULL) {
    swapHeadTail(p, q);
    return;
  } else if (head_ == q && p->next == NULL) {
    swapHeadTail(q, p);
    return;
  }

//if one of the nodes is the head of the chain
  if (head_ == p) {
    swapHead(p, q);
    return;
  } else if (head_ == q) {
    swapHead(q, p);
    return;
  }

//if one of the nodes is the tail of the chain
  if (p->next == NULL) {
    swapTail(p, q);
    return;
  } else if (q->next == NULL) {
    swapTail(q, p);
    return;
  }
  Node *previous_p = p->previous;
  Node *next_p = p->next;

  Node *previous_q = q->previous;
  Node *next_q = q->next;

  previous_p->next = q;
  previous_q->next = p;
  p->previous = previous_q;
  q->previous = previous_p;

  next_p->previous = q;
  next_q->previous = p;
  p->next = next_q;
  q->next = next_p;

  delete previous_p;
  delete previous_q;
  delete next_p;
  delete next_q;
  return;
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
