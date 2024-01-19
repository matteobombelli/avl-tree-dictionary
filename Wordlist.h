// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Matteo Bombelli
// St.# : 301550507
// Email: mgb10@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
    };

    Node *root = nullptr;

    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //

    //
    // Returns true if wordlist is empty, false otherwise
    //
    bool is_empty()
    {
        return root == nullptr;
    }

    //
    // Returns the height of the AVL tree starting at node n
    //
    int height(Node* n)
    {
        if (n != nullptr)
        {
            int left_h = height(n->left);
            int right_h = height(n->right);
            if (left_h >= right_h)
            {
                return left_h + 1;
            }
            else
            {
                return right_h + 1;
            }
        }

        return 0;
    }

    //
    // Returns the height difference of the children of node n
    // a value >0 means the left node is higher
    // a value <0 means the right node is higher
    //
    int difference(Node* n)
    {
        int left_h = height(n->left);
        int right_h = height(n->right);
        return left_h - right_h;
    }

    //
    // Various rotations required for balancing
    //
    Node* ll_rotation(Node* n)
    {
        Node* p = n;
        Node* q = n->right;

        p->right = q->left;
        q->left = p;

        return q;
    }

    Node* lr_rotation(Node* n)
    {
        Node* p = n;
        Node* q = n->left;
        Node* r = n->left->right;

        p->left = r->right;
        q->right = r->left;
        r->right = p;
        r->left = q; 
        
        return r; 
    }

    Node* rl_rotation(Node* n)
    {
        Node* p = n;
        Node* q = n->right;
        Node* r = n->right->left;

        p->right = r->left;
        q->left = r->right;
        r->left = p;
        r->right = q; 
        
        return r; 
    }

    Node* rr_rotation(Node* n)
    {
        Node* p = n;
        Node* q = n->right;

        p->right = q->left;
        q->left = p;

        return q; 
    }

    //
    // Balances the tree to maintain a height difference <2
    //
    void balance()
    {
        int h = height(root);
        if (h > 1)
        {
            if (difference(root->left) > 0)
            {
                ll_rotation(root);
            }
            else
            {
                lr_rotation(root);
            }
        }
        else if (h < -1) 
        {
            if (difference(root->right) > 0)
            {
                rl_rotation(root);
            }
            else
            {
                rr_rotation(root);
            }
        }
    }

    //
    // Returns the number of nodes in the word list.
    //
    int num_different_words_rec(Node* n, int count) const
    {
        if (n == nullptr)
        {
            return count;
        }

        count = total_words_rec(n->left, count);
        count = total_words_rec(n->right, count);

        return ++count;
    }

    //
    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.
    //
    int total_words_rec(Node* n, int total) const
    {
        if (n == nullptr)
        {
            return total;
        }

        total = total_words_rec(n->left, total);
        total = total_words_rec(n->right, total);

        total += n->count;
        return total;
    }

    //
    // Returns the most common word in wordlist
    //
    Node* most_frequent_rec(Node* n, Node* max) const
    {
        if (n == nullptr)
        {
            return max;
        }

        most_frequent_rec(n->left, max);
        most_frequent_rec(n->right, max);

        if (n->count > max->count )
        {
            max = n;
        }
        return max;
    }


    //
    // Returns the number of singleton words in wordlist
    //
    int num_singletons_rec(Node* n, int count) const
    {
        if (n == nullptr)
        {
            return count;
        }

        count = num_singletons_rec(n->left, count);
        count = num_singletons_rec(n->right, count);
        
        if (n->count == 1)
        {
            ++count;
        }
        return count;
    }

    //
    // Prints the data of Wordlist in order
    //
    int print_inorder(Node* n, int number) const
    {
        if (n == nullptr)
        {
            return number;
        }

        number = print_inorder(n->left, number);
        cout << number << ". {\"" << n->word << ", " << n->count << "}" << endl;
        print_inorder(n->right, ++number);
        return number;
    }

    public:

    //
    // Returns the number of times w occurs as a word in the word list.
    //
    int get_count(const string &w) const
    {
        Node* c = root;
        while (c != nullptr)
        { // search for word alphabetically
            if (w < c->word)
            {
                c = c->left;
            }
            else if (w > c->word)
            {
                c = c->right;
            }
            else
            {
                return c->count;
            }
        }

        // word not found
        return 0;
    }

    //
    // Returns the number of nodes in the word list.
    //
    int num_different_words() const
    {
        return num_different_words_rec(root, 0);
    }

    //
    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.
    //
    int total_words() const
    {
        return total_words_rec(root, 0);
    }

    //
    // Returns true if the words in the word list are in ascending sorted order,
    // false otherwise.
    //
    // For an AVL implementation, this should return true if the AVL tree is a
    // BST, and false otherwise.
    //
    bool is_sorted() const;

    //
    // Returns a string of the most frequent word in the format "word freq".
    // E.g. if the most frequent word is "the" with count 5437, then "the 5437"
    // is returned. 
    //
    // If there is a tie, the first word in the list is returned. For an AVL
    // implementation, this means return the word that occurs first
    // alphabetically.
    //
    // Assumes the list is not empty.
    //
    string most_frequent() const
    {
        Node* freq = most_frequent_rec(root, root);
        return freq->word + " " + to_string(freq->count);
    }

    //
    // Returns the number of nodes with count 1.
    //
    int num_singletons() const
    {
        return num_singletons_rec(root, 0);
    }

    //
    // Adds w to the word list. If w is already in the word list, then increment
    // its count. Otherwise add a new Node (with count 1) at the alphabetically
    // correct location for the word.
    //
    void add_word(const string &w)
    {

        // Case 0: empty tree
        if (is_empty())
        {
            Node* n = new Node();
            n->word = w;
            n->count = 1;
            n->left = n->right = nullptr;
            root = n;
            return;
        }

        // Case 1: word already exists in tree
        Node* c = root;
        while (c != nullptr)
        { // search for word alphabetically
            if (w < c->word)
            {
                c = c->left;
            }
            else if (w > c->word)
            {
                c = c->right;
            }
            else
            { // word found
                ++(c->count);
                return;
            }
        }

        // Case 2: word does not exist in tree
        Node* n = new Node();
        n->word = w;
        n->count = 1;
        n->left = n->right = nullptr;
        c = n; // insert node at the end
        
        // Balance the tree
        balance();
    }

    //
    // Prints the words in the word list in alphabetical order by word, along
    // with their counts. The first word is 1, the second 2, and so on, e.g.:
    //
    //   ❯ ./a5_main < small.txt
    //   1. {"This", 1}
    //   2. {"a", 2}
    //   3. {"is", 2}
    //   4. {"or", 1}
    //   5. {"test", 1}
    //   6. {"test?", 1}
    //   7. {"this", 1}
    //
    void print_words()
    {
        print_inorder(root, 1);
    }

    //
    // Default class constructor
    //
    Wordlist() { }

    //
    // Paramaterized Constructor
    // Takes file name (with extension) and loads file into Wordlist
    //
    Wordlist(string fileName)
    {
        ifstream textFile;
        string w;
        textFile.open(fileName);
        if (!textFile.is_open())
        { // file open failure
            return;
        }

        while (textFile >> w)
        { // loop every word in the file
            add_word(w);
        }

        textFile.close();
    }

    //
    // Destructor
    //
    ~Wordlist()
    {

    }

}; // class Wordlist

//
// Make sure to thoroughly test your code as you go!
//