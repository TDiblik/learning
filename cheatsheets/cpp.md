# General
- my default debugging flags: `-std=c++23 -g -O0 -Wall -Werror -Wpedantic -Wshadow -Wconversion -fsanitize=address,undefined -fno-omit-frame-pointer`

# Performance optimalization
My cheat sheet to refer to when optimizing code.

It's usually about minimizing unnecessary work, memory accesses, allocations, synchronization, and unpredictable delays.

**ALWAYS PROFILE BEFORE CHANGING STUFF BLINDLY**

Do it in the following order:

| Step | Name | Info |
| ---  | ---  | ---  |
| 0. | Benchmark | benchmark every step of the process, after that, always move onto the next one. | 
| 1. | Correctness | first of all, ensure the program is correct |
| 2. | Algorithms | Before optimizing code, ensure that we're using the best algorithm possible. Not only on the paper, but also in practice. Some algorithms may have `O(n)` complexity but perform worse than `O(n log n)` because of the niput sizes and other factors. Big-O only describes how the algorithm scales, not how fast it actaully runs |
| 3. | Memory Layout | prefer linear data structures that don't jump around in memory (when it makes sense) and ideally pre-allocate when possible to avoid expensive and unpredictable runtime allocations. |
| 4. | Hot path | identify the hot path of the code (executed the most) and try to optimize it. Avoid allocations in the hot path as much as possible. |
| 5. | Compiler | after identifying the hot path, inspect the generated assembly to understand how the compiler optimizes your code. |


## Best practices
| Technique | Recomendation |
| ---- | ---- |
| Algorithm selection | Prefer least total work before micro-optimizing |
| Cache-friendly storage | Prefer `std::vector` or `std::array` with pre-allocation |
| Preallocatin | Use `reserve()`, fixed-capacity storage or memory pools (`std::pmr`) |
| Minimize heap allocations | reuse buffers / objects. Allocate outside hot paths. |
| Data-oriented design | Arrange data in the order it is accessed. |
| Avoid pointer chaising | Prefer fixed arrays over linked nodes **when possible**. |
| Avoid unnnecessary copies | For classes / larger objects / arrays Use references, moves, views and in-place constructions (`emplace()`). See `Data passing` section bellow. |
| Reduce synchronization | Limit shared mutable state as much as possible when multithreading |
| Minimize system calls | Avoid blocking I/O, logging, etc in hot paths |
| Miinimize critical|path work - Move optional formatting, diagnostics and maintenance work elsewhere |
| Optimize the compiler target | Use an optimized build, then test CPU-specific tuning and LTO	 |
| Profile before changing code | Identify actual bottlenecks using representative workloads	 |



## Data passing

| Type | Preferred approach | Reason |
|---|---|---|
| `int`, `float`, `double`, `bool` | Pass by value (`T`) | Cheap to copy, often passed using registers |
| Small `struct` | Usually pass by value (`T`) | Copying can be cheaper than passing a reference |
| Large `struct` / `class` | `const T&` for reading, `T&` for modifying | Avoids unnecessary copies |
| `const T&` | Required, read-only access | Non-owning reference, no copying |
| `T&` | Required, mutable access | Non-owning reference, modifies the original object |
| `const T*` | Optional, read-only access | Non-owning pointer, can be `nullptr` |
| `T*` | Optional, mutable access | Non-owning pointer, can be `nullptr` |
| `std::optional<T>` | Optional owned value | Stores `T` directly when present, no separate heap allocation |
| `std::optional<T&>` (C++26) | Optional, mutable reference | Like `T*`, but expresses optional reference semantics. |
| `std::optional<const T&>` (C++26) | Optional, read-only reference | Like `const T*`. |
| `std::expected<T, E>` | Return a value or an error. Prefer `enum class CustomError` for `E` when possible. | Alternative to exceptions for expected failures |
| `std::string` | `std::string_view` for reading, `std::string&` for modifying | Avoids copying string contents; view doesn't own the data |
| `std::vector<T>` | `std::span<const T>` for reading, `std::span<T>` for modifying elements, `std::vector<T>&` for modifying the container | Zero-copy access to contiguous data |
| `std::unique_ptr<T>` | Use for exclusive dynamic ownership | No reference counting. Use `std::move()` to transfer ownership, `*ptr` to access without transferring |
| `std::shared_ptr<T>` | Only when multiple owners must control the lifetime | Reference counting adds overhead. Pass by value when sharing ownership |
| `std::weak_ptr<T>` | Non-owning observer of a `shared_ptr`-managed object | Doesn't keep the object alive, use `.lock()` to access safely |
| `std::move(obj)` | When transferring resources / ownership | Enables moving instead of copying when supported. Doesn't actually move anything by itself |

