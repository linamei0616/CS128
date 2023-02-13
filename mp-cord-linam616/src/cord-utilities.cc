#include "cord-utilities.hpp"


std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord) {
  if (!left_cord->IsValidCord() || !right_cord->IsValidCord()) {
    throw std::invalid_argument("Not a valid cord to concat");
  }
  std::shared_ptr<Cord> new_left = std::move(left_cord);
  std::shared_ptr<Cord> new_right = std::move(right_cord);
  return std::make_shared<Cord>(new_left, new_right);
}
void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  std::map<std::string, std::shared_ptr<Cord>>
      map;  // the map holds the data and then the address of the cord
  for (std::shared_ptr<Cord>& cord : cords) {  // deferencing to get the adress
    ReduceCords(cord, map);
  }
}
void ReduceCords(std::shared_ptr<Cord>& cord,
                 std::map<std::string, std::shared_ptr<Cord>>& map) {
  // basecase
  if (map[cord->ToString()] == nullptr) {  // if it is not already in the map, DO NOT DO DATA_ this wasted me like 3 hours smfh
    map[cord->ToString()] = cord;  // add to the map, key = data, value = address
  } else {
    cord = map[cord->ToString()];  // update it to the prexisting key with the addy
  }
  // recursive
  if (cord->left_ != nullptr) {
    ReduceCords(cord->left_, map);
  }
  if (cord->right_ != nullptr) {
    ReduceCords(cord->right_, map);
  }
}