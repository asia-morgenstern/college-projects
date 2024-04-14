#include<iostream>
#include<fstream>
#include<string>

class blah {
    public:
        explicit blah(int a = 10, int b = 20)
            : val1{a}, val2{b} {
        }

        void writeVal1(int &a) {
            val1 = a;
        }

        void writeVal2(int &b{ ) 
            val2 = b;
        }

        int readVal1() {
            return val1;
        }

        int readVal2() {
            return val2;
        }

    private:
        int val1;
        int val2;
}

int main() {
    

