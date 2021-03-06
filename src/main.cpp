#include <iostream>
#include <functional>

using namespace std;

/* Linked list item. Consists of a data integer and two prev/next pointers */
struct Node {
    int data;
    struct Node* previous;
    struct Node* next;
};

/* NOTE: dash functions are reversed. i.e the _add functions appends an element to the start of the list */ 
class LinkedList
{
public:
    struct Node* firstItem = nullptr;
    struct Node* lastItem = nullptr;

    LinkedList(){}

    ~LinkedList(){}

    /* Add an element to the end of the linked list. Returns the added element's pointer */
    Node* add(int data) {
        // create new node
        Node *n = new Node;
        // set data
        n->data = data;
        n->previous = lastItem;     
        n->next = nullptr;          // n becomes the last element

        // if it's not the first element, set the last element's next attribute as n
        if(lastItem != nullptr) lastItem->next = n;
        // if it's the first one, set the firstItem POINTER
        if(firstItem == nullptr) firstItem = n;
        // set the lastItem POINTER
        lastItem = n;
        // return pointer
        return n;
    }

    /* Add an element to the START of the linked list. Returns the added element's pointer */
    Node* _add(int data) {
        Node *n = new Node;
        n->data = data;
        n->previous = nullptr;
        n->next = firstItem;
        if(firstItem != nullptr) firstItem->previous = n;
        if(lastItem == nullptr) lastItem = n;
        firstItem = n;
        return n;
    }

    /* Print the elements of the list */
    void print(char separator){
        // start from the first element
        Node* f = firstItem;

        // loop until no next pointer
        for(;;){
            if(f == nullptr) break;
            cout << f->data << separator;
            f = f->next;
        }
    }

    /* Print the elements of the list in reversed order */
    void _print(char separator){
        Node* l = lastItem;
        for(;;){
            if(l == nullptr) break;
            cout << l->data << separator;
            l = l->previous;
        }
    }

    /* Simple O(n) function to check if value is present in list */ 
    bool includes(int searchValue){
        Node* f = firstItem;
        // standard loop
        for(;;){
            if(f == nullptr) break;
            if(f->data == searchValue) return true;
            f = f->next;
        }
        return false;
    }

    /* Remove the last element of the list */
    void bonk(){
        // get last element
        Node* l = lastItem;
        // get previous element, and set its next attribute to null, and set lastItem to itself
        if(l->previous != nullptr){
            l->previous->next = nullptr;
            lastItem = l->previous;
        }
        // unallocate from memory block
        delete l;
    }

    /* Remove the first element of the list */
    void _bonk(){
        Node* f = firstItem;
        if(f->next != nullptr){
            f->next->previous = nullptr;
            firstItem = f->next;
        }
        delete f;
    }

    /* Create a constraint between two nodes. Don't link the end with the start because loop functions will break everything. */
    void constraint(Node* node, Node* node2){
        node->next = node2;
        node2->previous = node;
    }

    /* Get the node at a specific index */
    Node* at(int index){
        int i = 0;
        Node* f = firstItem;
        for(;;){
            // end of loop
            if(f == nullptr) return nullptr;
            // match
            if(i == index) return f;
            f = f->next;
            i++;
        }
    }

    /* Insert an element at a specific index. Returns the added element's pointer. NOTE: to add to the start or the end of the sequence use add/_add */
    void insertAt(int index, int data) {
        // create new node
        Node *n = new Node;
        n->data = data;
        n->previous = nullptr;  // will be set later
        n->next = nullptr;
        // get node @ index
        Node* f = at(index);
        // create constraints
        // invalid index
        if(f == 0 || f->next == nullptr || f->previous == nullptr) return;
        
        constraint(f->previous, n);
        constraint(n, f);
    }

    /* Remove element at specific index */
    void removeAt(int index){
        // get node @ index
        Node* f = at(index);
        // invalid index
        if(f == 0 || f->next == nullptr || f->previous == nullptr) return;
        
        constraint(f->previous, f->next);
    }

    /* Get the number of elements in this list */
    int size(){
        int s = 0;
        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) break;
            f = f->next;
            s++;
        }
        return s;
    }

    /* Find the first occurrence of a value in the list. Returns -1 if not found. */ 
    int firstIndexOf(function<bool(int)> lambda){
        int i = 0;
        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) return -1;
            // return index if search value matches (else -1)
            if( lambda(f->data) ) return i;
            
            f = f->next;
            i++;
        }
    }

    /* Find the last occurrence of a value in the list. Returns -1 if not found. */ 
    int lastIndexOf(function<bool(int)> lambda){
        int i = 0;
        Node* f = lastItem;
        for(;;){
            if( f == nullptr ) return -1;
            // return index if search value matches (else -1)
            if( lambda(f->data) ) return size() - i - 1;
            
            f = f->previous;
            i++;
        }
    }

    /* Get the Nth occurance's index of an element. Returns -1 if not found. */ 
    int nthIndexOf(int N, function<bool(int)> lambda){
        int i = 0;
        int _n = 0;
        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) return -1;
            
            if( lambda(f->data) ) {
                if( N == _n ) return i;
                _n++;
            }
            
            f = f->next;
            i++;
        }
    }

    /* Count the occurrances of a value in the list */
    int count(int searchValue){
        int i = 0;
        int c = 0;
        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) break;
            
            if( f->data == searchValue ) c++;
            
            f = f->next;
            i++;
        }

        return c;
    }

    /* Create a new LinkedList instance with values matching the lambda function */
    LinkedList filter( function<bool(int)> lambda ){
        LinkedList result;

        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) break;
            
            if( lambda(f->data) ) result.add(f->data);
            
            f = f->next;
        }

        return result;
    }

    /* Return the first value mathcing lambda */
    int first( function<bool(int)> lambda ){
        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) break;
            
            if( lambda(f->data) ) return f->data;
            
            f = f->next;
        }
        return 0;
    }

    /* Return the last value mathcing lambda */
    int last( function<bool(int)> lambda ){
        Node* f = lastItem;
        for(;;){
            if( f == nullptr ) break;
            
            if( lambda(f->data) ) return f->data;
            
            f = f->previous;
        }
        return 0;
    }

    /*  */
    void aggregate( function<void(int)> lambda){
        Node* f = firstItem;
        for(;;){
            if( f == nullptr ) break;
            
            lambda(f->data);
            
            f = f->next;
        }
    }
  
};


int main(){
    LinkedList list;

    list.add(21);
    list.add(212);
    list.add(11);
    list.add(212);
    list.add(214);

    // get values bigger than 21
    LinkedList biggerThan21 = list.filter([](int x){ return x > 21; });
    biggerThan21.print('\n');

    // print the first value bigger than 21
    cout << "First value bigger than 21: " << list.first( [](int x){ return x > 21; } ) << "\n";

    // print the first index of value bigger than 21
    cout << "Index of first value bigger than 21: " << list.firstIndexOf( [](int x){ return x > 21; } ) << "\n";

    list.print('\n');

    int sum = 0;
    list.aggregate([&sum](int x){ sum += x; } );

    cout << "Sum of list: " << sum << "\n";


}

