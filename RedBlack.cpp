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
#include <iostream>
#include <string>
#include <regex> //Note : THIS REQUIRES ' -std=c++11 ' to be enabled in compiler options
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

string get_new_time()
{
    time_t present = time(0);
    tm *current_time = localtime(&present);
    string hours,minutes,seconds,time_of_insertion;
    hours = (current_time->tm_hour < 10) ? ("0" + to_string(current_time->tm_hour)) : (to_string(current_time->tm_hour));
    minutes = (current_time->tm_min < 10) ? ("0" + to_string(current_time->tm_min)) : (to_string(current_time->tm_min));
    seconds = (current_time->tm_sec < 10) ? ("0" + to_string(current_time->tm_sec)) : (to_string(current_time->tm_sec));
    time_of_insertion = (hours + ":" + minutes + ":" + seconds) ; //storing time of insertion

    return time_of_insertion;
}

class Tree
{
public:
    class Node
    {
    public:
        string value,time,status;
        int color;
        Node *left, *right, *parent;
        tm *time_of_entry;

        Node(string data, string t) //parametrised constructor
        {
            status = "IN";
            time = t;;
            value = data;
            color = RED;                  //by default a node will have color as RED
            left = right = parent = NULL; //redundant
        }

        string get_TimeOfEntry()
        {
            return time;
        }
    };
    //Node class ends

    Node *root;
    Node *nill;
    Node *searchNode;

private:
    tm *date_of_recording; //stores the date at which the attendance was recorded
    string course_name;

public:
    Tree()
    {
        root = NULL;
        //
        time_t time_of_program_start = time(0);
        date_of_recording = localtime(&time_of_program_start);
        //
        tm *time = localtime(&time_of_program_start);
        nill = new Node("-1","Time Not Set");
        nill->color = BLACK;
        nill->left = nill->right = nill->parent = NULL;
        course_name = "Course Not Set";
        //
    }
    //Tree() Constructor ends
private:
    bool validate(string reg)
    {
        regex expression("[[:d:]]{2}[a-zA-Z]{3}[[:d:]]{4}");
        bool match = regex_match(reg, expression);
        return match;
    }
    //validate() ends

public:
    string get_Date()
    {
        string hours,minutes,seconds,time_of_insertion;
        hours = (date_of_recording->tm_hour < 10) ? ("0" + to_string(date_of_recording->tm_hour)) : (to_string(date_of_recording->tm_hour));
        minutes = (date_of_recording->tm_min < 10) ? ("0" + to_string(date_of_recording->tm_min)) : (to_string(date_of_recording->tm_min));
        seconds = (date_of_recording->tm_sec < 10) ? ("0" + to_string(date_of_recording->tm_sec)) : (to_string(date_of_recording->tm_sec));
        time_of_insertion = (hours + ":" + minutes + ":" + seconds) ; //storing time of insertion
        return ("Recording begun at:"+time_of_insertion);
    }
    bool insert(string data , string t) //returns true if data has been inserted, false if invalid/duplicate
    {
        if ((validate(data) == true) && (search(root, data) == NULL)) //if the data value is a valid Reg.No. and not already present in the Tree
        {

            //Note: When comparing two register numbers, we can directly use '>' and '<' on the strings and get the result
            Node *new_node = new Node(data, t);
            new_node->left = nill;
            new_node->right = nill;
            Node *x = root;
            Node *y = NULL;
            //obtain point of insertion --> 'y'
            while (x != NULL && x != nill)
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
            //cout<<data<<" inserted."<<" Resolve conflict if occurred"<<endl;
            //
            resolve_insertion(new_node);
            return true;
        } //if for validation ends
        else if (!validate(data))
        {
            //VALIDATION FOR INPUT failed
            cout << "--\"" << data << "\" is an INVALID Reg.No." << endl;
            return false;
        }
        else if (search(root, data) != NULL)
        {
            //update timestamp and change status to OUT
            Node* x = search(root,data);
            x->time = get_new_time();
            x->status = "OUT";

        }
    }
    //insert() ends

private:
    void resolve_insertion(Node *x)
    {
        int counter = 1;
        Node *uncle = NULL;
        while (x != root && x->parent->color == RED)
        {
            //
            //cout<<"    Iteration "<<counter++<<": Conflict occurred for "<<x->value<<endl;
            //
            if (x->parent == x->parent->parent->left) //if parent of 'x' is a left child
            {                                         //
                //cout<<"       parent("<<x->parent->value<<") is a LEFT child"<<endl;
                //
                uncle = x->parent->parent->right;
                //
                //cout<<"       uncle("<<uncle->value<<") is of color "<<uncle->color<<endl;
                //
                if (uncle->color == RED) //CASE 1
                {
                    //
                    //cout<<"        uncle("<<uncle->value<<") is red"<<uncle->color<<endl;
                    //
                    x->parent->color = BLACK;
                    uncle->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                    continue;
                }
                else if (x == x->parent->right) //Case 2 - uncle is black/NULL and 'x' is a right child
                {
                    x = x->parent;
                    left_rotate(x);

                } //Case 2 transforms into Case 3
                //Case 3 - 'x' is a left child and uncle is black/NULL
                //
                //cout<<"        uncle("<<uncle->value<<") is black"<<endl;
                //
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                right_rotate(x->parent->parent);
            }
            else //if parent of 'x' is a right child
            {    //interchanging left <--> right from above block
                //
                //cout<<"       parent("<<x->parent->value<<") is a RIGHT child"<<endl;
                //
                uncle = x->parent->parent->left;
                //
                //cout<<"       uncle("<<uncle->value<<") is of color "<<uncle->color<<endl;
                //
                if (uncle->color == RED) //CASE 1
                {
                    //
                    //cout<<"        uncle("<<uncle->value<<") is red"<<endl;
                    //
                    x->parent->color = BLACK;
                    uncle->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                    continue;
                }
                else if (x == x->parent->left) //Case 2 - uncle is black and 'x' is a left child
                {
                    x = x->parent;
                    right_rotate(x);

                } //Case 2 transforms into Case 3
                //Case 3
                //
                //cout<<"        uncle("<<uncle->value<<") is black"<<endl;
                //
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                left_rotate(x->parent->parent);
            }
        }
        root->color = BLACK;
    }
    //resolve_insertion() ends

