#include <bits/stdc++.h>

using namespace std;  // NOLINT

//
// Returns the 1st first short name option.
//
string first(const string& team) {
  return team.substr(0, 3);
}

//
// Returns the 2nd short name option.
//
string second(const string& team, const string& town) {
  return team.substr(0, 2) + town.substr(0, 1);
}


int main() {
  int n;
  cin >> n;

  // (1st, 2nd) short name options for each team.
  vector<pair<string, string>> options(n);

  // Number of teams mapping to each 1st short name option.
  unordered_map<string, int> counts;

  for (int i = 0; i < n; i++) {
    string team, town;
    cin >> team >> town;
    options[i].first = first(team);
    options[i].second = second(team, town);
    counts[options[i].first]++;
  }

  // Short names that have already been used.
  unordered_set<string> used;

  // Selected short name option for each team.
  vector<string> names(n);

  // Number of teams for which we have chosen a short name option.
  int k = 0;

  // Find teams which share their first short name option with at least one
  // other team. All such teams must use their second short name option to not
  // violate the last naming rule. (See problem statement)
  for (int i = 0; i < n; i++) {
    if (counts[options[i].first] > 1) {
      // Check for conflict!
      if (used.find(options[i].second) != used.end()) {
        cout << "NO" << endl;
        return 0;
      }

      // Use second short name option if no conflict.
      used.insert(options[i].second);
      names[i] = options[i].second;
      k++;
    }
  }

  bool conflicts = true;

  // All remaining teams have unique 1st short name options. However some of
  // these options may have already been taken as the 2nd short name in the
  // previous section. Thus, we may have to choose the 2nd short name option
  // for some of the remaining teams. We do this via BFS by processing teams in
  // layers, where the next layer consists of teams with a conflict in either
  // the 1st or 2nd short name choice so there is no amiguity with which one to
  // use.
  while (conflicts) {
    conflicts = false;

    for (int i = 0; i < n; i++) {
      if (names[i].empty()) {
        bool f = used.find(options[i].first) == used.end();
        bool s = used.find(options[i].second) == used.end();

        // Check if both options are taken already.
        if (!f && !s) {
          cout << "NO" << endl;
          return 0;
        } else if (!f && s) {
          names[i] = options[i].second;
        } else if (f && !s) {
          names[i] = options[i].first;
        } else {
          continue;
        }

        // Mark the selected option as used.
        conflicts = true;
        used.insert(names[i]);
        k++;
      }
    }
  }

  // Assign remaining teams with unique and 1st and 2nd short name options.
  for (int i = 0; i < n; i++) {
    if (names[i].empty()) {
      names[i] = options[i].first;
    }
  }

  // Display chosen names.
  cout << "YES" << endl;
  for (int i = 0; i < n; i++) {
    cout << names[i] << endl;
  }

  return 0;
}

