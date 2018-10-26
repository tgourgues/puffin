//  ____         __  __ _       
// |  _ \ _   _ / _|/ _(_)_ __  
// | |_) | | | | |_| |_| | '_ \ 
// |  __/| |_| |  _|  _| | | | |
// |_|    \__,_|_| |_| |_|_| |_|          
//
// Copyright (c) 2011-2018 thomas.gourgues@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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