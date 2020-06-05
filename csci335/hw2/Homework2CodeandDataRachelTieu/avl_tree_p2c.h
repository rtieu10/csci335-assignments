// Rachel Tieu
// 3-1-20
// This file holds the AVL class, and holds the member functions
// of it, in this AVL file, we modify the double rotation
// functions

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }

    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );

        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x , float& removecounter)
    {
        remove( x, root , ++removecounter);
    }

    // @x: the object that we are trying to find
    // @post: this function will return the found object
    Comparable find(const Comparable & x) const{
      return find(x,root);
    }

    // @x: the object that we are looking for
    // @counter: a float varibale that gets incremented with every recursive call
    //          to the private function find
    Comparable find(const Comparable & x, float & counter) const{
      return find(x, root, ++counter);
    }

    // @post: this function will calls a private function which will return
    //        the private counter function
    int TotalNodeCount(){    //public function that calls the counter function
      return NumofNodes(root);
    }

    // @&node: the node in the tree that we are currently finding the depth of
    // @post: this function calls the private Depth function
    int Depth(AvlTree &node){
      return DepthofNode(node,root);
    }

    // @post: a public member function which calls the private function which
    //    calculates the internal path length
    int InternalPathLength(){
      return InternalPathLength(root);
    }

    // @post: this function calls the private internal path function, and the
    //        private node counter function and divide them, it returns a float
    float AverageDepth(){
      return InternalPathLength(root) / NumofNodes(root);
    }

    // @post: this function will call the public member function that calculates
    //        the average depth and divides it by the log2 of the number of nodes
    //
    float LogRatio(){
      return AverageDepth()/log2(NumofNodes(root));
    }


  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }

        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else{    //if the elements are equal, then we merge part 2a
            (t->element).Merge(x);     //calling the Merge function from the SequenceMap class
        }
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else{     //if the element is equal to the node in the tree
          (t->element).Merge(x);        //calling the Merge function
        }

        balance( t );
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    // @x: this is a Comparable object which is the SequenceMap object we are removing
    // @t: the tree that we are currently working on, and accessing its nodes where the
    //     SequenceMap objects are stored
    // @removecounter: a float character which will be incremented everytime the remove
    //     function is recursively called
    // void remove( const Comparable & x, AvlNode * & t , float& removecounter)
    // {
    //     if( t == nullptr )
    //         return;   // Item not found; do nothing
    //
    //     if( x < t->element ){
    //         removecounter++;
    //         remove( x, t->left,removecounter );
    //         return;
    //     }
    //     else if( t->element < x ){
    //         removecounter++;
    //         remove( x, t->right, removecounter);
    //         return;
    //     }
    //     else if( t->left != nullptr && t->right != nullptr ) // Two children
    //     {
    //         t->element = findMin( t->right )->element;
    //         removecounter++;
    //         remove( t->element, t->right , removecounter);
    //         return;
    //     }
    //     else
    //     {
    //         AvlNode *oldNode = t;
    //         t = ( t->left != nullptr ) ? t->left : t->right;
    //         delete oldNode;
    //     }
    //
    //     balance( t );
    //     return;
    // }


    void remove( const Comparable & x, AvlNode * & t , float& removecounter)
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
            cout << "Not" << removecounter << endl;
        if( x < t->element ){
            cout << "Left" << endl;
            removecounter++;
            remove( x, t->left,removecounter );
            return;
        }
        else if( t->element < x ){
            cout << "Right" << endl;
            removecounter++;
            remove( x, t->right, removecounter);
            return;
        }
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
          cout << "Two" << endl;
            t->element = findMin( t->right )->element;
            removecounter++;
            cout <<
            remove( t->element, t->right , removecounter);
            return;
        }
        else
        {
            cout << "Found" << removecounter << endl; 
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }

        balance( t );
        return;
    }




    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;

        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */


      Comparable find(const Comparable & x, AvlNode *t) const{
       if( t == nullptr )
           return Comparable("Not Found", "Not Found");
       else if( x < t->element )
           return find(x, t->left);
       else if( t->element < x )
           return find(x, t->right);
       else
           return (t->element);    // Match

       }

      // @x: this is the item that we are currently searching for
      // @t: the node of the tree that we are currently working on
      // @counter: a float variable which will be incremented everytime find is
      //        recursively called
      Comparable find(const Comparable & x, AvlNode *t, float& counter) const{
        if( t == nullptr ){
            return Comparable("Not Found", "Not Found");
        }
        else if( x < t->element ){
            counter++;
            return find(x, t->left, counter);
        }
        else if( t->element < x ){
            counter++;
            return find(x, t->right, counter);
        }
        else{
            return (t->element);    // Match
        }
      }

    // @x: the object that we are currently looking to see if the tree
    //      contains it
    // @t: the pointer to the node of the tree that we are traversing through
    bool contains( const Comparable & x, AvlNode *t ) const
     {
         if( t == nullptr ){
             return false;
          }
         else if( x < t->element ){
             return contains( x, t->left );
          }
         else if( t->element < x ){
             return contains( x, t->right );
          }
         else{
             return true;    // Match
        }

     }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */


    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
    * Double rotate binary tree node: first left child.
    * with its right child; then node k3 with new left child.
    * For AVL trees, this is a double rotation for case 2.
    * Update heights, then set new root.
    */
    void doubleWithLeftChild( AvlNode * & t )
    {
      AvlNode *k2 = t->left->right;
      t->left->right = k2->left;
      k2->left=t->left;

      t->left->height = (max( height( t->left->left ), height( t->left->right )) +1);
      k2->height = (max( height( k2->right), t->left->height) +1);
      t->left = k2;


      AvlNode *k3 = t->left;
      t->left = k3->right;
      k3->right=t;

      t->height = (max( height( t->left ), height( t->right)) +1);
      k3->height = (max( height( k2->left), t->height) +1);
      t = k3;
    }

    /**
    * Double rotate binary tree node: first right child.
    * with its left child; then node k1 with new right child.
    * For AVL trees, this is a double rotation for case 3.
    * Update heights, then set new root.
    */
    void doubleWithRightChild( AvlNode * & t )
    {
      AvlNode *k1 = t->right->left;
      t->right->left = k1->right;
      k1->right=t->right;

      t->right->height = (max( height( t->right->left ), height( t->right->right )) +1);
      k1->height = (max( height( k1->left), t->right->height) +1);
      t->right = k1;


      AvlNode *k3 = t->right;
      t->right = k3->left;
      k3->left=t;

      t->height = (max( height( t->left ), height( t->right)) +1);
      k3->height = (max( height( k3->right), t->height) +1);
      t = k3;

    }

    // @t: the root of the tree that we are currently iterating through
    // @ post: this function will traverse through a tree, and count the numebr of
    //       nodes in the tree
    int NumofNodes(AvlNode *t) const{
      if(t == nullptr){
        return 0;
      }
      return 1 + NumofNodes(t->left) + NumofNodes(t->right);
      }


    // @node: this is the node of the tree, tha twe are currently visiting
    // @root: this is the pointer to the root of the tree, and we consistently update
    //        the root value we are currently visiting
    // @post: this function finds the depth of a single node in the tree
    float DepthofNode(AvlNode* node, AvlNode* root){
      if(root == nullptr){
        return 0;
      }
      else if(node->element < root->element){
        return 1+DepthofNode(node, root->left);
      }
      else if(root->element < node->element){
        return 1+DepthofNode(node, root->right);
      }
      else{    //if its equal
        return 0;
      }
    }


    // @node: the pointer to the node that we are currently at
    // @post: this function counts the internal path length of the whole tree
    float InternalPathLength(AvlNode* node){
      if(node == nullptr){
        return 0;
      }
      else{
        return DepthofNode(node,root)+InternalPathLength(node->left) + InternalPathLength(node->right);
      }
    }



};

#endif
