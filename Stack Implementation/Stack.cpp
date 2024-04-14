#include<iostream>
#include<fstream>
#include<string>

template <typename Object>

class Stack {
    public:
        explicit Stack(int capacity = 250)\
            : size{capacity} {
            arr = new Object[size];
            theTop = 0;
        }

        ~Stack() {
            delete[] arr;
        }

        void push(Object &obj) {
            if (theTop >= size) {
                std::cerr << "ERROR:  Stack overflow" << std::endl;
                std::exit(-1);
            };
            theTop++;
            arr[theTop - 1] = obj;
        }

        Object pop() {
            if (theTop == 0) {
                std::cerr << "ERROR:  No objects in stack" << std::endl;
                std::exit(-1);
            }
            theTop--;
            return arr[theTop];
        }

        Object top() const {
            if (theTop == 0) {
                std::cerr << "ERROR:  No objects in stack" << std::endl;
                std::exit(-1);
            }
            return arr[theTop - 1];
        }

        bool isEmpty() const {
            return (theTop == 0);
        }

        void makeEmpty() {
            theTop = 0;
        }

    private:
        int size;
        int theTop;
        Object* arr;
};

int main() {
    std::string fname;

    std::cout << "Enter a file name:  ";
    std::cin >> fname;

    std::ifstream fin(fname.c_str());
    if (!fin) {
        std::cerr << "ERROR:  Could not open file " << fname << std::endl;
        std::exit(-1);
    }

    // fin.open(fname);

    Stack<char> stack;
    char x;

    if (fin.is_open()) {
        while (fin) {
            x = fin.get();
            if (x == (char) 40 or x == (char) 91 or x == (char) 123) {                  // char 40 & 41 are (), 91 & 93 are [], and 123 & 125 are {} 
                stack.push(x);
            } else if (x == (char) 41 or x == (char) 93 or x == (char) 125) {           // char 40 & 41 are (), 91 & 93 are [], and 123 & 125 are {} 
                char open = stack.pop();
                if (x == (char) 41) {
                    if (open != (char) 40) {
                        std::cerr << "ERROR:  Imbalanced delimiters ()" << std::endl;
                        std::exit(-1);
                    }
                } else if (x == (char) 93) {
                    if (open != (char) 91) {
                        std::cerr << "ERROR:  Imbalanced delimiters []" << std::endl;
                        std::exit(-1);
                    }
                } else if (x == (char) 125) {
                    if (open != (char) 123) {
                        std::cerr << "ERROR:  Imbalanced delimiters {}" << std::endl;
                        std::exit(-1);
                    }
                }
            }
        };
    };
    
    fin.close();

    if (!(stack.isEmpty())) {
        std::cerr << "ERROR:  Delimiters left open" << std::endl;
        std::exit(-1);
    }

    std::cout << "Delimiters are balanced in " << fname << std::endl;
}
