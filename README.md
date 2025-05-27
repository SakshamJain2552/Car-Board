# 🚗 CarBoard

An interactive console-based C++ project that simulates a car navigating through a board with obstacles. Designed to reinforce modern C++ development skills in a hands-on, engaging way.

---

## 🔥 Features

- **Dynamic 10×10 Game Board** with predefined maps.
- **Obstacle Handling** using ASCII representation (`*`).
- **Car Navigation** with directional control (↑, ↓, ←, →).
- **Command-driven Gameplay** using validated user input.
- **Menu System** with game loop and session tracking.
- **Robust Input Validation** and error feedback.
- **Modular Class Design**:
  - `Game`: manages game loop and user interaction
  - `Board`: handles map layout and rendering
  - `Player`: tracks car position and direction
  - `Helper`: processes and validates input

---

## 🛠️ Build & Run

### Prerequisites

- C++14-compatible compiler (`g++`, `clang++`, etc.)

### Build Instructions

```bash
g++ -std=c++14 -Wall -Werror -O2 \
  board.cpp carboard.cpp game.cpp helper.cpp player.cpp \
  -o carboard
````

### Run

```bash
./carboard
```

---

## 🧠 C++ Concepts Practiced

* **Pointers**
  Used for dynamic object manipulation and memory referencing within game logic.

* **Dynamic Memory Management**
  Explicit use of `new` and `delete`, along with RAII principles.

* **Arrays & Vectors**

  * Static arrays for board representations.
  * `std::vector` for dynamic input processing and flexible data storage.

* **Class Design & Encapsulation**
  Implemented using multiple interrelated C++ classes across separate translation units.

* **C++11/14 Features Used**

  * Range-based for loops
  * `auto` type deduction
  * Member initializer lists
  * Smart use of `std::string`, `std::vector`, and STL utilities
  * Type inference and scoped enumerations

