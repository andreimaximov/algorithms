#!/usr/bin/env python

import sys

# Map from max player -> values for winners. If X' is the max player, then
# a tie with '_' winning is better than 'O' winning but worse than 'X' winning.
VALUES = {'X': {'O': 0, '_': 1, 'X': 2},
          'O': {'X': 0, '_': 1, 'O': 2}}


def main():
    player = raw_input()
    board = [list(raw_input()) for _ in range(3)]
    r, c = minimax(board, player, player)[1]
    print('%s %s' % (r, c))


def minimax(board, curr_player, max_player):
    '''Runs min-max on the board.'''
    if finished(board):
        w = winner(board)
        return VALUES[max_player][w], None

    if curr_player == 'X':
        value, next_player = VALUES[max_player]['O'], 'O'
    else:
        value, next_player = VALUES[max_player]['X'], 'X'

    move = None

    for r, c in options(board):
        board[r][c] = curr_player
        value_ = minimax(board, next_player, max_player)[0]
        board[r][c] = '_'
        if (curr_player == max_player and value_ >= value) or \
           (curr_player != max_player and value_ <= value):
            value, move = value_, (r, c)

    return value, move


def options(board):
    '''Returns a generator of available moves.'''
    for r in range(3):
        for c in range(3):
            if board[r][c] == '_':
                yield (r, c)


def finished(board):
    '''Returns if the game is finished or not.'''
    if winner(board) != '_':
        return True
    for r in board:
        for x in r:
            if x == '_':
                return False
    return True


def winner(board):
    '''Returns the current winner, if one exists.'''
    for i in range(3):
        # Check rows...
        if board[i][0] != '_' and board[i][0] == board[i][1] == board[i][2]:
            return board[i][0]
        # Check cols...
        if board[0][i] != '_' and board[0][i] == board[1][i] == board[2][i]:
            return board[0][i]

    # Check diags...
    if board[0][0] != '_' and board[0][0] == board[1][1] == board[2][2]:
        return board[0][0]

    if board[2][0] != '_' and board[2][0] == board[1][1] == board[0][2]:
        return board[2][0]

    return '_'


if __name__ == '__main__':
    main()
