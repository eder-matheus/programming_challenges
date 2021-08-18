// rnaa

#include <iostream>
#include <list>

int main() {
  std::string rnaa;

  while (std::cin >> rnaa) {
    std::string connections;
    connections.resize(rnaa.size());

    // create another sequence of rna that connects
    // perfectly with the original rnaa
    for (int i = 0; i < rnaa.size(); i++) {
      if (rnaa[i] == 'B') {
        connections[i] = 'S';
      } else if (rnaa[i] == 'C') {
        connections[i] = 'F';
      } else if (rnaa[i] == 'F') {
        connections[i] = 'C';
      } else if (rnaa[i] == 'S') {
        connections[i] = 'B';
      }
    }

    std::list<char> stack_of_bases;
    int conn_count = 0;

    // iterate through all the original rnaa sequence
    for (int i = 0; i < rnaa.size(); i++) {
      // add the i-th base of the original sequence to the stack while
      // not find a connection in the perfectly matching sequence
      if (stack_of_bases.empty() || connections[i] != stack_of_bases.back()) {
        stack_of_bases.push_back(rnaa[i]);
      } else {
        while (!stack_of_bases.empty() && i < connections.size()) {
          if (connections[i] == stack_of_bases.back()) {
            stack_of_bases.pop_back();
            conn_count++;
            i++;
          } else {
            break;
          }
        }
        // go back one item to add it to the stack
        i--;
      }
    }

    std::cout << conn_count << "\n";
  }

  return 0;
}
