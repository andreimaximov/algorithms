#!/usr/bin/env python

import argparse
import random

VERSION = '1.0.0'


def run(args):
    print(args.T)
    for T in range(0, args.T):
        N = random.randint(int(args.N/2), args.N + 1)
        print(N)
        T = random.randint(1, int(N/50) + 1)
        print(T)
        for i in range(0, N):
            print(random.randint(args.min, args.max), end=" ")
        print()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--version", action="version", version=VERSION)
    parser.add_argument("--T", help="Number of test cases", type=int,
                        default=10)
    parser.add_argument("--min", help="The minimum randomly generated a",
                        type=int, default=0)
    parser.add_argument("--max", help="The maximum randomly generated a",
                        type=int, default=1000)
    parser.add_argument("--N", help="Sets N/2 to N + 1 numbers per test case",
                        type=int, default=1000)

    args = parser.parse_args()
    run(args)

if __name__ == "__main__":
    main()
