import sys
from dataclasses import dataclass, field


@dataclass
class Input:
    def __post_init__(self) -> None:
        self.keys_teams = [i for i in range(len(self.teams))]
        self.keys_tables = [i for i in range(len(self.tables))]

    teams: list[int] = field(default_factory=list)
    tables: list[int] = field(default_factory=list)
    keys_teams: list[int] = field(default_factory=list)
    keys_tables: list[int] = field(default_factory=list)


@dataclass
class Solution:
    tables_sol: list[int] = field(default_factory=list)
    is_valid: bool = False


def load_input() -> Input:
    return Input(
        [ int(x) for x in sys.stdin.readline().split()],
        [ int(x) for x in sys.stdin.readline().split()]
    )


def process_input() -> list[Input]:
    inputs: list[Input] = []
    i, j = [int(x) for x in sys.stdin.readline().split() ]
    while (i or j):
        inputs.append(load_input())
        i, j = [int(x) for x in sys.stdin.readline().split() ]
    return inputs


def solve(putin: Input) -> Solution:
    is_valid: bool = False
    if not len(putin.teams):
        return Solution([], False)
    if not len(putin.tables):
        return Solution([], False)

    # sort associative list of key with input data
    putin.teams, putin.keys_teams = [
        list(x) for x in zip(
            *sorted(zip(putin.teams, putin.keys_teams),
                key=lambda p: p[0], reverse=True
            )
        )
    ]
    putin.tables, putin.keys_tables = [
        list(x) for x in zip(
            *sorted(zip(putin.tables, putin.keys_tables),
                key=lambda p: p[0], reverse=True
            )
        )
    ]

    # list of tables occupancy
    tables: list[list[int]] = [ [] for _ in putin.tables ]
    # associate to list(key_tables) with capacity
    keys_tables = [i for i in range(len(tables))]

    # print(f"teams: ", putin.teams, " teams count: ", len(putin.teams))
    # print(f"tables: ", putin.tables, " tables count: ", len(putin.tables))
    for idx, x in enumerate(putin.teams):
        for i in range(x):
            if i > len(tables) - 1:
                return Solution([], False)
        
            if len(tables[i]) >= putin.tables[keys_tables[i]]:
                return Solution([], False)

            tables[i].append(putin.keys_teams[idx])

        tables, keys_tables = [
            list(x) for x in zip(
                *sorted(zip(tables, keys_tables),
                    key=lambda p: putin.tables[p[1]] - len(p[0]), reverse=True
                )
            )
        ]

    tables = [ tables[putin.keys_tables.index(i)] for i in range(len(keys_tables)) ]
    teams = [ [i + 1 for i, t in enumerate(tables) if x in t] for x in putin.keys_teams ]
    teams = [ teams[putin.keys_teams.index(i)] for i in range(len(putin.keys_teams)) ]
    
    return Solution(teams, True)


def print_sol(sol: Solution) -> None:
    print(int(sol.is_valid))
    _ = [ print(' '.join(map(str, sorted(table)))) for table in sol.tables_sol ]


def main() -> None:
    _ = [ print_sol(solve(x)) for x in process_input() ]


if __name__ == '__main__':
    main()
