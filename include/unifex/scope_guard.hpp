/*
 * Copyright 2019-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <type_traits>

namespace unifex {

template <typename Func>
struct scope_guard {
  UNIFEX_NO_UNIQUE_ADDRESS Func func_;

  scope_guard(Func&& func) noexcept(
      std::is_nothrow_move_constructible_v<Func>)
      : func_((Func &&) func) {}

  ~scope_guard() {
    static_assert(noexcept(((Func &&) func_)()));
    ((Func &&) func_)();
  }
};

template <typename Func>
scope_guard(Func&& func)->scope_guard<Func>;

} // namespace unifex
