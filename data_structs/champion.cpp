// champion

#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include <map>
#include <vector>

bool cmp(const std::pair<std::string, int>& a,
         const std::pair<std::string, int>& b) {
  return a.second > b.second;
}

void getChampion(std::map<std::string, int>& table) {
  std::vector<std::pair<std::string, int> > table_vec;

  for (auto& it : table) {
    table_vec.push_back(it);
  }

  std::sort(table_vec.begin(), table_vec.end(), cmp);

  std::string champion = table_vec[0].first;
  int pts = table_vec[0].second;
  if (champion == "Sport") {
    std::cout << "O Sport foi o campeao com " << pts << " pontos :D\n\n";
  } else {
    std::cout << "O Sport nao foi o campeao. O time campeao foi o " << champion << " com " << pts << " pontos :(\n\n";
  }
}

int main() {
  int num_teams;

  while (std::cin >> num_teams) {
    if (num_teams == 0) {
      break;
    }

    std::string team;
    int pts;
    std::map<std::string, int> team_to_pts;
    for (int i = 0; i < num_teams; i++) {
      std::cin >> team >> pts;
      team_to_pts[team] = pts;
    }

    std::string team0, team1, score;
    for (int i = 0; i < num_teams/2; i++) {
      std::cin >> team0 >> score >> team1;
      
      std::stringstream stream(score);
      std::string goals;
      std::vector<int> team_goals;
      while (getline(stream, goals, '-')) {
        team_goals.push_back(stoi(goals));
      }

      team_to_pts[team0] += 3*team_goals[0];
      team_to_pts[team1] += 3*team_goals[1];
      if (team_goals[0] == team_goals[1]) {
        team_to_pts[team0] += 1;
        team_to_pts[team1] += 1;
      } else if (team_goals[0] > team_goals[1]) {
        team_to_pts[team0] += 5;
      } else {
        team_to_pts[team1] += 5;
      }
    }
    getChampion(team_to_pts);
  }

  return 0;
}
