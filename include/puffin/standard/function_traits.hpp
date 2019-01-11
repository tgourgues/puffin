//  ____         __  __ _       
// |  _ \ _   _ / _|/ _(_)_ __  
// | |_) | | | | |_| |_| | '_  | 
// |  __/| |_| |  _|  _| | | | |
// |_|    \__,_|_| |_| |_|_| |_|          
//
// BSD 3-Clause License

// Copyright (c) 2019, Thomas Gourgues (thomas.gourgues@gmail.com)
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef FUNCTION_TRAITS_HPP
#define FUNCTION_TRAITS_HPP

#include <functional>
#include <tuple>

template<typename T>
struct function_argument { static const int value = 0x0; };

template<>
struct function_argument<int> { static const int value = 0x1; };

template<>
struct function_argument<std::string> { static const int value = 0x2; };

template<>
struct function_argument<float> { static const int value = 0x3; };

template<>
struct function_argument<bool> { static const int value = 0x4; };

template<typename... Args>
struct function_tag;

template<>
struct function_tag<> {
  static const int value = 0;
};

template<typename Arg, typename... Args>
struct function_tag<Arg, Args...> {
  static const uint64_t value = function_tag<Args...>::value | function_argument<Arg>::value << (4 * sizeof...(Args));
};

template<typename F>
struct function_traits : public function_traits<decltype(&F::operator())> {
};

template <typename Return, typename... Args>
struct function_traits<Return(Args...)> {
  typedef Return return_type;
  
  template<size_t N>
  using arg_type = typename std::tuple_element<N, std::tuple<Args...>>::type;

  static constexpr size_t arity = sizeof...(Args);

  static constexpr uint64_t tag = function_tag<Args...>::value;
  static constexpr int values[] = { function_argument<Args>::value... };
};

template<typename Class, typename Return, typename... Args>
struct function_traits<Return(Class::*)(Args...) const> : public function_traits<Return(Args...)> {
  using class_type = Class;
};

template <typename F>
struct function_traits<std::function<F>>
    : public function_traits<F>
{};

#endif //FUNCTION_TRAITS_HPP