from dataclasses import dataclass
from typing import List, Tuple
from enum import Enum


class Orientation(Enum):
    Up = 3
    Left = 0
    Down = 1
    Right = 2


def orientation_dist_val(o: Orientation) -> Tuple[int, int]:
    return {
        Orientation.Up: (0, 1),
        Orientation.Left: (-1, 0),
        Orientation.Down: (0, -1),
        Orientation.Right: (1, 0)
    }[o]


def orientation_char(o: Orientation) -> str:
    if o == Orientation.Up or o == Orientation.Down:
        return '|'
    return '_'


def fold_orientation(o: Orientation) -> Orientation:
    return {
        Orientation.Up: Orientation.Left,
        Orientation.Left: Orientation.Down,
        Orientation.Down: Orientation.Right,
        Orientation.Right: Orientation.Up
    }[o]


@dataclass
class Edge:
    direction: Orientation
    pos_x: int
    pos_y: int

    def _str_(self):
        return f'{self.direction.name} ({self.pos_x}, {self.pos_y}'


@dataclass
class Extremes:
    max_x: int
    min_x: int
    max_y: int
    min_y: int


@dataclass
class Dragon:
    fold_count: int
    parts: List[Edge]
    size: Tuple[int, int]
    extremes: Extremes

    def fold(self) -> None:
        self.parts = self.parts + [ Edge(fold_orientation(x.direction), 0, 0) for x in self.parts[::-1]]
        self.add_positions()

        self.fold_count = self.fold_count + 1
        self.set_size()

    def add_positions(self):
        last: Edge = self.parts[0]

        for edge in self.parts[1:]:
            offx: int = 0
            offy: int = 0
            idx: int = last.pos_x
            idy: int = last.pos_y

            if last.direction == Orientation.Up or last.direction == Orientation.Down:
                offx, offy = orientation_dist_val(edge.direction)
                idx += offx

            if edge.direction == Orientation.Down:
                offx, offy = orientation_dist_val(edge.direction)
                idx += offx
                idy += offy
                offx, offy = orientation_dist_val(last.direction)
                idx += offx
                idy += offy
            elif last.direction != Orientation.Down:
                offx, offy = orientation_dist_val(last.direction)
                idx += offx
                idy += offy

            edge.pos_x = idx
            edge.pos_y = idy

            last = edge

    # FIXME, not effective, not correct
    def set_size(self) -> None:
        max_x = max(self.parts, key=lambda item: item.pos_x)
        min_x = min(self.parts, key=lambda item: item.pos_x)
        max_y = max(self.parts, key=lambda item: item.pos_y)
        min_y = min(self.parts, key=lambda item: item.pos_y)

        self.size = (2 * (max_x.pos_x - min_x.pos_x + 1), 2 * (max_y.pos_y - min_y.pos_y + 1))
        self.extremes = Extremes(max_x.pos_x, min_x.pos_x, max_y.pos_y, min_y.pos_y)
        # self.size = (2 ** self.fold_count, 2 ** self.fold_count)

    def draw_dragon(self) -> List[str]:
        w, h = self.size

        offy = (-1) * self.extremes.min_y if self.extremes.min_y < 0 else 0
        offx = (-1) * self.extremes.min_x if self.extremes.min_x < 0 else 0

        ls: List[str] = [" " * w for _ in range(h)]

        # print('offset: ', offx, offy)
        #count: int = 0
        for edge in self.parts:
            # print('edge pos: ', edge.direction, '\t', edge.pos_x, edge.pos_y)
            tmp: List[str] = list(ls[h - edge.pos_y - offy - 1])
            tmp[edge.pos_x + offx] = orientation_char(edge.direction) # if count else 'S'
            ls[h - edge.pos_y + - offy - 1] = "".join(tmp)
            # count += 1

        ls = [ strip_end_of_line(line) for line in ls ]
        ls[-(self.extremes.max_y - self.extremes.min_y + offy + 1):]
        ls = [ line for line in ls if (line.find('_') != -1 or line.find('|') != -1)]

        return ls


def strip_end_of_line(line: str) -> str:
    underscore_idx = line.rfind('_')
    pipe_idx = line.rfind('|')

    idx: int = len(line) - 1
    if underscore_idx != -1:
        idx = max(underscore_idx, pipe_idx) if pipe_idx != -1 else underscore_idx
    elif pipe_idx != -1:
        idx = max(underscore_idx, pipe_idx) if underscore_idx != -1 else pipe_idx

    return line[:(idx + 1)]


def another_fold(dragon: Dragon, n: int) -> Dragon:
    if dragon.fold_count > n:
        return dragon

    dragon.fold()

    return another_fold(dragon, n)


def paper_folding(fold_count: int) -> Dragon:
    dragon: Dragon = Dragon(1, [ Edge(Orientation.Right, 0, 0) ], (0, 0), Extremes(0, 0, 0, 0))
    return another_fold(dragon, fold_count)


def solve() -> None:
    i: int = 1
    inputs : List[int] = []
    while (i):
        i = int(input())
        if i and i <= 13:
            inputs.append(i)
    
    # i = 1
    # while (i < 6):
    for num in inputs:
        dr = paper_folding(num)
        # _ = [ print(edge.direction.name + ', ') for edge in dr.parts ]
        # print([orientation_char(edge.direction) for edge in dr.parts ])
        _ = [ print(x) for x in dr.draw_dragon() ]
        # print('ˆ')
        print('^')
        # i += 1


if __name__ == "__main__":
    solve()

# 0
#
#  _
#
#
# 1
#
#  _|
#
#
# 2
#
# |_
#  _|
#
#
# 3
# 
#    _
#  _| |
# |_
#  _|
#
# 4
#    _   _
#   |_|_| |_
#    _|    x|
# |_|     |_
#          _|
#
