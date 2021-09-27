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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_pedidos, max_p;
  std::cin >> num_pedidos;

  while (num_pedidos != 0) {
    std::cin >> max_p;
    std::vector<int> t(num_pedidos);
    std::vector<int> p(num_pedidos);
    std::vector<std::vector<int>> tabela(num_pedidos + 1);
    for (int i = 0; i < tabela.size(); i++) {
      tabela[i].resize(max_p + 1, -1);
    }

    for (int i = 0; i < num_pedidos; i++) {
      std::cin >> t[i] >> p[i];
    }

    std::cout << maxTempo(t, p, 0, max_p, tabela) << " min.\n";

    std::cin >> num_pedidos;
  }

  return 0;
}
