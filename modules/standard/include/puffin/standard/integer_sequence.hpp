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

#ifndef INTEGER_SEQUENCE_HPP
#define INTEGER_SEQUENCE_HPP

#include <cstddef>

///
/// Integer and index sequence based on
/// http://stackoverflow.com/questions/17424477/implementation-c14-make-integer-sequence/17426611#17426611
///
template<typename T, T... Ints>
struct integer_sequence {
  using type = integer_sequence<T, Ints...>;
  using value_type = T;
  static constexpr std::size_t size() { return sizeof...(Ints); }
  static constexpr T values[] = { Ints... };
};

template<typename T, typename S1, typename S2>
struct merge_sequences {};

template<typename T, T... I1, T... I2>
struct merge_sequences<T, integer_sequence<T, I1...>, integer_sequence<T, I2...>>
  : integer_sequence<T, I1..., (sizeof...(I1)+I2)...>
{};

template<typename T, T Nt, std::size_t N = Nt>
struct make_integer_sequence
  : merge_sequences
    <
      T,
      typename make_integer_sequence<T, N/2>::type,
      typename make_integer_sequence<T, N - N/2>::type
    >
{};

template<typename T, T... Ints>
constexpr T integer_sequence<T, Ints...>::values[];

template<typename T, T N>
struct make_integer_sequence<T, N, 0> : integer_sequence<T> {} ;

template<typename T, T N>
struct make_integer_sequence<T, N, 1> : integer_sequence<T, T(0)> {} ;

// Types and helpers for index sequence

template<std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

template<size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

template<typename... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

#endif // INTEGER_SEQUENCE_HPP
