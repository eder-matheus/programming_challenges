// motoboy - uri 1286

#include <iostream>
#include <vector>

int maxTempo(const std::vector<int> &t, const std::vector<int> &p, int pedido,
             int pedidos_restantes, std::vector<std::vector<int>> &tabela) {
  if (tabela[pedido][pedidos_restantes] >= 0)
    return tabela[pedido][pedidos_restantes];

  if (pedido == p.size()) {
    tabela[pedido][pedidos_restantes] = 0;
    return 0;
  }

  int solucao = maxTempo(t, p, pedido + 1, pedidos_restantes, tabela);

  if (p[pedido] <= pedidos_restantes) {
    int solucao_temp =
        t[pedido] +
        maxTempo(t, p, pedido + 1, pedidos_restantes - p[pedido], tabela);
    if (solucao < solucao_temp)
      solucao = solucao_temp;
  }

  tabela[pedido][pedidos_restantes] = solucao;
  return solucao;
}

int maxTempoIter(const std::vector<int> &t, const std::vector<int> &p,
                 int pedidos_restantes, std::vector<std::vector<int>> &tabela) {
  int atual = 0;
  for (int pedido = p.size() - 1; pedido >= 0; pedido--) {
    atual = 1 - atual;
    for (int num_pedidos = 0; num_pedidos <= pedidos_restantes; num_pedidos++) {
      int solucao = tabela[1 - atual][num_pedidos];

      if (p[pedido] <= num_pedidos &&
          solucao < (t[pedido] + tabela[1 - atual][num_pedidos - p[pedido]])) {
        solucao = t[pedido] + tabela[1 - atual][num_pedidos - p[pedido]];
      }

      tabela[atual][num_pedidos] = solucao;
    }
  }

  return tabela[atual][pedidos_restantes];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_pedidos, max_p;
  std::cin >> num_pedidos;

  while (num_pedidos != 0) {
    std::cin >> max_p;
    std::vector<int> t(num_pedidos);
    std::vector<int> p(num_pedidos);
    std::vector<std::vector<int>> tabela(2);
    for (int i = 0; i < tabela.size(); i++) {
      tabela[i].resize(max_p + 1, 0);
    }

    for (int i = 0; i < num_pedidos; i++) {
      std::cin >> t[i] >> p[i];
    }

    std::cout << maxTempoIter(t, p, max_p, tabela) << " min.\n";

    std::cin >> num_pedidos;
  }

  return 0;
}
