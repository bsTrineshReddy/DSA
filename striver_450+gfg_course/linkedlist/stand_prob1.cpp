/*
 basics of singly linked list
*/
class Node{
    Public: // access modifier
    int data; // the data value
    Node* next; // the pointer to the next value
    Public:
    // constructor
    Node (int data1, Node* next1){
        data=data1;  // Initialize data with the provided value
        next=next1;  // Initialize next with the provided
    }
    Node (int data1){
        data=data1;  // Initialize data with the provided value
        next=nullptr;  // Initialize next as null since it's the end of the list

    }
};
int main(){
    vector<int> arr={2,5,8,7};
    Node* y= new Node(arr[0]);
    cout<<y<<'\n'; // returns the memory value
    cout<<y->data<<'\n'; // returns the data stored at that memory point
}
-------------------------------
ListNode * InsertatFirst(int value, ListNode * head) {

  // Step1 : creating a new Node with the given val
  ListNode * newnode = new ListNode(value);

  // Step2 : Making next of newly created Node to point the head of LinkedList
  newnode -> next = head;

  // Making the newly created Node as head
  head = newnode;
  return head;
}
----------------------------------
// Function to delete the tail node of a linked list and return the new head
Node* deleteTail(Node* head) {
    // If the list is empty or has only one node, return NULL
    if (head == NULL || head->next == NULL)
        return NULL;
    // Initialize a temporary pointer to traverse the list
    Node* temp = head;
    // Traverse to the second last node in the list
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    // Delete the last node
    delete temp->next;
    // Set the next of the second last node to nullptr, effectively removing the last node
    temp->next = nullptr;
    // Return the head of the modified list
    return head;
}
-------------------------------
int lengthOfLinkedList(Node* head) {
    Node* temp = head;
    int cnt = 0;
    // Traverse the linked list and count nodes
    while (temp != NULL) {
        temp = temp->next;
        cnt++; // increment cnt for every node traversed
    }
    return cnt;
}
-------------------------------
int checkifPresent(Node* head, int desiredElement) {
    Node* temp = head;

    // Traverse the linked list
    while (temp != nullptr) {
        // Check if the current node's data is equal to the desired element
        if (temp->data == desiredElement)
            return 1;  // Return 1 if the element is found

        // Move to the next node
        temp = temp->next;
    }

    return 0;  // Return 0 if the element is not found in the linked list
}
---------------------------------------------------------------------------------------------
/*
 basics of doubly linked list
*/
class Node {
public:
    int data;       // Data stored in the node
    Node* next;     // Pointer to the next node in the list (forward direction)
    Node* back;     // Pointer to the previous node in the list (backward direction)

    // Constructor for a Node with both data, a reference to the next node, and a reference to the previous node
    Node(int data1, Node* next1, Node* back1) {
        data = data1;
        next = next1; // Similar to a singly linked list, but now with a 'back' pointer.
        back = back1; // Addition of 'back' pointer for the doubly linked list.
    }

    // Constructor for a Node with data, and no references to the next and previous nodes (end of the list)
    Node(int data1) {
        data = data1;
        next = nullptr; // Similar to a singly linked list.
        back = nullptr; // Addition of 'back' pointer initialization.
    }
};
-------------------------------
Node* insertAtTail(Node* head, int k) {
    // Create a new node with data 'k'
    Node* newNode = new Node(k);

    // If the doubly linked list is empty, set 'head' to the new node
    if (head == nullptr) {
        return newNode;
    }

    // Traverse to the end of the doubly linked list
    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // Connect the new node to the last node in the list
    tail->next = newNode;
    newNode->back = tail;

    return head;
------------------------------------
Node* deleteTail(Node* head) {
    if (head == nullptr || head->next == nullptr) {
     // If the list is empty or has only one node, return null
        return nullptr;  
    }
    
    Node* tail = head;
    while (tail->next != nullptr) {
     // Traverse to the last node (tail)
        tail = tail->next; 
    }
    
    Node* newTail = tail->back;
    newTail->next = nullptr;
    tail->back = nullptr;
    
    // Free memory of the deleted node
    delete tail;  
    
    return head;
}
-----------------------------------
/*
 reverse doubly linked list
*/

// method1: brute force
// Stack Brute Force Approach
Node* reverseDLL(Node* head){
    // if head is empty or there is only one element
    // we can directly just return the head
    if(head==NULL || head->next == NULL){
        return head;
    }
    
    // Initialise a stack st
    stack<int> st;
    
    // Initialise the node pointer temp at head
    Node* temp = head;
    
    // Traverse the doubly linked list via the temp pointer
    while(temp!=NULL){
        // insert the data of the current node into the stack
        st.push(temp->data);
        // traverse further
        temp = temp->next;
    }
    
    // Reinitialise temp to head
    temp = head;
    
    // Second iteration of the DLL to replace the values
    while(temp!=NULL){
        // Replace the value pointed via temp with
        // the value from the top of the stack
        temp->data = st.top();
        // Pop the value from the stack
        st.pop();
        // Traverse further
        temp = temp->next;
    }
    
    // Return the updated doubly linked 
    // where the values of nodes from both ends 
    // has been swapped
    return head;

}
-------------------------------
// method 2: optimal approach
// Function to reverse a doubly linked list
// In-place link exchange method
Node* reverseDLL(Node* head) {
    
    // Check if the list is empty
    // or has only one node
    if (head == NULL || head->next == NULL) {
        // No change is needed;
        // return the current head
        return head; 
    }
    
     // Initialize a pointer to
     // the previous node
    Node* prev = NULL;  
    
    // Initialize a pointer to
    // the current node
    Node* current = head;   

    // Traverse the linked list
    while (current != NULL) {
        // Store a reference to
        // the previous node
        prev = current->back; 
        
        // Swap the previous and
        // next pointers
        current->back = current->next; 
        
        // This step reverses the links
        current->next = prev;          
        
        // Move to the next node
        // in the original list
        current = current->back; 
    }
    
    // The final node in the original list
    // becomes the new head after reversal
    return prev->back;
}
------------------------------------------------------------------------------------------------------------