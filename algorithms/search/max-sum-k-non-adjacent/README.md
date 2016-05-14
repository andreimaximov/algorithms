# README

This isn't a HackerRank challenge - just something I wanted to try.

## Problem

Find the sum of the top K non-adjacent integers in a list.

### Input Format

The first line contains a single integer T, the number of test cases. For every
test case, the first line contains a single integer N, where N is the size of
the list. The next line contains a single integer K. The following line contains
N integers {a<sub>1</sub>, a<sub>2</sub> ... a<sub>N</sub>}.

You can execute `python3 generator.py` to create some random input data.

### Constraints

0 <= T <= 2<sup>32</sup> - 1

0 <= N <= 2<sup>32</sup> - 1

0 < K <= N

0 <= a<sub>i</sub> <= 2<sup>32</sup> - 1

### Output Format

For each test case, print the sum of the top K non-adjacent integers of the list
or -1 if it is not possible to pick K non-adjacent integers.

### Sample Input

```
1
5
3
1 2 3 4 5
```

### Sample Output

```
9
```

### Explanation

5 + 3 + 1 = 9
