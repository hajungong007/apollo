/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file indexed_list.h
 **/

#ifndef MODULES_PLANNING_COMMON_INDEXED_LIST_H_
#define MODULES_PLANNING_COMMON_INDEXED_LIST_H_

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace apollo {
namespace planning {

template <typename I, typename T>
class IndexedList {
 public:
  /**
   * @brief copy object into the container
   * @param id the id of the object
   * @param object the const reference of the objected to be copied to the
   * container.
   * @return The pointer to the object in the container.
   */
  T* Add(const I id, const T& object) {
    auto* ptr = Find(id);
    if (ptr) {
      return nullptr;
    } else {
      const auto iter = object_dict_.insert(
          typename std::unordered_map<I, T>::value_type(id, object));
      object_list_.push_back(&(iter.first->second));
      return &(iter.first->second);
    }
  }

  /**
   * @brief Find object by id in the container
   * @param id the id of the object
   * @return the raw pointer to the object if found.
   * @return nullptr if the object is not found.
   */
  T* Find(const I id) {
    auto iter = object_dict_.find(id);
    if (iter == object_dict_.end()) {
      return nullptr;
    } else {
      return &iter->second;
    }
  }

  /**
   * @brief List all the items in the container.
   * @return the list of const raw pointers of the objects in the container.
   */
  const std::vector<const T*>& Items() const { return object_list_; }

 private:
  std::vector<const T*> object_list_;
  std::unordered_map<I, T> object_dict_;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_COMMON_INDEXED_LIST_H
