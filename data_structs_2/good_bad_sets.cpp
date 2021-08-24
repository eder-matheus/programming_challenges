// good and bad sets - uri 2087

#include <iostream>
#include <vector>
#include <string>

const int ALPHABET = 27;

struct vertex {
  std::vector<int> edges;
  bool key = false;
  bool inside_word = false;

  vertex() {
    edges.resize(ALPHABET);
    std::fill(std::begin(edges), std::end(edges), -1);
  }
};

bool addToTrie(std::vector<vertex>& trie, const std::string& s) {
  int v = 0;
  int cnt = 0;
  for (const char ch : s) {
    cnt++;
    int c = ch - 'a';
    if (trie[v].edges[c] == -1) {
      trie[v].edges[c] = trie.size();
      trie.emplace_back();
    }
    v = trie[v].edges[c];
    if (trie[v].key) {
      return false;
    }
    if (cnt < s.size())
      trie[v].inside_word = true;
  }
  trie[v].key = true;

  if (trie[v].inside_word) {
    return false;
  }

  return true;
}

int main() {
  int word_count;
  while (std::cin >> word_count) {
    std::vector<vertex> trie(1);
    if (word_count == 0) {
      break;
    }

    std::string word;
    bool is_good = false;
    for (int i = 0; i < word_count; i++) {
      std::cin >> word;
      is_good = addToTrie(trie, word);
      if (!is_good)
        break;
    }

    if (is_good) {
      std::cout << "Conjunto Bom\n";
    } else {
      std::cout << "Conjunto Ruim\n";
    }
  }

  return 0;
}
