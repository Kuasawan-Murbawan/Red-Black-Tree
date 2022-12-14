#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    bool colour;
};

typedef struct Node* Nodeptr;


Nodeptr createNode(Nodeptr root){ // black leftover node
    
    Nodeptr n = new Node;
    n -> data = 0;
    n -> left = NULL;
    n -> right = NULL;
    n -> colour = true;
    n -> parent = root;
    
    return n;
};

Nodeptr head; // points to the root of the tree

Nodeptr checkAvail(Nodeptr root, int key){  // check whether the node is empty or not
    
    if(root -> data == 0){
        return root;
    }
    
    else{
        
        if (key < root -> data){
            return checkAvail(root -> left, key);
        }
        else if (key > root -> data){
            return checkAvail(root -> right, key);
        }
        else{
            return 0;
        }
    }
    
}

void case1(Nodeptr current){
    
        cout << "\n\n Initiate Procedure case 1: Uncle Black";
        cout << "\n restructuring...\n\n";
        
        
        
        Nodeptr grandfather = current -> parent -> parent; // assign grandfather
   
   
        // this is for case 1 (bengkok ">")
        if (grandfather -> right -> left == current){ 
            
            current -> parent -> right = current; // swap from left to right
            
            Nodeptr temp = current -> parent; // store parent's address in temporary
            
            
            current -> right = temp; // swap current's left child to parent
            
            
            current -> left = temp -> parent;
            
            
            temp -> parent = current; // make parent as child of current
            
            
            current -> left -> parent = current;
            
            
            current -> parent = NULL;
            
            temp -> left = createNode(temp);
            temp -> right = createNode(temp);
            current -> left -> right = createNode(head);
            
            head = current;
            
            
            cout << "\n recoloring...\n\n";
            current -> colour = true;
            current -> left -> colour =false;
            current -> right -> colour = false;
            
        }
        
        //this is for case 2 "<"
        else if (grandfather -> left -> right == current){
            
    
            Nodeptr father = current -> parent; // assign father
            
            
            grandfather -> parent -> left = current;
            current -> left = father;
            current -> right = grandfather; // cucun terus
            
            current -> parent = grandfather -> parent;
            father -> right = createNode(father -> right);
            grandfather -> parent = current;
            father -> parent = current;
            grandfather -> left = createNode(grandfather -> left); // update values
            
            cout << "\n recoloring...\n\n";       
            current -> colour = true;
            father -> colour = false;
            grandfather -> colour = false;
            
        }
        
        
        else if (grandfather -> right -> right == current){
            
            // case 3 "\"
            cout << "case 2 in uncle black: \n\n";
            
            Nodeptr grandfather = current -> parent -> parent;
            
            current -> parent -> left = grandfather;
            grandfather -> parent -> right = current -> parent;
            grandfather -> parent = current -> parent;
            grandfather -> right = createNode(grandfather -> right);
            
            grandfather -> colour = false;
            grandfather -> parent -> colour = true;
           // grandfather -> parent -> right -> colour = false;
 
        }

}

void case2(Nodeptr current){
    
        Nodeptr grandfather = current -> parent -> parent;
    
        cout << "\n\n Initiate Procedure case 2: Uncle Red";
        cout << "\n recolouring...\n\n";
        
        if(grandfather -> right ==  current -> parent){  // for "\"
        current -> parent -> colour = true;
        grandfather -> left -> colour = true;
        grandfather -> colour = false;
        
        }
        
           
        else if (current -> parent->  parent -> left == current -> parent){  // for "/"
            
            current -> parent -> colour = true;
            current -> parent -> parent -> colour = false;
            current -> parent -> parent -> right -> colour = true;
            
        }
        
        
        head -> colour = true;
}

void checkViolation(Nodeptr current){
    
    if(current -> parent -> parent -> left -> colour == false && current -> parent -> parent -> right -> colour == false){
        case2(current);

    }

    else if(current -> parent -> parent -> left -> colour == true){
        case1(current);
    }
    
    else if (current -> parent -> parent -> right -> colour == true){
        case1(current);
    }
    

}
    

void insert(int key){   // insert node with a key
    
    Nodeptr temp;
    temp = checkAvail(head, key);
    temp -> data = key;
    temp -> left = createNode(temp);
    temp -> right = createNode(temp);
    temp -> colour = false;
    
    
    if (temp -> colour == false && temp -> parent -> colour == false){
        cout << "WARNING! DOUBLE RED VIOLATION\n";
        checkViolation(temp);
    }
    
    cout << key << " has been inserted. \n\n";
}




void printColour(){
    
    // print colour
    
    // first level
    cout << "\t    " << head -> colour << "\n" ;
    
     // second level
    cout << "\t" << head -> left -> colour << "  ||  " << head -> right -> colour << "\n";
    
    
    //third level
    cout << head -> left ->left -> colour << "  ||  " << head -> left -> right -> colour << "\t";
    cout << head -> right -> left -> colour <<  "  ||  " << head  -> right -> right -> colour <<" \n";
    
    
    // fourth level
    cout << "\t     " << head -> right -> left -> left -> colour << "  ||  " <<  head -> right -> left -> right -> colour;
    cout << "     " << head -> right -> right -> left -> colour << "  ||  " <<  head -> right -> right -> right -> colour << "\n\n ";
     
    // fifth level
    cout << "\t"  << head -> right -> left -> left -> left -> colour << "  ||  " << head -> right -> left -> left -> right -> colour;
    cout << "   " << head -> right -> left -> right -> left -> colour << "  ||  " << head -> right -> left -> right -> right -> colour ;
        // third
    cout << "\t\t" << head -> right -> right -> right -> left -> colour << "  ||  " << head -> right -> right -> right -> right -> colour << "\n";

}

void printData(){
    
    // print data
    
    // first level
    cout << "\t    " << head -> data << "\n\n" ;
    
     // second level
    cout << "\t" << head -> left -> data << "  ||  " << head -> right -> data << "\n\n";
    
    
    //third level
    cout << head -> left ->left -> data << "  ||  " << head -> left -> right -> data << "\t";
    cout << head -> right -> left -> data <<  "  ||  " << head  -> right -> right -> data <<" \n\n";
    
    
    // fourth level
    cout << "\t     " << head -> right -> left -> left -> data << "  ||  " <<  head -> right -> left -> right -> data;
    cout << "     " << head -> right -> right -> left -> data << "  ||  " <<  head -> right -> right -> right -> data << "\n\n ";
     

    // fifth level
    cout << "\t"  << head -> right -> left -> left -> left -> data << "  ||  " << head -> right -> left -> left -> right -> data;
    cout << "   " << head -> right -> left -> right -> left -> data << "  ||  " << head -> right -> left -> right -> right -> data ;
        // third
    cout << "\t\t" << head -> right -> right -> right -> left -> data << "  ||  " << head -> right -> right -> right -> right -> data << "\n";
}



int main(){
       
    // enter first/root node
    Nodeptr n = new Node;
    n -> data = 2;
    n -> left = createNode(n);  // pass the address so that the created node save this address as parent
    n -> right = createNode(n);
    n -> colour = true;
    
    head = n;

    
    insert(13);

    insert(7);
    
    insert(16);
    
    insert(19);
    
    insert(9);
    
    insert (22);
    
    insert (10);
    
    insert(14);
    
    insert(17);

    printColour();
    //printData();
    
}
    
    
    
    
    