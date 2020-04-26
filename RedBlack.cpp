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
        4] http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
============================================================
        TO DO:
        -modify 'value' of node structure to be string type and add a compare() to handle strings
         and consequently modify all the comparisons used during insertion OR use operator overloading
        -create search() and implement a way to prevent program crash when duplicate is entered
============================================================
*/
#define RED 1
#define BLACK 0
#include<iostream>
using namespace std;


class Tree
{
    public:
    class Node
    {
        public:
        int value,color;
        Node *left, *right , *parent;

        Node(int data)  //parametrised constructor
        {
        value = data;
        color = RED;    //by default a node will have color as RED
        left = right = parent = NULL; //redundant
        }
    };
    //Node class ends

    Node* root;
    Node* nill;
    Tree()
    {
        root = NULL;
        cout<<"Red - "<<RED<<" and Black - "<<BLACK<<endl<<endl;
        nill = new Node(-1);
        nill->color = BLACK;
        nill->left = nill->right = nill->parent = NULL;
    }
    //Tree() Constructor ends

    void insert(int data)
    {
        Node* new_node = new Node(data);
        new_node->left = nill;
        new_node->right = nill;
        Node* x = root;
        Node* y = NULL;
            //obtain point of insertion --> 'y'
            while (x != NULL && x!= nill)
            {
                y = x;
                if (data < x->value)
                    x = x->left;
                else
                    x = x->right;
            }
        //point of insertion is obtained --> 'y'
        if (y == NULL) //tree is empty, assign newnode as root
        {
            new_node->color = BLACK;
            root = new_node;
        }
        else if (data < y->value) //assign as left child
        {
            new_node->parent = y;
            y->left = new_node;
        }
        else if (data > y->value) //assign as right child
        {
            new_node->parent = y;
            y->right = new_node;
        }
        else //duplicate value
        {
            //do nothing
        }
        //now resolve conflict of adjacent red nodes if occurred
            cout<<data<<" inserted."<<" Resolve conflict if occurred"<<endl;
            resolve_insertion(new_node);
    }
    //insert() ends

    void resolve_insertion(Node *x)
    {
       int counter = 1;
       Node* uncle = NULL;
       while(x != root && x->parent->color == RED)
       {
            cout<<"    Iteration "<<counter++<<": Conflict occurred for "<<x->value<<endl;
            if( x->parent == x->parent->parent->left ) //if parent of 'x' is a left child
            {
                    cout<<"       parent("<<x->parent->value<<") is a LEFT child"<<endl;
                    uncle = x->parent->parent->right;
                    //
                    cout<<"       uncle("<<uncle->value<<") is of color "<<uncle->color<<endl;
                    //
                    if(uncle->color == RED ) //CASE 1
                    {
                        cout<<"        uncle("<<uncle->value<<") is red"<<uncle->color<<endl;
                        x->parent->color = BLACK;
                        uncle->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                        continue;
                    }
                    else if(x == x->parent->right) //Case 2 - uncle is black/NULL and 'x' is a right child
                    {
                        x = x->parent;
                        left_rotate(x);

                    }//Case 2 transforms into Case 3
                    //Case 3 - 'x' is a left child and uncle is black/NULL
                    cout<<"        uncle("<<uncle->value<<") is black"<<endl;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    right_rotate(x->parent->parent);


            }
            else    //if parent of 'x' is a right child
            {   //interchange left <--> right from above block
                ///////if there are problems, try changing interchanging left_rotate and right_rotate here//////////////////
                    cout<<"       parent("<<x->parent->value<<") is a RIGHT child"<<endl;
                    uncle = x->parent->parent->left;
                    //
                    cout<<"       uncle("<<uncle->value<<") is of color "<<uncle->color<<endl;
                    //
                    if( uncle->color == RED) //CASE 1
                    {
                        cout<<"        uncle("<<uncle->value<<") is red"<<endl;
                        x->parent->color = BLACK;
                        uncle->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                        continue;
                    }
                    else if(x == x->parent->left) //Case 2 - uncle is black and 'x' is a left child
                    {
                        x = x->parent;
                        right_rotate(x);


                    }//Case 2 transforms into Case 3
                    //Case 3
                    cout<<"        uncle("<<uncle->value<<") is black"<<endl;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    left_rotate(x->parent->parent);



            }
       }
       root->color = BLACK;
    }
    //resolve_insertion() ends

    void left_rotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if(y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if(x->parent == NULL)
        {
            root = y;
        }
        else if(x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    y->left = x;
    x->parent = y;
    }
    //left rotate ends

    void right_rotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if(y->right != NULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;

        if(x->parent == NULL)
        {
            root = y;
        }
        else if(x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
    y->right = x;
    x->parent = y;
    }
    //right rotate ends

    void inorder(Node* root)
    {
        if (root == NULL)
            return;
        else {
            inorder(root->left);
            if(root->value!=-1)
                cout << root->value <<" ";
            inorder(root->right);
        }
    }
    //inorder() ends
};
//class Tree ends
int main()
{
    /* Testing example
            50
          /   \
        30      70
        / \   / \
       20 40 60 80 */

    Tree x;
    x.insert(10);
    x.insert(18);
    x.insert(7);
    x.insert(15);
    x.insert(16);
    x.insert(30);
    x.insert(25);
    x.insert(40);
    x.insert(60);
    x.insert(2);
    x.insert(1);
    x.insert(70);
    x.inorder(x.root);cout<<endl;

    return 0;
}
//main ends
