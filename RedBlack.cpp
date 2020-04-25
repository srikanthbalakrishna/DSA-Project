/*
            DATA STRUCTURES & ALGORITHMS PROJECT L43+L44
            Srikanth Balakrishna - 19BCE0158
            Prakhar Soni         - 19BCB0006
            */
/* this comment is to be removed once the project is final
============================================================
USEFUL LINKS:
        1] https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
        2] https://youtu.be/qA02XWRTBdw
        3] https://youtu.be/YWqla0UX-38
============================================================
        TO DO:
        -modify 'key' of node structure to be string type and add a compare() to handle strings
         and consequently modify all the comparisons used during insertion
        -create resolve_insertion()
        -create delete()
        -create resolve_deletion()
        -create search()
============================================================
*/
#define RED 0
#define BLACK 1
#include<iostream>
using namespace std;

class Tree
{
    public:
    struct Node
    {
        Node(int data)  //parametrised constructor
        {
        key = data;
        color = RED;    //by default a node will have color as RED
        left = right = parent = NULL;
        }
        int key,color;
        struct Node *left, *right , *parent;
    }*root;

    Tree()
    {
        root = NULL;
    }

    void insert(int key)
    {
        Node* new_node = new Node(key);
        Node* x = root;
        Node* y = NULL;
            while (x != NULL)
            {
                y = x;
                if (key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
        if (y == NULL)
        {
            new_node->color = BLACK;
            root = new_node;
        }
        else if (key < y->key)
        {
            new_node->parent = y;
            y->left = new_node;
        }
        else if (key > y->key)
        {
            new_node->parent = y;
            y->right = new_node;
        }
        else //duplicate key
        {
            //do nothing
        }
        //now resolve conflict of adjacent red nodes if occured --UNCOMMENT THE LINE BELOW ONCE THAT FUNCTION IS COMPLETED

            //resolve_insertion(new_node);
    }

    void resolve_insertion(Node *x) //INCOMPLETE
    {
        if(root == x)
        {
            //root->color = BLACK;          //redundant statement
            return;
        }
                                            // 'x' is the node that has just been inserted in the Tree
        Node* father = x->parent;           //parent of 'x'
        Node* uncle;                        //sibling of the parent of 'x'
        if(father == father->parent->left)
            uncle = father->parent->right;
        else
            uncle = father->parent->left;

        if( father->color!=BLACK )
        {
            if(uncle->color==BLACK)
            {
                // perform suitable rotation and recoloring
                //

                //INCOMPLETE

                //
            }
            else  //Uncle is RED
            {
                //recolor and then check the grandparent for conflict and so on until resolved
                father->color = BLACK;              //change uncle's color to black
                uncle->color = BLACK;               //change parent's color to black
                (father->parent)->color = RED;      //change grandparent's color to RED
                resolve_insertion(father->parent);  //resolve conflict if it occurs for the grandparent
            }
        }
    }

    void inorder(Node* root)
    {
        if (root == NULL)
            return;
        else {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

};

int main()
{
    /* Testing example
            50
          /   \
        30      70
        / \   / \
       20 40 60 80 */

    Tree x;
    x.insert(50);
    x.insert(30);
    x.insert(20);
    x.insert(40);
    x.insert(70);
    x.insert(60);
    x.insert(80);
    x.inorder(x.root);

    return 0;
}
