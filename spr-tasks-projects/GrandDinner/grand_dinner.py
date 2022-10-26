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


def read_all_numbers() -> list[list[int]]:
    return map(lambda x: map(int, x.split()), sys.stdin.readlines())


def read_num():
    return list(map(int, sys.stdin.readline().split()))


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

    # if len(putin.tables) - 1 > putin.teams[0]:
    #    return Solution([], is_valid)
    # print("prunned yet")
    # print(f"teams: ", putin.teams)
    # print(f"tables: ", putin.tables)

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

    tables: list[list[int]] = [ [] for _ in putin.tables ]
    keys_tables = [i for i in range(len(tables))]

    # print(f"teams: ", putin.teams, " teams count: ", len(putin.teams))
    # print(f"tables: ", putin.tables, " tables count: ", len(putin.tables))
    for idx, x in enumerate(putin.teams):
        # print("----------------------------")
        # print(f"BEFORE TABLES({idx}, {x}): ", tables)
        # print(f"get prunned, {idx=}, {len(putin.keys_tables)=}, {putin.keys_tables}")
        # if idx > len(putin.keys_tables):
            # return Solution([], False)

        for i in range(x):
            if i > len(tables) - 1:
                # print("exit_0")
                return Solution([], False)
        
            # for p1, p2 in zip(tables, keys_tables):
                # print(p2, "...", p1, "----> ", putin.tables[p2] - len(p1))

            # # print("......")
            # # print(f"MIDDLE TABLES({idx}, {x}): ", tables)
            # print(f"KEY tables: ", keys_tables)
            # # print(f"putin teams: ", putin.teams)
            # # print(f"putin tables: ", putin.tables)
            # # print(f"putin KEY teams: ", putin.keys_teams)
            # print(f"putin KEY tables: ", putin.keys_tables)
            # # print(f"tables: ", tables)
            # print(f"{i=}, {idx=}")
            # print(tables[i])
            # print(tables[keys_tables[i]])
            # print(putin.keys_tables[keys_tables[i]])
            # print(putin.tables[putin.keys_tables[keys_tables[i]]])
            # print(f"{len(tables[i])=}")
            # print(keys_tables)
            # # print(putin.keys_teams[idx])
            # print(putin.tables[i])
        
            # print(f"teams: ", putin.teams, " teams count: ", len(putin.teams))
            # print(f"tables: ", putin.tables, " tables count: ", len(putin.tables))

            # if len(tables[i]) >= putin.tables[i]:
            if len(tables[i]) >= putin.tables[keys_tables[i]]:
            # if len(tables[i]) >= putin.tables[keys_tables[idx]] - 1:
                # print("exit_1")
                return Solution([], False)

            tables[i].append(putin.keys_teams[idx])
            # print(f"MIDDLE_TABLES({idx}, {x}): ", tables)

        tables, keys_tables = [
            list(x) for x in zip(
                *sorted(zip(tables, keys_tables),
                    key=lambda p: putin.tables[p[1]] - len(p[0]), reverse=True
                )
            )
        ]
        # print(f"AFTER  TABLES({idx}, {x}): ", tables)

    tables = [ tables[putin.keys_tables.index(i)] for i in range(len(keys_tables)) ]
    teams = [ [i + 1 for i, t in enumerate(tables) if x in t] for x in putin.keys_teams ]
    # print(teams)
    teams = [ teams[putin.keys_teams.index(i)] for i in range(len(putin.keys_teams)) ]
    # print(teams)
    # print("tables ", tables)
    # print("tables ", keys_tables)
    # print(putin.tables)
    # print(putin.keys_tables)
    # print(putin.teams)
    # print(putin.keys_teams)
    
    return Solution(teams, True)


def print_sol(sol: Solution) -> None:
    print(int(sol.is_valid))
    _ = [ print(' '.join(map(str, sorted(table)))) for table in sol.tables_sol ]


def main() -> None:
    # _ = [ [print(xx) for xx in x] for x in read_all_numbers() ]
    # inputs: list[Input] = process_input()
    # for i in inputs:
    #     print("teams: ", i.teams)
    #     print("tables: ", i.tables)
    _ = [ print_sol(solve(x)) for x in process_input() ]


if __name__ == '__main__':
    main()
