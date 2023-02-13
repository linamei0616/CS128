#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <utilities.hpp>

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream people_file{people_fpath};  // transferring data for first file
  if (!people_file.is_open()) {
    throw std::runtime_error("People_ile is not open!");
  }
  for (std::string line; std::getline(people_file, line); line = "") {
    people_nodes_.push_back(std::stoi(line));
  }
  people_file.close();  // finished with transferring data for first file

  std::ifstream relationship_file{
      relations_fpath};  // transfering data for the second file
  if (!relationship_file.is_open()) {
    throw std::runtime_error("Relationship_file is not open!");
  }
  std::vector<std::vector<std::string>> data;
  for (std::string line; std::getline(relationship_file, line); line = "") {
    std::vector<std::string> vect = utilities::Split(line, ',');
    data.push_back(vect);
  }
  for (size_t row = 0; row < data.size(); row++) {
    for (size_t word = 0; word < data[row].size(); word += 3) {
      int first_uin = std::stoi(data[row][word]);
      int second_uin = std::stoi(data[row][word + 1]);
      std::string rel = data[row][word + 2];
      auto pair = std::make_pair(first_uin, second_uin);
      relationships_.emplace(pair, rel);
      adj_[first_uin].push_back(second_uin);
      adj_[second_uin].push_back(first_uin);
    }
  }
  relationship_file.close();  // finished with transferring data for first file
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  return (GetRelated(uin_1, uin_2) !=
          -1);  // if it = -1, then they are not related
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  return (GetRelated(uin_1, uin_2, relationship) !=
          -1);  // if it = -1, then they are not related
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::map<int, bool> visited;  // holds all the visited nodes, int = uin
  for (auto it = adj_.begin(); it != adj_.end(); it++) {
    visited.insert(std::pair<int, bool>(
        it->first, false));  // because we haven't visited yet
  }
  std::queue<std::pair<int, int>>
      q;  // first int = uin, the int holds the level of each node
  q.push(std::pair<int, int>(uin_1, 0));  // starts at level 0, first int = uin
  visited[uin_1] = true;
  while (!q.empty()) {
    std::pair<int, int> node =
        q.front();  // set first element = to node, therefore node is the UIN,
                    // and the level
    q.pop();        // remove the first element
    if (node.first == uin_2) {
      return node.second;
    }
    for (int it : GetAdjacencyList(node.first)) {
      if (!visited[it]) {
        visited[it] = true;
        q.push(
            std::pair<int, int>(it, node.second + 1));  // increase level by 1
      }
    }
  }
  return -1;
}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::map<int, bool> visited;  // holds all the visited nodes, int = uin
  for (auto it = adj_.begin(); it != adj_.end(); it++) {
    visited.insert(std::pair<int, bool>(
        it->first, false));  // because we haven't visited yet
  }
  std::queue<std::pair<int, int>>
      q;  // first int = uin, the int holds the level of each node
  q.push(std::pair<int, int>(uin_1, 0));  // starts at level 0, first int = uin
  visited[uin_1] = true;
  while (!q.empty()) {
    std::pair<int, int> node =
        q.front();  // set first element = to node, therefore node is the UIN,
                    // and the level
    q.pop();        // remove the first element
    if (node.first == uin_2) {
      return node.second;
    }
    for (int it : GetAdjacencyList(node.first, relationship)) {
      if (!visited[it]) {
        visited[it] = true;
        q.push(
            std::pair<int, int>(it, node.second + 1));  // increase level by 1
      }
    }
  }
  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> vect;
  std::map<int, bool> visited;
  for (auto it = adj_.begin(); it != adj_.end(); it++) {
    visited.insert(std::pair<int, bool>(it->first, false));
  }
  std::queue<std::pair<int, int>> q;
  q.push(std::pair<int, int>(uin, 0));
  visited[uin] = true;
  while (!q.empty()) {
    std::pair<int, int> node = q.front();
    q.pop();
    for (int adj : GetAdjacencyList(node.first)) {
      if (!visited[adj]) {
        visited[adj] = true;
        if (node.second + 1 == n) {
          vect.push_back(adj);
        }
        q.push(std::pair<int, int>(adj, node.second + 1));
      }
    }
  }
  return vect;
}
size_t IlliniBook::CountGroups() const {
  std::map<int, bool> visited;
  unsigned int count = 0;
  for (unsigned int i = 0; i < people_nodes_.size(); i++) {
    visited.insert({people_nodes_[i], false});
    if (!(visited[people_nodes_[i]])) {
      DFS(people_nodes_[i], visited);
      count += 1;
    }
  }
  return count;
}
size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::map<int, bool> visited;
  unsigned int count = 0;
  for (unsigned int i = 0; i < people_nodes_.size(); i++) {
    visited.insert({people_nodes_[i], false});
    if (!(visited[people_nodes_[i]])) {
      DFS(people_nodes_[i], visited, relationship);
      count += 1;
    }
  }
  return count;
}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  std::map<int, bool> visited;
  unsigned int count = 0;
  for (unsigned int i = 0; i < people_nodes_.size(); i++) {
    visited.insert({people_nodes_[i], false});
    if (!(visited[people_nodes_[i]])) {
      DFS(people_nodes_[i], visited, relationships);
      count += 1;
    }
  }
  return count;
}

