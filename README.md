# Data Compression with Ziv-Lempel Algorithm and Hash tables

In this project an algorithm for data compression is implemented. The
purpose of data compression is to take a file A and, within a reasonable amount of
time, transform it into another file B in such a way that: B is smaller than A, and it is possible to reconstruct A from B. 

The Ziv-Lempel Algorithm data compression algorithm is the basis for must popular compression programs
such as winzip, zip or gzip. Ziv-Lempel is an example of an adaptive data compression algorithm. What this
means is that the code that the algorithm uses to represent a particular sequence of
bytes in the input file will be different for different input files, and may even be
different if the same sequence appears in more than one place in the input file. The basic data structure used by the Ziv-Lempel compression algorithm is a hash
table.

This project is coded with C++
