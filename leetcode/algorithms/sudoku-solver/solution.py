#!/usr/bin/env python


class IndexedBoard(object):
    """
    Represents a board with indexed rows, columns, and 3 x 3 regions for
    efficiently mutating the board and checking if moves are valid.
    """
    def __init__(self, board, rows, cols, regions):
        self._board = board
        self._rows = rows
        self._cols = cols
        self._regions = regions

    def isValid(self, row, col, digit):
        """
        Checks if calling place(row, col, digit) will result in a valid board
        state.
        """
        digit = int(digit)
        if digit == 0:
            return True

        return not self._rows[row][digit] and \
            not self._cols[col][digit] and \
            not self._regions[row//3][col//3][digit]

    def place(self, row, col, digit):
        """
        Places digit into board[row][col]. Ensures the board stays in a valid
        state.
        """
        assert self.isValid(row, col, digit)

        # Clear out the previous digit.
        current = self.get(row, col)
        self._rows[row][current] = False
        self._cols[col][current] = False
        self._regions[row//3][col//3][current] = False

        # Place the new digit.
        digit = int(digit)
        self._rows[row][digit] = True
        self._cols[col][digit] = True
        self._regions[row//3][col//3][digit] = True

        # Update the actual board.
        self._board[row][col] = str(digit) if digit > 0 else '.'

    def get(self, row, col):
        """
        Gets the digit at board[row][col] as an int.
        """
        digit = self._board[row][col]
        return int(digit) if digit != '.' else 0

    @staticmethod
    def build(board):
        """
        Maps out the digits currently in each row, cell, and 3 x 3 region on
        the board and creates an IndexedBoard.
        """
        def digit_set():
            return [False for _ in range(0, 10)]

        regions = [[digit_set() for _ in range(0, 3)] for _ in range(0, 3)]
        rows = [digit_set() for _ in range(0, 9)]
        cols = [digit_set() for _ in range(0, 9)]
        indexed = IndexedBoard(board, rows, cols, regions)
        for r in range(0, 9):
            for c in range(0, 9):
                digit = board[r][c]
                indexed.place(r, c, 0 if digit == '.' else int(digit))
        return indexed


class Solution(object):
    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        """
        board = IndexedBoard.build(board)
        self._solve(board, 0, 0)

    def _solve(self, board, row, col):
        """
        Solves the sudoku board using backtracking. The IndexedBoard is able to
        check if a board state is legal in O(1) making this fairly efficient.

        :type board: IndexedBoard
        """
        if row > 8:
            # Solution found!
            return True
        elif col > 8:
            # Go to the next row.
            return self._solve(board, row + 1, 0)
        elif board.get(row, col) != 0:
            # Skip non-empty cells.
            return self._solve(board, row, col + 1)

        # Try each digit for this cell.
        for digit in range(1, 10):
            if not board.isValid(row, col, digit):
                continue
            board.place(row, col, digit)
            if self._solve(board, row, col + 1):
                return True
            board.place(row, col, 0)

        # Empty this cell.
        return False


def main():
    print('Please run this solution on LeetCode.')
    print('https://leetcode.com/problems/sudoku-solver/')

if __name__ == '__main__':
    main()
