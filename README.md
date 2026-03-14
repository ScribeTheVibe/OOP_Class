# OOP Class

A C++ student grade management program. Reads student records from files or console input, computes final grades using both average and median, splits students into two result groups, and outputs sorted results to the terminal or files.

## Features

- Manual, random, or file-based data input
- Final grade calculated two ways: average-based (`galVid`) and median-based (`galMed`)
- Students split into two groups: **galvočiai** (final grade ≥ 5.0) and **vargšiukai** (final grade < 5.0)
- Sortable output by name, surname, or final grade (ascending/descending)
- Output to terminal or files
- File generator for benchmark datasets
- Built-in performance timing tests (Study 1 & Study 2)

## Build

```bash
g++ -O2 -o studentai main.cpp Functions.cpp FileGen.cpp Data.cpp
```

## Usage

```bash
./studentai
```

Then pick an option from the menu:

```
1 - manual input
2 - read from file
3 - auto-generate grades
4 - auto-generate names, surnames and grades
5 - exit
6 - generate 5 benchmark files
7 - run performance tests
```

## File Format

Input files must follow this structure (header line required):

```
Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz.
Vardas1 Pavarde1 7 8 5 9 6 7
Vardas2 Pavarde2 4 3 6 5 2 4
```

The last number on each line is treated as the exam result. All preceding numbers are coursework grades.

---

## v0.4 Performance Analysis

All tests run on a **Release build** (`-O2`). Each file contains 5 coursework grades and 1 exam result per student.

### Study 1 — File Generation

Measures only the time to create and close each file. No vectors used — data written directly to disk.

| File | Records | Time (s) |
|------|---------|----------|
| studentai_1000.txt | 1,000 | 0.001 |
| studentai_10000.txt | 10,000 | 0.006 |
| studentai_100000.txt | 100,000 | 0.048 |
| studentai_1000000.txt | 1,000,000 | 0.453 |
| studentai_10000000.txt | 10,000,000 | 4.780 |

File generation scales roughly linearly with record count — each 10× increase in records produces approximately a 10× increase in write time.

### Study 2 — Data Processing

Measures three separate stages using **pre-generated files** from Study 1, ensuring consistent input across runs:

- **Nuskaitymas** — reading and parsing the file into a vector
- **Rušiavimas** — splitting students into two groups (galvočiai / vargšiukai)
- **Išsaugojimas** — writing both output files to disk
- **VISO** — total wall time

| File | Records | Read (s) | Split (s) | Write (s) | Total (s) | Gerai | Blogai |
|------|---------|----------|-----------|-----------|-----------|-------|--------|
| studentai_1000.txt | 1,000 | 0.001 | 0.000 | 0.003 | 0.004 | 513 | 487 |
| studentai_10000.txt | 10,000 | 0.010 | 0.002 | 0.015 | 0.027 | 5,036 | 4,964 |
| studentai_100000.txt | 100,000 | 0.142 | 0.009 | 0.121 | 0.272 | 50,173 | 49,827 |
| studentai_1000000.txt | 1,000,000 | 1.401 | 0.090 | 1.216 | 2.707 | 503,580 | 496,420 |
| studentai_10000000.txt | 10,000,000 | 10.015 | 1.093 | 12.451 | 23.559 | 5,032,661 | 4,967,339 |

### Observations

- **Read and write dominate** — I/O accounts for the vast majority of total time at every scale. The split step is consistently the fastest stage.
- **Split scales well** — splitting 10M records takes only 1.09 s, confirming that a single linear pass through the vector is efficient.
- **Write is slower than read** at large scale (12.45 s vs 10.02 s for 10M records), likely because two output files are written sequentially.
- **Grade distribution is close to 50/50** across all file sizes, as expected from uniformly random grades.

### Screenshot
![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://pub-1407f82391df4ab1951418d04be76914.r2.dev/uploads/43d5731a-8c6c-4aab-abb6-6419e978e269.png)
---

## Project Structure

```
├── main.cpp        # entry point, menu, output
├── Headers.h       # structs, includes, all declarations
├── Methods.cpp   # skaiciuotiMediana, saugusInt, sortS, nuskaitytiIsFailo
├── FileGen.cpp         # file generator, splitter, timing tests
└── Data.cpp        # name/surname arrays
```
