#include <iostream>
#include <fstream>

using namespace std;

int main () {
  filesystem::path path("input.txt");
  ifstream file(path);

  string line;
  vector<vector<char>> image;
  while (getline(file, line)) {
    vector<char> container;
    bool has_galaxy = false;
    for (auto c: line) {
      if (c == '#') {
        has_galaxy = true;
      }
      container.push_back(c);
    }

    image.push_back(container);
    if (!has_galaxy) {
      // expand row
      image.push_back(container);
    }
  }

  int nrow = image.size();
  int ncolumn = image[0].size();
  vector<pair<int, int>> galaxy_positions;

  for (int column = 0; column < ncolumn;  column++) {
    bool has_galaxy = false;
    int row = 0;
    for (;row < nrow; row++) {
      if (image[row][column] == '#') {
        has_galaxy = true;
        galaxy_positions.push_back(make_pair(row, column));
      }
    }

    // expand column
    if (!has_galaxy) {
      for (auto& row : image) {
        row.insert(row.begin() + column, '.');
      }
      column++;
      ncolumn++;
    }
  }

  int ret = 0;
  for (int i = 0; i < galaxy_positions.size() - 1; i++) {
    auto [x1, y1] = galaxy_positions[i];
    for (int j = i + 1; j < galaxy_positions.size(); j++) {
      auto [x2, y2] = galaxy_positions[j];
      ret += abs(x1 - x2) + abs(y1 - y2);
    }
  }


  std::cout << "Answer: " << ret << std::endl;
}
