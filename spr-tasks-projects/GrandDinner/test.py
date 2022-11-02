import sys


def read() -> tuple[list[int], list[int]]:
    with open(sys.argv[2], 'r') as f1:
        l1 = [ [int(x) for x in line.split()] for line in f1.readlines()]
    with open(sys.argv[3], 'r') as f2:
        l2 = [ [int(x) for x in line.split()] for line in f2.readlines()]

    return l1, l2


def test() -> None:
    l1, l2 = read()
    assert(len(l1) == len(l2))
    for x, y in zip(l1, l2):
        assert(len(x) == len(y))


if __name__ == "__main__":
    test()
