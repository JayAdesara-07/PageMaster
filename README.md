# PageMaster

PageMaster is a lightweight C++ memory-management simulation built to model how operating systems manage main memory, virtual memory, paging, and process swapping. The project demonstrates a simplified paging system where processes are loaded, executed, and moved between physical and virtual storage based on available memory and a basic LRU-style eviction policy.

It is mainly an educational project for learning:
- process loading and allocation
- page table management
- memory partitioning between main and virtual memory
- swapping pages in and out
- page replacement decisions under limited memory

## Overview

The simulator manages two memory spaces:
- main memory: faster physical memory
- virtual memory: secondary memory space used when the main memory becomes full

Each process is assigned a page table that maps virtual addresses to physical frames. The system tracks page availability, pages in use, and process states so the operating system can simulate tasks such as loading a process, running it, swapping it out, and killing it.

## Key Concepts

- Process: an executable unit represented by a `Process` object.
- Page table: maps each virtual page to a frame in main or virtual memory.
- Memory layout: main and virtual memory are represented as vectors of memory slots.
- LRU tracking: `lru` keeps a record of recently used process IDs to support swap decisions.
- Page allocator: free pages are tracked via `isFreeMain` and `isFreeVirtual`.

## Project Structure

- `main.cpp` – program entry point and command parsing
- `MemoryManager.h` – shared declarations for memory state and helpers
- `MemoryManager.cpp` – main simulator logic for memory management
- `Process.h` – process definition
- `Process.cpp` – validation logic for process file names

## Build

From the project directory, compile the project using:

```bash
g++ main.cpp MemoryManager.cpp Process.cpp -o PageMaster.exe
```

## Run

The program expects command-line arguments in a specific format. It parses the values for main memory size, virtual memory size, page size, and the names of the input/output text files.

Example:

```bash
./PageMaster.exe -M 64 -V 256 -P 4 -I input -O output
```

This means:
- main memory = 64 KB
- virtual memory = 256 KB
- page size = 4 KB
- input file = `input.txt`
- output file = `output.txt`

## Input File Format

The simulator reads a script file describing the operations to perform. The parser in `main.cpp` supports commands such as:

- `load <file1> <file2> ...`
- `run <pid>`
- `kill <pid>`
- `listpr`
- `pte <pid> <output-file>`
- `pteall <output-file>`
- `swapin <pid>`
- `swapout <pid>`
- `print <memloc> <len>`

The program stops when it encounters an unrecognized command or the input ends.

Example command script:

```text
load processA processB
run 1
listpr
pte 1 page_table
print 0 10
kill 1
```

## Process File Format

Each process file is a custom script that defines memory operations. The `run()` function reads the file, parses commands like `load`, `add`, `sub`, and `print`, and writes results to the output stream.

A typical process file begins with a size value, followed by operation lines. The project also uses address validation to ensure memory access stays within the process size.

Example process script:

```text
4
load 10, 0
add 0, 1, 2
print 0
```

The exact syntax is intentionally aligned with the parser in `MemoryManager.cpp`, which expects values in a compact, comma-separated style.

## Memory Behavior

The simulator performs the following behaviors:

1. Loads a process into main memory if enough physical pages are free.
2. Loads it into virtual memory if main memory is full but virtual memory still has space.
3. Moves a process back to main memory when a `run` or `swapin` operation requires it.
4. Uses LRU ordering to decide which process to evict when memory pressure increases.
5. Tracks page tables so individual process mappings can be dumped or inspected.

## Example Flow

A common lifecycle is:

```text
load P1
load P2
run 1
run 2
swapout 1
swapin 1
kill 2
```

This simulates process creation, execution, memory pressure, page replacement, and termination.

## Notes

This project is a teaching tool rather than a production-grade operating system component. It is useful for understanding how paging and memory management work conceptually, but it does not implement a full OS scheduler, security enforcement, or industrial-strength memory management.

## License

This project is provided as a learning example and can be adapted for coursework, study, or experimentation.
