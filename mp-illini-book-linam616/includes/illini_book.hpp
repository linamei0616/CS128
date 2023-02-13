#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string& relationship) const;
  size_t CountGroups(const std::vector<std::string>& relationships) const;
  std::map<int, std::list<int>> ToGetAdj() const { return adj_; }
  // Helper functions
  std::list<int> GetAdjacencyList(int UIN) const;
  std::list<int> GetAdjacencyList(int UIN,
                                  const std::string& relationship) const;
  std::list<int> GetAdjacencyList(
      int UIN, const std::vector<std::string>& relationships) const;
  void DFS(int vertex, std::map<int, bool>& visited) const;
  void DFS(int v,
           std::map<int, bool>& visited,
           const std::string& relationship) const;
  void DFS(int v,
           std::map<int, bool>& visited,
           const std::vector<std::string>& relationships) const;
  void AddVertex(int UIN);
  bool VertexInGraph(int UIN);
  bool PeopleNodeRelationship(int UIN, const std::string& relationship) const;
  int GetRelatedSteps(int uin_1, int uin_2, int n) const;

private:
  std::vector<int> people_nodes_;
  std::map<int, std::list<int>> adj_;
  std::map<std::pair<int, int>, std::string> relationships_;
};
std::ostream& operator<<(std::ostream& os, const IlliniBook& book);

#endif
