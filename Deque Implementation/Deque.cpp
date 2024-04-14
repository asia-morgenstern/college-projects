#include<iostream>

template <typename Object>

class Deque {
    public:

        
        explicit Deque() {
            // Zero argument constructor - creates a doubly linked list
            
            head = tail = new Node;
            *head.next = nullptr;
            *head.prev = nullptr;            
            *tail.next = nullptr;
            *tail.prev = nullptr;
            size = 0
        }

        explicit Deque(const Deque & rhs) {
            // Copy constructor - creates a copy of rhs, another deque

            head = tail = new Node;
            *head.next = nullptr;
            *head.prev = nullptr;            
            *tail.next = nullptr;
            *tail.prev = nullptr;
            size = 0

            for (auto & x : rhs) {
                inject(x);
            }
        }

        explicit Deque(Deque && rhs) 
            : size{rhs.size}, head{rhs.head}, tail{rhs.tail} {
                // Move constructor - sets this deque to rhs, another deque

                rhs.head = nullptr;
                rhs.tail = nullptr;
                rhs.size = 0;
        }

        ~Deque() {
            // Destructor - deletes the deque 

            makeEmpty();
            delete head;
            delete tail;
        }

        Deque & operator=(const Deque & rhs) {
            // Copy assignment - makes this deque rhs, another deque

            Deque copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        Deque & operator=(Deque && rhs) {
            // Move assignment - swaps this deque with rhs, another deque

            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
            std::swap(size, rhs.size);
        }

        int size() const {
            // returns size of the deque

            return size;
        }

        bool empty() {
            // returns true if the deque is empty, false otherwise

            return (size() == 0);
        }

        void makeEmpty() {
            // makes the deque empty

            while (!empty()) {
                pop();
            }
        }

        void push(const Object & x) {
            // adds another node to the front

            Node *newNode = new Node;
            *newNode.val = x;
            *head.prev = newNode;
            *newNode.next = head;
            head = newNode;
            size++;
        }

        Object pop() {
            // removes node at the front, and returns val of that node

            if (size() == 0) {
                std::cerr << "ERROR:  No objects in deque" << std::endl;
                std::exit(-1);
            }
            Node *temp = head;
            Object retVal = *head.val;
            head = *head.next;
            head.prev = nullptr;
            delete temp;
            size--;
            return retVal;
        }

        void inject (const Object & x) {
            // adds another node to the back

            Node *newNode = new Node;
            *newNode.val = x;
            *tail.next = newNode;
            *newNode.prev = tail;
            tail = newNode;
            size++;
        }

        Object eject() {
            // removes node at the back, and returns val of that node

            if (size() == 0) {
                std::cerr << "ERROR:  No objects in deque" << std::endl;
                std::exit(-1);
            }
            Node *temp = head;
            Object retVal = *head.val;
            tail = *tail.prev;
            tail.next = nullptr;
            delete temp;
            size--;
            return retVal;
        }

        class Node {
            public:
                explicit Node(const Object & d = Object{}, Node *n = nullptr, Node *p = nullptr)
                    : val{d}, next{n}, prev{p} {
                        // Copy constructor - creates a copy of Node
                }

                explicit Node(Object && d, Node *n = nullptr, Node *p = nullptr)
                    : val{std::move(d)}, next{n}, prev{p} {
                        // Move constructor - sets this deque to rhs, another deque
                }

                ~Node() {
                    // deletes the Node

                    delete val;
                }

                Node & operator=(const Node &  rhs) {
                    // Copy assignment - makes this Node rhs, another Node

                    if (this != &rhs) {
                        val = rhs.val;
                    }
                    return *this;
                }

                Node & operator=(Node && rhs) {
                    // Move assignment - swaps this Node with rhs, another Node

                    std::swap(val, rhs.val);
                    return *this;
                }
            
            private:
                Object val;         // value stored
                Node *next;         // pointer to next Node
                Node *prev;         // pointer to previous Node
            
            friend class Deque;     // allows Deque to access Node
        }

    private:
        Node *head;     // stores the front of the deque
        Node *tail;     // stores the end of the deque
        int size;       // stores the number of elements in the deque
};
