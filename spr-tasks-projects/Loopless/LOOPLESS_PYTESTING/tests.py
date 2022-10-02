import pytest
from app import solve


def test_compile(): #(n_compiled: int, programs: list[str]):
    binaries, programs = solve() 
    assert len(binaries) == len(programs)

if __name__ == '__main__':
    test_compile()