**Ownership rules:**
- Prefer direct values (`T`) whenever possible.
- Use `const T&` / `T&` when an object must exist, `const T*` / `T*` when it can be absent.
- Use `std::make_unique<T>()` instead of `new` when dynamic ownership is needed.
- Don't pass smart pointers around if the function only needs access. Pass `*ptr` as a reference instead.
- Use `std::shared_ptr<T>` only when shared ownership is actually needed.
- **Prefer this order of selection when deciding what to take into the function / how to pass value around: values -> references / non-owning pointers -> unique_ptr -> shared_ptr only when necessary.**


## C++ keywords / attributes that can improve performance
| Feature | Purpose | More info |
| --- | --- | --- |
| `noexcept` | Guarantees the function cannot throw | Can enable moving instead of copying |
| `constexpr` | Allows compile-time evaluation | Can remove runtime calculations if actually evaluated at compile time |
| `consteval` | Forces compile-time evaluation | No runtime computation for those calls |
| `constinit` | Ensures static initialization | Avoids dynamic initialization for eligible variables |
| `[[likely]]` / `[[unlikely]]` | Hints which branch is more likely | Might improve branch layout, not guaranteed, see assembly before and after |
| `[[assume(condition)]]` | Tells the compiler a condition is always true | No runtime check, undefined behavior if false. Only use when guaranteed, see assembly before and after. |
| `alignas(N)` | Aligns data in memory | Can help with alignment / false sharing, but might waste memory |
| `std::move()` | Allows moving an object instead of copying it | Doesn't actually move anything by itself; **don't call it everywhere** |

- Use `assert(condition)` to check internal invariants while debugging. It usually disappears with `-DNDEBUG`.
- Use `if` / error handling for checks that must work in production.
- Use `[[assume(condition)]]` only when the condition is guaranteed to be true and the compiler needs help with this assumption.


## Containers / memory
| Feature | Recommendation |
| --- | --- |
| `std::array<T, N>` | Fixed size (known at compile time), contiguous storage, no separate allocation for the elements |
| `std::vector<T>` | Good default for dynamic arrays, data is contiguous |
| `vector.reserve(n)` | Use when you know the expected size to avoid reallocations |
| `vector.emplace_back(args...)` | Constructs inplace instead of creating a temporary value and the calling `.push_back(...)` |
| `std::pmr` / memory pools | Reuse allocated memory when normal allocations are a bottleneck |
| `std::from_chars()` | Parse numbers without allocations. When parsing only 0-9, you can use `char - '0'` instead. |


## SoA vs AoS
```cpp
// AoS
#include <vector>
struct Order {
  int price;
  int quantity;
  int id;
};
std::vector<Order> orders = {
  {100, 10, 1},
  {101, 20, 2},
  {102, 30, 3}
};

// SoA ; ofter better SIMD optimalizations
#include <vector>
struct Orders {
  std::vector<int> prices;
  std::vector<int> quantities;
  std::vector<int> ids;
};
Orders orders{
  .prices = {100, 101, 102},
  .quantities = {10, 20, 30},
  .ids = {1, 2, 3}
};
```


## Concurrency / CPU
todo: do when i learn more about it.


## Things to watch out for (!)
- **Lock-free doesn't automatically mean faster:** atomics, contention and complexity can make it worse.
- **`std::list` / `std::unordered_map` everywhere:** can have bad cache locality or extra overhead. Compare against contiguous alternatives for your workload.
- **Inlining everything:** can make the binary bigger and hurt instruction-cache performance.
- **Average latency isn't enough:** measure p95 / p99 / p99.9 as well, especially in low-latency code.


# Helpful Compiler flags
For `clang++`. **Always benchmark on the actual hardware**, more aggressive optimization doesn't always mean faster code.


## Flags explained

