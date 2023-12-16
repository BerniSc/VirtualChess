#!/usr/bin/python3
from stockfish import Stockfish
import sys

stockfish = Stockfish("/usr/games/stockfish")

while True:
    # read in the FEN, remove leading and Trailing Whitespaces
    data = sys.stdin.readline().strip()
    # If data is not  a fen, but the exit command then quit
    if (data == "exit"): break
    # give Stockfish the current BoardPosition
    stockfish.set_fen_position(data)
    # Print the best move
    print(stockfish.get_best_move())
    sys.stdout.flush()