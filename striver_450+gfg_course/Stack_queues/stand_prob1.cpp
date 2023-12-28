/*
 Implemet lru cache
*/

//method 1 : using doubly linked list
struct Node {
    int key;
    int val;
    Node *next;
    Node *prev;
    Node(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, Node*> dic;
    Node *head = new Node(-1, -1);
    Node *tail = new Node(-1, -1);
    LRUCache(int capacity) {
        this->capacity = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (dic.find(key) == dic.end()) {
            return -1;
        }
        
        Node *node = dic[key];
        remove(node);
        add(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if (dic.find(key) != dic.end()) {
            Node *oldNode = dic[key];
            remove(oldNode);
        }
        
        Node *node = new Node(key, value);
        dic[key] = node;
        add(node);
        
        if (dic.size() > capacity) {
            Node *nodeToDelete = head->next;
            remove(nodeToDelete);
            dic.erase(nodeToDelete->key);
        }
    }
    
    void add(Node *node) {
        Node *previousEnd = tail->prev;
        previousEnd->next = node;
        node->prev = previousEnd;
        node->next = tail;
        tail->prev = node;
    }
    
    void remove(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

};

// method 2 : using inbuilt list stl fnction
class LRUCache {
public:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> dic;
    list<pair<int, int>> lru;
    
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = dic.find(key);
        
        if (it == dic.end()) {
            return -1;
        }
        
        int value = it->second->second;
        lru.erase(it->second);
        lru.push_front({key, value});
        
        dic.erase(it);
        dic[key] = lru.begin();
        return value;
    }
    
    void put(int key, int value) {
        auto it = dic.find(key);
        
        if (dic.find(key) != dic.end()) {
            lru.erase(it->second);
            dic.erase(it);
        }
        
        lru.push_front({key, value});
        dic[key] = lru.begin();
        
        if (dic.size() > capacity) {
            auto it = dic.find(lru.rbegin()->first);
            dic.erase(it);
            lru.pop_back();
        }
    }

};
-------------------------------------------