# DNA Profiler

A C++ implementation of a dna profiler program

### Table of Contents

1. [Introduction](#1-introduction)
2. [Background](#2-background)
3. [Interface](#3-interface)
4. [How to Build](#4-how-to-build)
5. [How to Run](#5-how-to-run)

# 1. Introduction

This program does the following features: (1) receives two input files --- a CSV file that contains a DNA database and a ASCII file that contains a DNA sequence that belongs to an unknown subject; (2) creates a DNA profile and searches for a match in the DNA database. If there is a match, the program prints out the name of the match and the DNA profile, otherwise a "no match" message is displayed.

# 2. Background

DNA, the carrier of genetic information in living things, has been used in criminal justice for decades. But how, exactly, does DNA profiling work? Given a sequence of DNA, how can forensic investigators identify to whom it belongs?

Well, DNA is really just a sequence of molecules called nucleotides, arranged into a particular shape (a double helix). Each nucleotide of DNA contains one of four different bases: adenine (`A`), cytosine (`C`), guanine (`G`), or thymine (`T`). Every human cell has billions of these nucleotides arranged in sequence. Some portions of this sequence (i.e. genome) are the same, or at least very similar, across almost all humans, but other portions of the sequence have a higher genetic diversity and thus vary more across the population.

One place where DNA tends to have high genetic diversity is in [**Short Tandem Repeats** (STRs)](https://en.wikipedia.org/wiki/STR_analysis). An STR is a short sequence of DNA bases that tends to be repeated back-to-back numerous times at specific locations in DNA. The number of times any particular STR repeats varies a lot among different people. In the DNA samples below, for example, Alice has the STR `AGAT` repeated four times in her DNA, while Bob has the same STR repeated six times.

Using multiple STRs, rather than just one, can improve the accuracy of DNA profiling. If the probability that two people have the same number of repeats for a single STR is 5%, and the analyst looks at 10 different STRs, then the probability that two DNA samples match purely by chance is about 1 in 1 quadrillion (assuming all STRs are independent of each other). So if two DNA samples match in the number of repeats for each of the STRs, the analyst can be pretty confident they came from the same person. CODIS, The FBI's [DNA database](https://www.fbi.gov/services/laboratory/biometric-analysis/codis/codis-and-ndis-fact-sheet), uses 20 different STRs as part of its DNA profiling process.

What might such a DNA database look like? Well, in its simplest form, you could imagine formatting a DNA database as a _CSV_ file, wherein each row corresponds to an individual, and each column corresponds to a particular STR.

```
name,AGAT,AATG,TATC
Alice,28,42,14
Bob,17,22,19
Charlie,36,18,25
```

The data in the above file would suggest that Alice has the sequence `AGAT` repeated 28 times consecutively somewhere in her DNA, the sequence `AATG` repeated 42 times, and `TATC` repeated 14 times. Bob, meanwhile, has those same three STRs repeated 17 times, 22 times, and 19 times, respectively. And Charlie has those same three STRs repeated 36, 18, and 25 times, respectively.

So given a sequence of DNA, how might you identify to whom it belongs? Well, imagine that you looked through the DNA sequence for the **longest consecutive sequence of repeated** `AGAT` and found that the longest sequence was 17 repeats long. If you then found that the longest sequence of `AATG` is 22 repeats long, and the longest sequence of `TATC` is 19 repeats long, that would provide pretty good evidence that the DNA was Bob's. Of course, it's also possible that once you take the counts for each of the STRs, it doesn't match anyone in your DNA database, in which case you have no match.

In practice, since analysts know on which chromosome and at which location in the DNA an STR will be found, they can localize their search to just a narrow section of DNA. But we'll ignore that detail for this problem.

# 3. Interface

The program, called `dna_profiler`, reads command line arguments, as follows:

```shell
% ./dna_profiler
Usage: dna_profiler -d <database_file> -s <dna_sequence_file>
  Where the arguments are:
      <database_file>     The DNA database file.
      <dna_sequence_file> The DNA sequence file you wish to identify (find a match for).
```

The `<database_file>` is the the `CSV` file withe the names and STR counts.

The `<dna_sequence_file>` is the file that contains an unknown DNA sequence we wish to investigate (profile) and find a match for (if such a match exists).

# 4. How to Build

To create a build of this program, on the base directory of the project run the following commands:

```shell
cmake -S ./ -B build
cmake --build build
```

### Windows and MinGW

If you are running this on a Windows machine and using MinGW as a compiler, you might want to use the following command instead. This will make sure you are using MinGW and prevent any futher issues that might occur.

```shell
cmake -S ./ -B build -G "MinGW Makefiles"
cmake --build build
```

Be aware that CMake uses a cache file, so if you are already using the proper Windows command and still facing issues on the build process, either delete the `CMakeCache.txt` file on the build directory or change your build directory to a new one.

Note: Be sure to have POSIX threads, otherwise this might not run as intended or not even compile at all.

# 5. How To Run

Once you have builded the executable of the program, to run it, you can simply type:

```shell
% ./dna_profiler
Usage: dna_profiler -d <database_file> -s <dna_sequence_file>
  Where the arguments are:
      <database_file>     The DNA database file.
      <dna_sequence_file> The DNA sequence file you wish to identify (find a match for).
```

You can use any of the files present at the `data` directory.

Author: Lucas do Nascimento Ribeiro
