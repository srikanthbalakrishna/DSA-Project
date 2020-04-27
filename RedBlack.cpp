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
        -create search() and implement a way to prevent program crash when duplicate is entered
============================================================
*/
#define RED 1
#define BLACK 0
#include<iostream>
#include<string>
#include<regex>  //Note : THIS REQUIRES ' -std=c++11 ' to be enabled in compiler options


class Tree
{
    public:
    class Node
    {
        public:
        std::string value;
        int color;
        Node *left, *right , *parent;

        Node(std::string data)  //parametrised constructor
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
        //
        //std::cout<<"Red - "<<RED<<" and Black - "<<BLACK<<std::endl<<std::endl;
        //
        nill = new Node("-1");
        nill->color = BLACK;
        nill->left = nill->right = nill->parent = NULL;
    }
    //Tree() Constructor ends

    bool validate(std::string reg)
    {
        std:: regex expression("[[:d:]]{2}[a-zA-Z]{3}[[:d:]]{4}");
        bool match = regex_match(reg,expression);
        return match;
    }
    //validate() ends

    void insert(std::string data)
    {
        if(validate(data) && !search(root,data) ) //if the data value is a valid Reg.No. and not already present in the Tree
        {

        //Note: When comparing two register numbers, we can directly use '>' and '<' on the strings and get the result
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
        //now resolve conflict of adjacent red nodes if occurred
            //
            //std::cout<<data<<" inserted."<<" Resolve conflict if occurred"<<std::endl;
            //
            resolve_insertion(new_node);

        }//if for validation ends
        else if(!validate(data))
        {
            //VALIDATION FOR INPUT failed
            std::cout<<"--\""<<data<<"\" is an INVALID Reg.No."<<std::endl<<std::endl;
        }
    }
    //insert() ends

    void resolve_insertion(Node *x)
    {
       int counter = 1;
       Node* uncle = NULL;
       while(x != root && x->parent->color == RED)
       {
            //
            //std::cout<<"    Iteration "<<counter++<<": Conflict occurred for "<<x->value<<std::endl;
            //
            if( x->parent == x->parent->parent->left ) //if parent of 'x' is a left child
            {       //
                    //std::cout<<"       parent("<<x->parent->value<<") is a LEFT child"<<std::endl;
                    //
                    uncle = x->parent->parent->right;
                    //
                    //std::cout<<"       uncle("<<uncle->value<<") is of color "<<uncle->color<<std::endl;
                    //
                    if(uncle->color == RED ) //CASE 1
                    {
                        //
                        //std::cout<<"        uncle("<<uncle->value<<") is red"<<uncle->color<<std::endl;
                        //
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
                    //
                    //std::cout<<"        uncle("<<uncle->value<<") is black"<<std::endl;
                    //
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    right_rotate(x->parent->parent);


            }
            else    //if parent of 'x' is a right child
            {   //interchanging left <--> right from above block
                    //
                    //std::cout<<"       parent("<<x->parent->value<<") is a RIGHT child"<<std::endl;
                    //
                    uncle = x->parent->parent->left;
                    //
                    //std::cout<<"       uncle("<<uncle->value<<") is of color "<<uncle->color<<std::endl;
                    //
                    if( uncle->color == RED) //CASE 1
                    {
                        //
                        //std::cout<<"        uncle("<<uncle->value<<") is red"<<std::endl;
                        //
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
                    //
                    //std::cout<<"        uncle("<<uncle->value<<") is black"<<std::endl;
                    //
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
        else
        {
            inorder(root->left);
            if(root->value!="-1")
                std::cout << root->value <<" ";
            inorder(root->right);
        }
    }
    //inorder() ends

    bool search(Node* x, std::string key)
    {
        if (x == NULL)
            return false;

        if (x->value == key)
            return true;


        bool res1 = search(x->left, key); //first checking the left subtree

        if(res1) return true; // key was found so return true and exit search process


        bool res2 = search(x->right, key); //key not found on left subtree so check the right subtree

        return res2; //return to the calling search() whether it waas found or not
    }
    //search() ends

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
    x.insert("19BCE0158");
    x.insert("19BCE0157");
    x.insert("19BCI0873");
    x.insert("19BCI0006");
    x.insert("18BCE0983");
    x.insert("17BIT0846");
    x.insert("16BIO9999");
    x.insert("G.Vishwanathan");
    x.insert("17BCE9684");
    x.insert("15BCE0985");
    x.insert("17BCE9684");
    x.insert("14BIT0384");
    x.insert("20BCE0001");
    x.insert("14BIT0384");
    x.inorder(x.root);std::cout<<std::endl;

    return 0;
}
//main ends
