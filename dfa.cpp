#include <iostream>

class DFinitAutomata {

      public:
      DFinitAutomata():currentState(START), decimalEncounter(false) {}

      bool processing(const std::string& input) {

        currentState = START;
        decimalEncounter = false;

        for(char c: input) {

           transitions( c );

           if(currentState == REJECTED) return false;
        }

        return currentState == ACCEPTED;
      }

      private:

      enum State {START, INTEGER, DECIMAL, SIGN, REJECTED, ACCEPTED};
      State currentState;
      bool decimalEncounter;

      void transitions(char c) {

           if(isdigit(c)) {
             currentState = INTEGER;
           } else if(c == '.') {

             if(!decimalEncounter) {
               currentState = DECIMAL;
               decimalEncounter = true;

             } else {
               currentState = REJECTED;
             }

           } else if(c == '+' || c == '-') {
               currentState = SIGN;
           } else {
             currentState = REJECTED;
           }

           if(currentState == INTEGER) currentState = ACCEPTED;
      }
};

int main(int argc, char const *argv[]) {

    DFinitAutomata automata;

    std::string input0 = "-1a23";
    std::string input1 = "123";
    std::string input2 = "-45.67";
    std::string input3 = "abc";
    std::string input4 = "12.34.56";

    std::cout << input0 << " is " << (automata.processing(input0) ? "ACCEPTED" : "REJECTED") << " number." << std::endl;
    std::cout << input1 << " is " << (automata.processing(input1) ? "ACCEPTED" : "REJECTED") << " number." << std::endl;
    std::cout << input2 << " is " << (automata.processing(input2) ? "ACCEPTED" : "REJECTED") << " number." << std::endl;
    std::cout << input3 << " is " << (automata.processing(input3) ? "ACCEPTED" : "REJECTED") << " number." << std::endl;
    std::cout << input4 << " is " << (automata.processing(input4) ? "ACCEPTED" : "REJECTED") << " number." << std::endl;

  return 0;
}
