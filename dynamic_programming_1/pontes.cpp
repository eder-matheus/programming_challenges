// pontes de sao petersburgo - uri 1203

#include <iostream>
#include <vector>

int pontes(const std::vector<int> &pontes_por_regiao, int regiao,
           int total_regioes, int total_pontes,
           std::vector<std::vector<int>> &tabela) {
  if (tabela[regiao][total_pontes] >= 0)
    return tabela[regiao][total_pontes];
  if (regiao >= total_regioes) {
    tabela[regiao][total_pontes] = 0;
    return 0;
  }

  int solucao = pontes(pontes_por_regiao, regiao + 1, total_regioes,
                       total_pontes, tabela);

  if (pontes_por_regiao[regiao] <= total_pontes) {
    int solucao_temp = pontes_por_regiao[regiao] +
                       pontes(pontes_por_regiao, regiao + 1, total_regioes,
                              total_pontes - pontes_por_regiao[regiao], tabela);

    if (solucao < solucao_temp)
      solucao = solucao_temp;
  }

  tabela[regiao][total_pontes] = solucao;
  return solucao;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_regioes, num_pontes;

  while (std::cin >> num_regioes >> num_pontes) {
    std::vector<int> pontes_por_regiao(num_regioes, 0);
    std::vector<std::vector<int>> tabela(num_regioes + 1);
    for (int i = 0; i < tabela.size(); i++) {
      tabela[i].resize(num_pontes + 1, -1);
    }

    int rA, rB;
    for (int i = 0; i < num_pontes; i++) {
      std::cin >> rA >> rB;
      rA--;
      rB--;
      pontes_por_regiao[rA]++;
      pontes_por_regiao[rB]++;
    }

    int max_pontes =
        pontes(pontes_por_regiao, 0, num_regioes, num_pontes, tabela);
    if (max_pontes == num_pontes) {
      std::cout << "S\n";
    } else {
      std::cout << "N\n";
    }
  }

  return 0;
}
