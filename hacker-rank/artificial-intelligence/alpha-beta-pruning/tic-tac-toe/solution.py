#!/usr/bin/env python

import sys


class State:
    def children(self):
        '''Returns an iterator over child states.

        NOTE: Valid only if NOT is_terminal().
        '''
        raise NotImplementedError()

    def payoff(self):
        '''Returns the payoff of the state.

        NOTE: Valid only if is_terminal().
        '''
        raise NotImplementedError()

    def payoff_lower(self):
        '''Returns a lower bound on the payoff.'''
        raise NotImplementedError()

    def payoff_upper(self):
        '''Returns an upper bound on the payoff.'''
        raise NotImplementedError()

    def is_terminal(self):
        '''Checks if the state is terminal.'''
        raise NotImplementedError()

    def is_max_player(self):
        '''Checks if the current state is a max player's turn.'''
        raise NotImplementedError()


class TicTacToe(State):
    def __init__(self, board, player, is_max_player, move=None):
        self._board = board
        self._player = player
        self._is_max_player = is_max_player
        self._move = move

    def children(self):
        player = 'X' if self._player == 'O' else 'O'
        is_max_player = not self._is_max_player

        for r in range(3):
            for c in range(3):
                if self._board[r][c] == '_':
                    board = [[x for x in row] for row in self._board]
                    board[r][c] = self._player
                    yield TicTacToe(board, player, is_max_player, (r, c))

    def payoff(self):
        winner = self._winner()

        if winner is None:
            return 0

        # Either previous min-player won (-1) or previous max-player won (+1).
        return -1 if self._is_max_player else 1

    def payoff_lower(self):
        return -1

    def payoff_upper(self):
        return 1

    def is_terminal(self):
        if self._winner() is not None:
            return True

        for r in range(3):
            for c in range(3):
                if self._board[r][c] == '_':
                    return False

        return True

    def is_max_player(self):
        return self._is_max_player

    def move(self):
        '''Returns the move used to transition to this state.'''
        return self._move

    def _winner(self):
        '''Returns the current winner, if one exists.'''
        board = self._board

        for i in range(3):
            # Check rows...
            if board[i][0] != '_' and \
               board[i][0] == board[i][1] == board[i][2]:
                return board[i][0]

            # Check columns...
            if board[0][i] != '_' and \
               board[0][i] == board[1][i] == board[2][i]:
                return board[0][i]

        # Check diagonals...
        if board[0][0] != '_' and \
           board[0][0] == board[1][1] == board[2][2]:
            return board[0][0]

        if board[2][0] != '_' and \
           board[2][0] == board[1][1] == board[0][2]:
            return board[2][0]

        return None


def main():
    player = raw_input()
    board = [list(raw_input()) for _ in range(3)]
    state = TicTacToe(board, player, True)
    state = alpha_beta_minimax_choice(state)
    print('%d %d' % state.move())


def alpha_beta_minimax_choice(state):
    '''Uses alpha beta minimax to choose the best child state.'''
    if state.is_terminal():
        raise ValueError('Terminal state does not have children!')
    elif not state.is_max_player():
        raise ValueError('State should be a max player!')

    lower, upper = state.payoff_lower(), state.payoff_upper()
    value, choice = lower, None

    for s in state.children():
        value_ = alpha_beta_minimax(s, lower, upper)
        if value_ >= value:
            value, choice = value_, s

    return choice


def alpha_beta_minimax(state, alpha, beta):
    '''Runs alpha-beta pruning version of minimax on the state tree.'''
    if state.is_terminal():
        return state.payoff()
    elif state.is_max_player():
        value = state.payoff_lower()
        for s in state.children():
            value = max(value, alpha_beta_minimax(s, alpha, beta))
            alpha = max(value, alpha)
            if alpha >= beta:
                break
        return value
    else:
        value = state.payoff_upper()
        for s in state.children():
            value = min(value, alpha_beta_minimax(s, alpha, beta))
            beta = min(beta, value)
            if beta <= alpha:
                break
        return value

if __name__ == '__main__':
    main()
