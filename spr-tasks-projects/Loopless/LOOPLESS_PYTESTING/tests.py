import pytest
from app import solve, parse_sort_test, programs_output


def test_compile(): #(n_compiled: int, programs: list[str]):
     binaries, programs = solve() 
     assert len(binaries) == len(programs)

def test_results():
    data = parse_sort_test()
    inputs = [ x.test_inputs for x in data ]
    outputs = [ x.test_result for x in data ]
    # print("inputs:\n", inputs)
    computed_outputs = programs_output(inputs)
    print("outputs:\n", computed_outputs)

    for computed, given in zip(computed_outputs, outputs):
        print(computed, "   ", given)
        assert(computed == given)


if __name__ == '__main__':
    test_compile()
