#include "catch.hpp"
#include "puffin/events.hpp"

using namespace pfn::events;

struct my_event {};
struct my_event_2 {};

using my_events = events
<
  my_event,
  my_event_2
>;

class test {
public:
  void handle(const my_event& e) {
    throw "my_event";
  }

  void handle(const my_event_2& e) {
    throw "my_event_2";
  }
};

TEST_CASE("Events are received or not", "[Events]") {
  event_bus<my_events> bus;

  bus.add_handler<my_event>([](const my_event& e) {
    throw "my_event";
  });

  SECTION("Events are received") {
    REQUIRE_THROWS_WITH(bus.send(my_event()), Catch::Contains("my_event"));
  }

  SECTION("Events handlers can be cleared") {
    test t;

    bus.add_handler<my_event_2>(&t);

    bus.clear<my_event>();
    REQUIRE_NOTHROW(bus.send(my_event()));
    REQUIRE_THROWS_WITH(bus.send(my_event_2()), Catch::Contains("my_event_2"));
  }

  SECTION("Events handlers can be removed") {
    test t;

    bus.add_handler<my_event_2>(&t);
    REQUIRE_THROWS_WITH(bus.send(my_event_2()), Catch::Contains("my_event_2"));
    
    bus.remove_handler<my_event_2>(&t);
    REQUIRE_NOTHROW(bus.send(my_event_2()));
  }

  SECTION("All events handler can be cleared") {
    test t;

    bus.add_handler<my_event_2>(&t);
    bus.clear_all();

    REQUIRE_NOTHROW(bus.send(my_event()));
    REQUIRE_NOTHROW(bus.send(my_event_2()));
  }

  SECTION("Multiple events can be registered or cleared") {
    test t;

    bus.clear_all();
    register_events<my_event, my_event_2>(bus, &t);

    REQUIRE_THROWS_WITH(bus.send(my_event()), Catch::Contains("my_event"));
    REQUIRE_THROWS_WITH(bus.send(my_event_2()), Catch::Contains("my_event_2"));

    unregister_events<my_event, my_event_2>(bus, &t);

    REQUIRE_NOTHROW(bus.send(my_event()));
    REQUIRE_NOTHROW(bus.send(my_event_2()));
  }
}