// own helper functions

bool IlliniBook::PeopleNodeRelationship(int UIN,
                                        const std::string& relationship) const {
  for (auto const& [key, value] : relationships_) {
    if (key.first == UIN || key.second == UIN) {
      if (value == relationship) {
        return true;
      }
    }
  }
  return false;
}

void IlliniBook::AddVertex(int UIN) {
  if (VertexInGraph(UIN)) {
    throw std::runtime_error("vertex already in graph.");
  }
  adj_[UIN] = std::list<int>();
}

std::list<int> IlliniBook::GetAdjacencyList(int UIN) const {
  for (const auto& i : adj_) {
    if (i.first == UIN) {
      return i.second;
    }
  }
  // return adj_.find(UIN)->second; // NOT SURE why this would not work ...
  return std::list<int>();
}
std::list<int> IlliniBook::GetAdjacencyList(
    int UIN, const std::string& relationship) const {
  std::list<int> adj_list;
  for (const auto& i : relationships_) {
    if (i.second == relationship) {
      if (i.first.first == UIN) {
        adj_list.push_back(i.first.second);
      } else if (i.first.second == UIN) {
        adj_list.push_back(i.first.first);
      }
    }
  }
  return adj_list;
}
std::list<int> IlliniBook::GetAdjacencyList(
    int UIN, const std::vector<std::string>& relationships) const {
  std::list<int> adj_list;
  for (const auto& i : relationships_) {
    for (const auto& j : relationships) {
      if (i.second == j) {
        if (i.first.first == UIN) {
          adj_list.push_back(i.first.second);
        } else if (i.first.second == UIN) {
          adj_list.push_back(i.first.first);
        }
      }
    }
  }
  return adj_list;
}

bool IlliniBook::VertexInGraph(int UIN) {
  return (adj_.find(UIN) != adj_.end());
}

void IlliniBook::DFS(int v, std::map<int, bool>& visited) const {
  visited[v] = true;
  for (int it : GetAdjacencyList(v)) {
    if (!visited[it]) {
      DFS(it, visited);
    }
  }
}

void IlliniBook::DFS(int v,
                     std::map<int, bool>& visited,
                     const std::string& relationship) const {
  visited[v] = true;
  for (int it : GetAdjacencyList(v, relationship)) {
    if (!visited[it]) {
      DFS(it, visited, relationship);
    }
  }
}
void IlliniBook::DFS(int v,
                     std::map<int, bool>& visited,
                     const std::vector<std::string>& relationships) const {
  visited[v] = true;
  for (int it : GetAdjacencyList(v, relationships)) {
    if (!visited[it]) {
      DFS(it, visited, relationships);
    }
  }
}

std::ostream& operator<<(std::ostream& os, const IlliniBook& book) {
  os << "Contents:" << std::endl;

  for (const auto& pair : book.ToGetAdj()) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }

  return os;
}