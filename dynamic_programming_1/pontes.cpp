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

int pontesIter(const std::vector<int> &pontes_por_regiao, int total_regioes,
               int total_pontes, std::vector<std::vector<int>> &tabela) {
  int atual = 0;
  for (int regiao = total_regioes - 1; regiao >= 0; regiao--) {
    atual = 1 - atual;
    for (int pontes = 0; pontes <= total_pontes; pontes++) {
      int solucao = tabela[1 - atual][pontes];

      if (pontes_por_regiao[regiao] <= pontes &&
          solucao <
              pontes_por_regiao[regiao] +
                  tabela[1 - atual][pontes - pontes_por_regiao[regiao]]) {
        solucao = pontes_por_regiao[regiao] +
                  tabela[1 - atual][pontes - pontes_por_regiao[regiao]];
      }

      tabela[atual][pontes] = solucao;
    }
  }

  return tabela[atual][total_pontes];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int num_regioes, num_pontes;

  while (std::cin >> num_regioes >> num_pontes) {
    std::vector<int> pontes_por_regiao(num_regioes, 0);
    std::vector<std::vector<int>> tabela(2);
    for (int i = 0; i < tabela.size(); i++) {
      tabela[i].resize(num_pontes + 1, 0);
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
        pontesIter(pontes_por_regiao, num_regioes, num_pontes, tabela);
    if (max_pontes == num_pontes) {
      std::cout << "S\n";
    } else {
      std::cout << "N\n";
    }
  }

  return 0;
}
