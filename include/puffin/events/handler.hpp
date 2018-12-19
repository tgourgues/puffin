//  ____         __  __ _       
// |  _ \ _   _ / _|/ _(_)_ __  
// | |_) | | | | |_| |_| | '_  | 
// |  __/| |_| |  _|  _| | | | |
// |_|    \__,_|_| |_| |_|_| |_|          
//
// Copyright (c) 2011-2019 thomas.gourgues@gmail.com
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

#ifndef PFN_HANDLER_HPP
#define PFN_HANDLER_HPP

namespace cxe {
namespace events {

template<typename Event>
class handler {
public:
  using fn_type = std::function<void(const Event&)>;

public:
  handler(const fn_type& f)
    : owner_((size_t)this), f_(f)
  {}

  handler(size_t owner, const fn_type& f)
    : owner_(owner), f_(f)
  {}

  bool operator==(size_t rhs) const 
  {
    return owner_ == rhs;
  }

  void operator()(const Event& e) const
  {
    f_(e);
  }

private:
  size_t owner_;
  fn_type f_;
};

}
}

#endif // PFN_HANDLER_HPP