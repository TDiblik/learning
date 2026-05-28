# Formal Learning

This is my central repository for all formal self-learning, book notes, and interview prep.

I mainly created this repo to have a single, unified place to track what I've learned from formal sources. I have other repos where I learn things by building actual projects, but this one is strictly for studying, taking notes, and testing isolated code snippets.

I'll organize everything by topic or book, adding directories for different subjects as I go.

## LeetCode
- Tracks my progress through various coding challenges.
- Follows (kinda) the outlined [NeetCode Roadmap 250](https://neetcode.io/roadmap).
- Uses Catch2 for unit testing so I don't have to write boilerplate `main()` functions.
- Includes a streamlined `Makefile` for compiling, testing, and debugging.

### Testing Solutions
For compilation and (quick) testing of each solution I use:
```sh
# Template
make <problem name (should match directory)> <.cpp file name with the solution>

# Usually I include naive and final versions:
# 
# Run the final optimized version of a problem after I've though it through
make 1-Two-Sum final
# Run the naive version I wrote before thinking too long about the problem
make 1-Two-Sum naive

# Compile and drop directly into LLDB for debugging
make lldb 1-Two-Sum final
```
