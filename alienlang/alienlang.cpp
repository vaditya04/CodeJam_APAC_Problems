
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
 
#define ALPHABETS 26
 
using namespace std;
 
class TrieTreeNode
{
    public:
        TrieTreeNode * parent;
        TrieTreeNode * children[ALPHABETS];
        vector<int> occurrences;
};
 
class TrieTree
{
    public:     
        TrieTreeNode * root;
         
        TrieTree() {
            root = (TrieTreeNode *) calloc(1, sizeof(TrieTreeNode));
        }
         
        // Inserts a word 'text' into the Trie Tree
        // 'trie_tree' and marks it's occurence as 'index'.
        void insert(char text[], int index)
        {
            // Converting the input word 'text'
            // into a vector for easy processing
            vector<char> word(text, text + strlen(text));
            TrieTreeNode * temp = root;
             
            int i = 0;
             
            while (i < word.size()) {      // Until there is something to process
                if (temp->children[word[i] - 'a'] == NULL) {
                    // There is no node in 'trie_tree' corresponding to this alphabet
          
                    // Allocate using calloc(), so that components are initialised
                    temp->children[word[i] - 'a'] =
                            (TrieTreeNode *) calloc(1, sizeof(TrieTreeNode));
                    temp->children[word[i] - 'a']->parent = temp; // Assigning parent
                }
          
                temp = temp->children[word[i] - 'a'];

                ++i;   // Next alphabet
            }
          
            temp->occurrences.push_back(index);      //Mark the occurence of the word
        }
         
        // Prints the 'trie_tree' in a Pre-Order or a DFS manner
        // which automatically results in a Lexicographical Order
        void lexicographPrint(TrieTreeNode * trie_tree, vector<char> printUtilVector)
        {
            int i;
            bool noChild = true;
                         
            vector<int>::iterator itr = trie_tree->occurrences.begin();
          
            for (i = 0; i < ALPHABETS; ++i) {
                if (trie_tree->children[i] == NULL) {
                    continue;
                } else {
                    noChild = false;
                    printUtilVector.push_back('a' + i);    // Select a child
          
                    // and explore everything associated with the cild
                    lexicographPrint(trie_tree->children[i], printUtilVector);
                    printUtilVector.pop_back();
                    // Remove the alphabet as we dealt
                    // everything associated with it
                }
            }
          
            if (trie_tree->occurrences.size() != 0) {
                // Condition trie_tree->occurrences.size() != 0,
                // is a neccessary and sufficient condition to
                // tell if a node is associated with a word or not
          
                vector<char>::iterator itr = printUtilVector.begin();
          
                while (itr != printUtilVector.end()) {
                    printf("%c", *itr);
                    ++itr;
                }
                printf(" -> @ index -> ");
          
                vector<int>::iterator counter = trie_tree->occurrences.begin();
                // This is to print the occurences of the word
          
                while (counter != trie_tree->occurrences.end()) {
                    printf("%d, ", *counter);
                    ++counter;
                }
          
                printf("\n");
            }
          
            printUtilVector.pop_back();
        }
         
        // Searches for the occurence of a word in 'trie_tree',
        // if not found, returns NULL,
        // if found, returns poniter pointing to the
        // last node of the word in the 'trie_tree'
        bool searchWord(TrieTreeNode * trie_tree, char * text)
        {
            // Functions very similar to insert() function
            vector<char> word(text, text + strlen(text));
            TrieTreeNode * temp = trie_tree;
          
            while (word.size() != 0) {
                if (temp->children[word[0] - 'a'] != NULL) {
                    temp = temp->children[word[0] - 'a'];
                    word.erase(word.begin());
                } else {
                	return false;
                }
            }
          	return true;
        }
         
        // Searches the word first, if not found, does nothing
        // if found, deletes the nodes corresponding to the word 
};
 
void recursiveCount(char * word, TrieTree trie, int length, int & count, int currentPos, int currentLength, TrieTreeNode * currentNode)
{    
	if (word[currentPos] == '(')
	{
		int j;
		for (j = currentPos; word[j] != ')'; j++);

		for (int i = currentPos+1; i<j; i++)
		{
			
			// cout<<currentWord<<endl;
	           currentLength++;
			// char *cstr = new char[currentWord.length() + 1];
			
			// strcpy(cstr, currentWord.c_str());
/*                if (temp->children[word[0] - 'a'] != NULL) {
                    temp = temp->children[word[0] - 'a'];*/

			if (currentNode->children[word[i] - 'a'] != NULL)
			{
					// delete [] cstr;
				if (currentLength == length)
				{
									// cout<<"HERE1"<<endl;

					count++;
                    currentLength--;
					continue;
				}	
				recursiveCount(word, trie, length, count, j+1, currentLength, currentNode->children[word[i]- 'a']);
			}
			else
			{
						// delete [] cstr;
	
			}
            currentLength--;
			// currentWord = currentWord.substr(0, currentWord.length()-1);


		}
	}
	else
	{

			// currentWord.append(word, currentPos, 1);
			// cout<<currentWord<<endl;
            currentLength++;
			// char *cstr = new char[currentWord.length() + 1];
			
			// strcpy(cstr, currentWord.c_str());

			if (currentNode->children[word[currentPos]- 'a'] != NULL)
			{

					// delete [] cstr;
				if (currentLength == length)
				{
									// cout<<"HERE2"<<endl;

					count++;
					return;
				}	
				recursiveCount(word, trie, length, count, currentPos+1, currentLength, currentNode->children[word[currentPos]- 'a']);
			}
			else
            {
				// delete [] cstr;
                return;
            }
	}


}


int main()
{

    freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);
    int wordSize, dictSize, testCases;
  
    // printf("Enter the number of words-\n");
    cin>>wordSize>>dictSize>>testCases;
  
    char words[dictSize][wordSize];
    TrieTree trie;
  
    for (int i = 0; i < dictSize; ++i) {
        scanf("%s", words[i]);
		trie.insert(words[i], i + 1);
    }
  	

  	char currentWord[26*wordSize];

  	for (int i = 0; i < testCases; i++)
  	{ 	 		
  		int possibleCount = 0;
	  	scanf("%s", currentWord);
	  	recursiveCount(currentWord, trie, wordSize, possibleCount, 0, 0, trie.root);
  		cout<<"Case #"<<i+1<<": "<<possibleCount<<endl;

  	}
/*vector<char> util;
    // printf("\n");   // Just to make the output more readable
    trie.lexicographPrint(trie.root, util);*/
    
    // Creating the Trie Tree using calloc so that the components
    // are initialised
    // Always initialize
    //struct node * trie_tree = (struct node *) calloc(1, sizeof(struct node));
  /*
    vector<char> util;
    // printf("\n");   // Just to make the output more readable
    trie.lexicographPrint(trie.root, util);
    trie.removeWord(trie.root, words[0]);
    // printf("\n");   // Just to make the output more readable
    trie.lexicographPrint(trie.root, util);*/
  
    return 0;
}