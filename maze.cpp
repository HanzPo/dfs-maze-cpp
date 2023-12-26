#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

using namespace std;

// Must be odd values!
const int width = 25;
const int height = 19;
char maze[height][width];

vector<array<int, 2>> find_unvisited_neighbours(array<int, 2> position) {
  vector<array<int, 2>> unvisited_neighbours;

  if (position[0] == 1 && position[1] == 1) {
    if (maze[1][3] == 'w') {
      unvisited_neighbours.push_back({1, 3});
    }
    if (maze[3][1] == 'w') {
      unvisited_neighbours.push_back({3, 1});
    }
  } else if (position[0] == height - 2 && position[1] == width - 2) {
    if (maze[height - 4][width - 2] == 'w') {
      unvisited_neighbours.push_back({height - 4, width - 2});
    }
    if (maze[height - 2][width - 4] == 'w') {
      unvisited_neighbours.push_back({height - 2, width - 4});
    }
  } else if (position[0] == 1 && position[1] == width - 2) {
    if (maze[3][width - 2] == 'w') {
      unvisited_neighbours.push_back({3, width - 2});
    }
    if (maze[1][width - 4] == 'w') {
      unvisited_neighbours.push_back({1, width - 4});
    }
  } else if (position[0] == 1 && position[1] == width - 2) {
    if (maze[3][width - 2] == 'w') {
      unvisited_neighbours.push_back({3, width - 2});
    }
    if (maze[1][width - 4] == 'w') {
      unvisited_neighbours.push_back({1, width - 4});
    }
  } else if (position[0] == height - 2 && position[1] == 1) {
    if (maze[height - 4][1] == 'w') {
      unvisited_neighbours.push_back({height - 4, 1});
    }
    if (maze[height - 2][3] == 'w') {
      unvisited_neighbours.push_back({height - 2, 3});
    }
  } else if (position[0] == 1) {
    if (maze[1][position[1] - 2] == 'w') {
      unvisited_neighbours.push_back({1, position[1] - 2});
    }
    if (maze[1][position[1] + 2] == 'w') {
      unvisited_neighbours.push_back({1, position[1] + 2});
    }
    if (maze[3][position[1]] == 'w') {
      unvisited_neighbours.push_back({3, position[1]});
    }
  } else if (position[0] == height - 2) {
    if (maze[height - 2][position[1] - 2] == 'w') {
      unvisited_neighbours.push_back({height - 2, position[1] - 2});
    }
    if (maze[height - 2][position[1] + 2] == 'w') {
      unvisited_neighbours.push_back({height - 2, position[1] + 2});
    }
    if (maze[height - 4][position[1]] == 'w') {
      unvisited_neighbours.push_back({height - 4, position[1]});
    }
  } else if (position[1] == 1) {
    if (maze[position[0] + 2][1] == 'w') {
      unvisited_neighbours.push_back({position[0] + 2, 1});
    }
    if (maze[position[0] - 2][1] == 'w') {
      unvisited_neighbours.push_back({position[0] - 2, 1});
    }
    if (maze[position[0]][3] == 'w') {
      unvisited_neighbours.push_back({position[0], 3});
    }
  } else if (position[1] == width - 2) {
    if (maze[position[0] + 2][width - 2] == 'w') {
      unvisited_neighbours.push_back({position[0] + 2, width - 2});
    }
    if (maze[position[0] - 2][width - 2] == 'w') {
      unvisited_neighbours.push_back({position[0] - 2, width - 2});
    }
    if (maze[position[0]][width - 4] == 'w') {
      unvisited_neighbours.push_back({position[0], width - 4});
    }
  } else {
    if (maze[position[0] + 2][position[1]] == 'w') {
      unvisited_neighbours.push_back({position[0] + 2, position[1]});
    }
    if (maze[position[0] - 2][position[1]] == 'w') {
      unvisited_neighbours.push_back({position[0] - 2, position[1]});
    }
    if (maze[position[0]][position[1] + 2] == 'w') {
      unvisited_neighbours.push_back({position[0], position[1] + 2});
    }
    if (maze[position[0]][position[1] - 2] == 'w') {
      unvisited_neighbours.push_back({position[0], position[1] - 2});
    }
  }

  return unvisited_neighbours;
}

int main() {
  stack<array<int, 2>> cells;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i == 1 && j == 1) {
        maze[i][j] = '.';
      } else {
        maze[i][j] = 'w';
      }
    }
  }

  // Algo implementation

  // TODO: Fix how the random number generation works
  int choice = 863442;
  bool placed_target = false;
  cells.push({1, 1});
  while (cells.size() > 0) {
    srand(time(nullptr));
    choice += rand();
    array<int, 2> current_cell = cells.top();
    cells.pop();

    vector<array<int, 2>> unvisited_neighbours =
        find_unvisited_neighbours(current_cell);

    if (unvisited_neighbours.size() > 0) {
      cells.push(current_cell);

      array<int, 2> chosen_cell =
          unvisited_neighbours[choice % unvisited_neighbours.size()];

      if (chosen_cell[0] > current_cell[0]) {
        maze[chosen_cell[0] - 1][chosen_cell[1]] = '.';
      } else if (chosen_cell[0] < current_cell[0]) {
        maze[chosen_cell[0] + 1][chosen_cell[1]] = '.';
      } else if (chosen_cell[1] > current_cell[1]) {
        maze[chosen_cell[0]][chosen_cell[1] - 1] = '.';
      } else if (chosen_cell[1] < current_cell[1]) {
        maze[chosen_cell[0]][chosen_cell[1] + 1] = '.';
      }

      maze[chosen_cell[0]][chosen_cell[1]] = '.';
      cells.push(chosen_cell);
    } else {
      if (!placed_target) {
        maze[current_cell[0]][current_cell[1]] = 't';
        placed_target = true;
      }
    }
  }

  maze[1][1] = 'p';

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << maze[i][j];
    }

    cout << endl;
  }

  return 0;
}