| Flag | Recommendation |
| --- | --- |
| `-O0` | No optimization, useful for debugging, don't benchmark with this |
| `-O1` | Basic optimizations |
| `-O2` | Good default for release builds, strong optimizations without being too aggressive |
| `-O3` | More aggressive optimizations, not always faster than `-O2`. Benchmark both |
| `-g` | Include debug symbols, useful for debugging / profiling even with `-O2` |
| `-fsanitize=address,undefined` | Detect memory bugs and undefined behavior, use for debugging, NOT benchmarking |
| `-fsanitize=thread` | Detect data races, use in a separate build, cannot combine with AddressSanitizer |
| `-Wall -Wextra -Wpedantic` | Enable useful compiler warnings |
| `-Wshadow -Wconversion` | Warn about variable shadowing and implicit conversions |
| `-Werror` | Treat all warnings as errors |
| `-fno-omit-frame-pointer` | Keeps frame pointers, useful for profiling stack traces. Might have a small performance cost |
| `-DNDEBUG` | Disables standard `assert()` checks, use for release builds |
| `-march=native` | Optimize for the CPU you're compiling on, can use CPU-specific instructions. Less portable binary |
| `-mtune=native` | Tune instruction scheduling for the current CPU without necessarily enabling new instruction sets |
| `-flto=thin` / `-flto=full` | Link-time optimization across source files. `thin` is generally faster to build and uses less memory; `full` performs more global optimization. Benchmark both |
| `-ffast-math` | Allows faster floating-point optimizations by relaxing correctness guarantees. Avoid unless you know exactly what you're doing |
| `-fno-exceptions` | Disables C++ exceptions, only use if the whole codebase is designed for this |
| `-fprofile-instr-generate` | Instrument the program to collect runtime profiling data for PGO |
| `-fprofile-instr-use=profile.profdata` | PGO, optimize using previously collected profiling data. Needs representative workloads |
| `-Rpass=<regex>` | Shows successful optimizations in the terminal. Useful values: `inline` (inlining), `loop-vectorize` (SIMD loops), `slp-vectorizer` (SIMD independent operations), `loop-unroll` (unrolling), `licm` (moving operations outside loops), `loop-delete` (removing loops) |
| `-Rpass-missed=<regex>` | Shows missed optimizations. Use the same values as above, e.g. `inline`, `loop-vectorize`, `slp-vectorizer`, `loop-unroll`. Also `regalloc` for register allocation remarks |
| `-Rpass-analysis=<regex>` | Shows more details about optimization decisions. Useful values: `loop-vectorize` (why SIMD failed), `prologepilog` / `stack-frame-layout` (stack usage), `asm-printer` / `size-info` (instruction counts / code size) |
| `-fsave-optimization-record` | Saves successful, missed and analysis optimization remarks into `.opt.yaml` files for more detailed inspection |
| `-foptimization-record-file=<file>` | Specifies where to save the optimization report |
| `-foptimization-record-passes=<regex>` | Filters which optimization passes are included in the saved report |
| `-S` | Generate assembly (`.s`) instead of an executable, useful for inspecting what the compiler actually generated |
| `-save-temps=obj` | Save intermediate compilation files alongside the output, including assembly |
| `-S -emit-llvm` | Generate LLVM IR (`.ll`) instead of assembly, useful for inspecting optimizations before machine code generation |

### Notes:
- `-O3` can make the generated code bigger and hurt instruction-cache performance. Always compare against `-O2`.
- For PGO, run the instrumented binary on realistic workloads, merge the `.profraw` files using `llvm-profdata`, then rebuild using `-fprofile-instr-use=...`.
- `<regex>` is a regular expression. Use `.*` to report everything or `(inline|loop-vectorize|loop-unroll)` to check multiple passes at once. Example: `-Rpass='(inline|loop-vectorize)' -Rpass-missed='(inline|loop-vectorize)'`
- Use `-O2` / `-O3` when inspecting optimizations, not `-O0`.
- `-Rpass` outputs to the terminal, while `-fsave-optimization-record` saves structured reports to files.
- Text from `Rpass=<regex>` untill this line was written by `chatgpt sol 6.1 xHigh`. I didn't feel like writing it out.
- **Don't benchmark with sanitizers or `-O0`.**
- For quick checking use **Compiler Explorer (godbolt.org)** to compare the generated assembly.
