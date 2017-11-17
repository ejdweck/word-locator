//
// File: wl.h
//
//  Description: word locator program that uses a binary search tree to store
//  all words from a text file.
//
#include "wl.h"

/**
 * @usage destroys the bst by recursively deleting nodes.
 *
 * @param leaf node pointer to delete the tree from
 */
void btree::destroy_tree(node *leaf) {
  if (leaf != NULL) {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

/**
 * @usage inserts nodes into the bst. Recursively calls itself until it gets to the
 *        bottom of the tree (ie the proper spot to insert. If the word already exists
 *        as a node in the list, then the index of the word is added to the node.
 *
 * @param word the word to be inserted
 * @param leaf the leaf that is being compared against for ordering
 * @param index the occurance of the word
 *
 */
void btree::insert (std::string word, node *leaf, int index) {
  if (word == leaf->word) {
    leaf->index_list.push_back(index);
  } else if(word < leaf->word) {
    if (leaf->left != NULL) {
      insert(word, leaf->left, index);
    } else {
      leaf->left = new node;
      leaf->left->word = word;
      leaf->left->index_list.push_back(index);
      leaf->left->left = NULL;
      leaf->left->right = NULL;
    }
  } else if (word >= leaf->word) {
    if (leaf->right != NULL) {
      insert(word, leaf->right, index);
    } else {
      leaf->right = new node;
      leaf->right->word = word;
      leaf->right->index_list.push_back(index);
      leaf->right->left = NULL;
      leaf->right->right = NULL;
    }
  }
}

/**
 * @usage recursively searches the tree for a specific occurance of a given word.
 *
 * @param word the word that is being searched for
 * @param leaf the leaf that the search starts on
 * @param index the occurance of the word being searched for
 *
 * @return node* the node that is found.  Null if not found
 */
node *btree::search(std::string word, node *leaf, int index) {
  if (leaf != NULL) {
    if (word == leaf->word) {
      return leaf;
    }
    if (word < leaf->word) {
      return search(word, leaf->left, index);
    } else {
      return search (word, leaf->right, index);
    }
  } else {
    return NULL;
  }
}

/**
 * @usage inserts the root if the the tree is not yet constructed. Otherwise calls the
 *        other insert method with root that recursively traverses to the correct place
 *        for insertion.
 *
 * @param word the word to be inserted
 * @param index the occurance of the word
 *
 */
void btree::insert (std::string word, int index) {
  if (root != NULL) {
    insert(word, root, index);
  } else {
    root = new node;
    root->word = word;
    root->index_list.push_back(index);
    root->left = NULL;
    root->right = NULL;
  }
}

/**
 * @usage calls the private message search
 *
 * @param word the word to be searched
 * @param index the occurance of the word
 *
 * @return node* the node that is found.  Null otherwise
 */
node *btree::search(std::string word, int index) {
  return search(word, root, index);
}

/**
 * @usage calls the private destroy method to destroy the tree
 */
void btree::destroy_tree() {
  destroy_tree(root);
}

/**
 * @usage parses the white space form a string
 *
 * @param line the line that is being parsed into words
 *
 * @return vector<string> the words organized without whitespace.
 */
std::vector<std::string> parse_whitespace(std::string line) {
  std::stringstream ss(line);
  std::string temp;
  std::vector<std::string> parsed_input;
  while (ss >> temp) {
    parsed_input.push_back(temp);
  }
  return parsed_input;
}

/**
 * @usage changes the string to be all lowercase characters
 *
 * @param word the word that is being forced to lowercase
 *
 * @return string the formatted string (ie all lowercase characters)
 */
std::string lowercase(std::string word) {
  for (unsigned int i = 0; i < word.length(); i++) {
    word[i] = tolower(word[i]);
  }
  return word;
}

/**
 * @usage gets rid of the punctuation characters from words at the end of the
 *        sentence
 * @param word the word that is being check and trimmed for punctuation
 *
 * @return string a string with no punctuation at the end of the sentence
 */
std::string trim_punctuation(std::string word) {
  if (word.length() > 1) {
    char final_character = word[word.length()-1];
    if (!(isdigit(final_character) || isalpha(final_character))) {
      word = word.substr(0, word.length()-1);
    }
  }
  return word;
}

/**
 * @usage delets the tree object and procures a new one
 *
 * @param btree* a pointer to the bst that will be "cleaned" (ie erased and
 *               reset to empty
 * @return btree* returns a bst pointer that points to a new empty tree
 */
btree* clean_tree(btree *mytree) {
  btree *new_btree;
  new_btree = mytree;
  mytree->destroy_tree();
  delete mytree;
  new_btree = new btree;
  mytree = new_btree;
  return mytree;
}

int main()
{
    btree *mytree;
    mytree = new btree;

    std::string user_input;
    std::string delimiter = " ";
    bool bad_arg = false;
    int word_index = 1;

    std::cout << ">";
    // get input from the user
    while(getline(std::cin, user_input)) {
      // delimit the input string by spaces
      std::vector<std::string> parsed_input;
      parsed_input = parse_whitespace(user_input);
      // force the user input into lower case
      for (unsigned int i = 0; i < parsed_input.size(); i++) {
        parsed_input[i] = lowercase(parsed_input[i]);
      }

      bad_arg = false;

      if (parsed_input.size() == 1 && parsed_input[0] == "new") {
        // reset the word list to original (empty) state
        mytree = clean_tree(mytree);
        word_index = 1;
      } else if( parsed_input.size() == 1 && parsed_input[0] == "end") {
        mytree->destroy_tree();
        delete mytree;
        return 0;
      } else if (parsed_input.size() == 2 && parsed_input[0] == "load") {
        // load the file in a data structure
        std::string file_name = parsed_input[1];
        std::string line;
        std::ifstream myfile (file_name.c_str());
        // open the text file
        if(myfile.is_open()) {
          // clear out tree if already existing to make room for new one
          mytree = clean_tree(mytree);
          // reset the word index to 1
          word_index = 1;
          while (getline(myfile, line)) {
            std::vector<std::string> words;
            words = parse_whitespace(line);
            for (unsigned int i = 0; i < words.size(); i++) {
              words[i] = lowercase(words[i]);
              words[i] = trim_punctuation(words[i]);
              mytree->insert(words[i], word_index);
              word_index++;
            }
          }
          mytree->is_empty = false;
          myfile.close();
        } else {
            std::cout << "ERROR: Invalid command" << std::endl;
        }
      } else if (parsed_input.size() == 3 && parsed_input[0] == "locate") {
        // check if second arg (word) is valid input
        std::string second_arg = parsed_input[1];
        for (unsigned int i = 0; i < second_arg.size(); i++) {
          if(!(isdigit(second_arg[i]) || isalpha(second_arg[i]) ||
                  second_arg[i] == '\'')) {
              std::cout << "ERROR: Invalid command" << std::endl;
              bad_arg = true;
              break;
          }
        }

        // check if third arg (index of word) is valid input
        std::string third_arg = parsed_input[2];
        if (bad_arg != true) {
          for (unsigned int i = 0; i < third_arg.size(); i++) {
            if(!(isdigit(third_arg[i]))) {
                std::cout << "ERROR: Invalid command" << std::endl;
                bad_arg = true;
                break;
            }
          }
        }

        // search for the word based on input params
        unsigned int index_num = atoi(third_arg.c_str());
        if (bad_arg == false) {
          if (mytree->is_empty == false) {
            // search for the word that the user entered with the locate command
            // at the occurance the user specified in the third argument
            struct node *mynode = mytree->search(second_arg, index_num); // wil be third_arg
            if (mynode != NULL) {
              // check that the index specified by the user exists
              if (mynode->index_list.size() >= index_num) {
                std::cout << mynode->index_list[index_num-1] << std::endl;
              } else {
                std::cout << "No matching entry" << std::endl;
              }
            } else {
              std::cout << "No matching entry" << std::endl;
            }
          } else {
              std::cout << "No matching entry" << std::endl;
          }
        }

      } else {
        std::cout << "ERROR: Invalid command" << std::endl;
      }
      std::cout << ">";
    }
    return 0;
}
