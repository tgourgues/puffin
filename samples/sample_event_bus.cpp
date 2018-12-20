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

#include <puffin/events.hpp>
#include <iostream>

using namespace pfn::events;

struct my_event {};
struct my_event_2 {};
struct my_event_3 {};
struct my_event_4 {};

using my_events = events
<
  my_event, 
  my_event_2,
  my_event_3
>;

class my_class {
public:
  void handle(const my_event& e) {
    std::cout << "class: my_event handler" << std::endl;
  }
};

int main(int argc, char** argv) {
  my_class m;
  event_bus<my_events> bus;

  std::function<void(const my_event_2&)> f = [](const my_event_2& e) {
    std::cout << "std::function my_event_2 handler" << std::endl;
  };

  bus.add_handler<my_event>([](const my_event& e) {
    std::cout << "lambda my_event handler" << std::endl;
  });

  bus.add_handler<my_event_2>(f);

  /*bus.add_handler<my_event>(
    std::bind(&my_class::handle, &m, std::placeholders::_1)
  );*/
  
  bus.add_handler<my_event>(&m);

  bus.send(my_event());
  bus.send(my_event_2());
  
  //bus.clear<my_event>();
  bus.remove_handler<my_event>(&m);

  bus.send(my_event());
  bus.send(my_event_2());

  return 0;
}
