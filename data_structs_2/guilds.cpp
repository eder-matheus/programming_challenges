// guilds - uri 1527

#include <iostream>
#include <vector>
#include <string>

const int JOIN = 1;
const int FIGHT = 2;

std::vector<int> guild_level;
std::vector<int> guild;
std::vector<int> guild_size;

void buildGuild(int players_count) {
  guild.clear();
  guild_size.clear();
  guild_level.clear();

  guild.resize(players_count);
  guild_size.resize(players_count);
  guild_level.resize(players_count);
  for (int i = 0; i < players_count; i++) {
    guild[i] = i;
    guild_size[i] = 1;
  }
}

int searchInGuild(int player) {
  if (player != guild[player]) {
    guild[player] = searchInGuild(guild[player]);
  }

  return guild[player];
}

void joinGuilds(int g0, int g1) {
  int top0 = searchInGuild(g0);
  int top1 = searchInGuild(g1);

  if (top0 != top1) {
    if (guild_size[top0] >= guild_size[top1]) {
      guild[top1] = top0;
      guild_size[top0] += guild_size[top1];
      guild_level[top0] += guild_level[top1];
    } else {
      guild[top0] = top1;
      guild_size[top1] += guild_size[top0];
      guild_level[top1] += guild_level[top0];
    }
  }
}

void getPlayerGuild(int player) {
  int player_guild = searchInGuild(player);
  std::cout << "player " << player << " is in guild " << player_guild << "\n";
}

int main() {
  int num_players;
  int num_actions;

  while (std::cin >> num_players >> num_actions) {
    if (num_players == 0 && num_actions == 0) {
      break;
    }
    buildGuild(num_players);

    for (int i = 0; i < num_players; i++) {
      std::cin >> guild_level[i];
    }

    int wins = 0;
    for (int i = 0; i < num_actions; i++) {
      int action, g0, g1;
      std::cin >> action >> g0 >> g1;
      g0--;
      g1--;
      if (action == JOIN) {
        joinGuilds(g0, g1);
      } else if (action == FIGHT) {
        bool g0_my_team = searchInGuild(g0) == searchInGuild(0);
        bool g1_my_team = searchInGuild(g1) == searchInGuild(0);
        int g0_level = guild_level[searchInGuild(g0)];
        int g1_level = guild_level[searchInGuild(g1)];
        if ((g0_level > g1_level && g0_my_team) ||
            (g0_level < g1_level && g1_my_team)) {
          wins++;
        }
      } else {
        std::cout << "[ERROR] Invalid action\n";
        exit(1);
      }
    }
    std::cout << wins << "\n";
  }


  return 0;
}
