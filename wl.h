//
// File: wl.h
//
//  Description: Add stuff here ...
//  Student Name: Evan Dweck
//  UW Campus ID: 9069602150
//  enamil: dweck@wisc.edu


#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <locale>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct node {
  std::string word;
  std::vector<int> index_list;
  node *left;
  node *right;
};

class btree {
    public:
        btree() {
          root = NULL;
          is_empty = true;
        };

        void insert(std::string word, int index);
        node *search(std::string word, int index);
        void destroy_tree();
        bool is_empty;

    private:
        void destroy_tree(node *leaf);
        void insert(std::string word, node *leaf, int index);
        node *search(std::string word, node *leaf, int index);
        node *root;
};


