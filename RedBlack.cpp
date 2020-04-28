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
        -create delete() if needed
============================================================
*/
#define RED 1
#define BLACK 0
#include<iostream>
#include<string>
#include<regex>  //Note : THIS REQUIRES ' -std=c++11 ' to be enabled in compiler options
#include<conio.h>
#include<ctime>

class Tree
{
    public:
    class Node
    {
        public:
        std::string value;
        int color;
        Node *left, *right , *parent;
        tm* time_of_entry;

        Node(std::string data,tm* current_time)  //parametrised constructor
        {
            time_of_entry = current_time;
            value = data;
            color = RED;    //by default a node will have color as RED
            left = right = parent = NULL; //redundant
        }

        std::string get_TimeOfEntry()
        {
            std::string hours,minutes,seconds;
            hours   = ( time_of_entry->tm_hour < 10 ) ? ("0" + std::to_string(time_of_entry->tm_hour) ):( std::to_string(time_of_entry->tm_hour) );
            minutes = ( time_of_entry->tm_min  < 10 ) ? ("0" + std::to_string(time_of_entry->tm_min)  ):( std::to_string(time_of_entry->tm_min)  );
            seconds = ( time_of_entry->tm_sec  < 10 ) ? ("0" + std::to_string(time_of_entry->tm_sec)  ):( std::to_string(time_of_entry->tm_sec)  );
            return( hours + ":" + minutes +":"+ seconds );
        }
    };
    //Node class ends

    Node* root;
    Node* nill;
    Node* searchNode;
    private:
    tm* date_of_recording;  //stores the date at which the attendance was recorded
    std::string course_name;

    public:
    Tree()
    {
        root = NULL;
        //
        time_t time_of_program_start;
        date_of_recording = localtime(&time_of_program_start);
        //
        tm* time = localtime(&time_of_program_start);
        nill = new Node("-1",time);
        nill->color = BLACK;
        nill->left = nill->right = nill->parent = NULL;
        course_name="Course Not Set";
        //
    }
    //Tree() Constructor ends
    private:
    bool validate(std::string reg)
    {
        std:: regex expression("[[:d:]]{2}[a-zA-Z]{3}[[:d:]]{4}");
        bool match = regex_match(reg,expression);
        return match;
    }
    //validate() ends

    public:
    bool insert(std::string data)  //returns true if data has been inserted, false if invalid/duplicate
    {
        if(validate(data) && search(root,data)==NULL ) //if the data value is a valid Reg.No. and not already present in the Tree
        {

            //Note: When comparing two register numbers, we can directly use '>' and '<' on the strings and get the result
            time_t now = time(0);
            tm* current_time = localtime(&now);
            Node* new_node = new Node(data,current_time);
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
            return true;
        }//if for validation ends
        else if(!validate(data))
        {
            //VALIDATION FOR INPUT failed
            std::cout<<"\n--\""<<data<<"\" is an INVALID Reg.No."<<std::endl;
            return false;
        }
    }
    //insert() ends

    private:
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

    public:
    void inorder(Node* root)
    {
        if (root == NULL)
            return;
        else
        {
            inorder(root->left);
            if(root->value!="-1")
                std::cout <<"\nReg No: "<< root->value <<"\nTimestamp: "<<root->get_TimeOfEntry()<<std::endl;
            inorder(root->right);
        }
    }
    //inorder() ends

    Node *search(Node* x, std::string key)
    {
        if (x == NULL){
            return NULL;
        }  //not found

        if (x->value == key){
            return x;
        } //found , returns a pointer to the node
            


        Node* res1 = search(x->left, key); //first checking the left subtree

        if(res1){
            return x;
        } // key was found so return pointer to the node and exit search process


        Node*res2 = search(x->right, key); //key not found on left subtree so check the right subtree

        return res2; //return to the calling search() whether it waas found or not
    }
    //search() ends

    void set_CourseName(std::string course_name)
    {
        this->course_name = course_name;
    }
    //set_CourseName() ends

    std::string get_CourseName()
    {
        return this->course_name;
    }
    //get_CourseName() ends

};
//class Tree ends
int main()
{
    /*
        public functions of Tree Class available for use:
        -inorder( Node* n )            --> performs inorder traversal starting from the node passed to it(so we pass the root node to it to
                                           traverse the whole tree)
        -insert( string x )            --> inserts a node in the redBlack tree. The node automatically stores the time at which it was inserted
        -set_CourseName( string x )    --> sets the name of the course to be the passed string (e.g: DLD, DSA or even "SJT building" if needed)
        -get_CoourseName()             --> returns a string containing coursename
        -search(Node* root,string reg) --> the first parameter must be the root. The second parameter is the register no. of the
                                             student being searched.
                                             If student is found,   function returns a pointer to the Node
                                                                    else it returns NULL
        functions of Node Class available for use:
        -get_TimeOfEntry()  --> returns a string containing the time of entry for the student
                                can be used to get the time at which a particular student/Node entered their attendance

    */
    Tree x[10]; //create 10 classes/courses and automatically sets todays date as the date at which attendance is recorded
    x[0].set_CourseName("Data Structures & Algorithms");
    x[0].insert("19BCE0158");
    x[0].insert("19BCE0157");
    x[0].insert("19BCI0873");
    x[0].insert("19BCI0006");
    x[0].insert("18BCE0983");
    x[0].insert("17BIT0846");
    x[0].insert("16BIO9999");
    x[0].insert("G.Vishwanathan");
    x[0].insert("17BCE9684");
    x[0].insert("15BCE0985");
    x[0].insert("17BCE9684");
    x[0].insert("14BIT0384");
    x[0].insert("20BCE0001");
    x[0].insert("14BIT0384");
    int ch;
    while(ch != 6){
        std::cout<<"\nEnter your Choice:\n1.Insert Record\n2.Search for a Record\n3.Display Inorder\n4.Exit\n\n";
        std::cin>>ch;
        if(ch == 1){
            std::string data;
            std::cout<<"\nWhat is the Registration Number you want to insert: ";
            std::cin>>data;
            x[0].insert(data);
        }
        else if(ch == 2){
            std::string searchdata;
            std::cout<<"\nEnter the Reg No. to search for: ";
            std::cin>>searchdata;
            x[0].searchNode = x[0].search(x[0].root, searchdata);
            if(x[0].searchNode == NULL){
                std::cout<<"\nThere is no such record!\n";
            }
            else{
                std::cout <<"\nRecord Found!\nReg No: "<< x[0].searchNode->value <<"\nTimestamp: "<<x[0].searchNode->get_TimeOfEntry()<<std::endl;
            }
        }
        else if(ch == 3){
            x[0].inorder(x[0].root);
        }
        else if(ch == 4){
            return 0;
        }
        else{
            return 0;
        }
    }
    getch();
    return 0;
}
//main ends