    void left_rotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->left)
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

    void right_rotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != NULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->right)
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
    bool inorder(Node *root)
    {
        if (root == NULL){
            return false;
        }
        else
        {
            inorder(root->left);
            if (root->value != "-1")
                cout << "\nReg No: " << root->value << "\nTimestamp: " << root->get_TimeOfEntry() << "\nStatus: " << root->status<<endl;
            if(root->value == "-1"){
                return true;
            }
            inorder(root->right);
        }
    }
    //inorder() ends

    Node *search(Node *x, string key)
    {
        if (x == NULL)
        {
            return NULL;
        } //not found

        if (x->value == key)
        {
            return x;
        } //found , returns a pointer to the node

        Node *res1 = search(x->left, key); //first checking the left subtree

        if (res1)
        {
            return res1;
        } // key was found so return pointer to the node and exit search process

        Node *res2 = search(x->right, key); //key not found on left subtree so check the right subtree

        return res2; //return to the calling search() whether it waas found or not
    }
    //search() ends

    void set_CourseName(string course_name)
    {
        this->course_name = course_name;
    }
    //set_CourseName() ends

    string get_CourseName()
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
        -get_new_time()     -->returns string containing current system time in hours:minutes:seconds format

    */
    Tree x; //create a class and automatically set todays date as the date at which attendance is recorded
    x.set_CourseName("SJT Building Attendance");
    ////
    system("cls");
    //cout<<"Course:"<<x.get_CourseName()<<endl<<x.get_Date()<<endl;
    cout<<"Commands(not case sensitive):\ninsert <Reg No. to insert>\nsearch <Reg No. to search for>\ndisplay\ncls(Clear Screen)\nexit\n\n";
    do
    {
        cout << "> ";
        char str[100];
        string input[10];
        cin.getline(str, sizeof(str));
        istringstream iss(str);
        string s;
        int i = 0;
        while (getline(iss, s, ' '))
        {
            input[i++] = s.c_str();
        }
        cout<<"\n";
        if (input[0] == "insert" || input[0] == "Insert")
        {

            if(  x.insert(input[1],get_new_time()) )
            {
                cout << "Record Inserted Successfully!\n";
            }
        }
        else if (input[0] == "search" || input[0] == "Search")
        {
            x.searchNode = x.search(x.root, input[1]);
            if (x.searchNode == NULL)
            {
                cout << "There is no such record!\n";
            }
            else
            {
                cout << "Record Found!\nReg No: " << x.searchNode->value << "\nTimestamp: " << x.searchNode->get_TimeOfEntry() << endl;
            }
        }
        else if (input[0] == "display" || input[0] == "Display")
        {
            if(!x.inorder(x.root))
            {
                cout<<"There are no more records!\n";
            }
        }
        else if (input[0] == "exit" || input[0] == "Exit")
        {
            return 0;
        }
        else if(input[0] == "cls" || input[0] == "Cls" || input[0] == "clr" || input[0] == "Clr"){
            system("cls");
        }
        else
        {
            cout << "Not a valid command.\n";
        }
        cout<<"\n";
    } while (true);
    getch();
    return 0;
}
//main ends
