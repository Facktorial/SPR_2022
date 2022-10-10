import os
import sys
from subprocess import check_output
from functools import partial
from dataclasses import dataclass, field
import pytest


DIR_PATH = os.path.dirname(os.path.realpath(__file__))
FILES_DIR = '../ps_files'
LOGS_DIR = 'logs_dir'
BINARY_DIR = 'binary'
COMPILATION_ERROR = b'Fatal: Compilation aborted\n'
SUFFIX = '.pas'
TEST_SUFFIX = '.test'


@dataclass
class DataTest:
    test_result: str
    test_inputs: list[str] = field(default_factory=list)


def get_list_of_files() -> list[str]:
    output: list[str] = []
    for root, dirs, files in os.walk(f'{DIR_PATH}/{FILES_DIR}'):
        if root == f'{DIR_PATH}/{FILES_DIR}':
            output = [ file for file in files ]
    return output


def solve() -> tuple[list[str], list[str]]:
    programs: list[str] = [ x for x in get_list_of_files() if x.find(SUFFIX) != -1 ]
    binaries: list[str] = []

    # os.system('pwd')
    # os.chdir(f'{FILES_DIR}')
    os.system(f"rm -rf {BINARY_DIR}")
    os.mkdir(BINARY_DIR)

    counter: int = 0

    for i, program in enumerate(programs):
        os.system(f'fpc -Fe{LOGS_DIR}/xxx{i} -FE{BINARY_DIR} {FILES_DIR}/{program} > /dev/null')
        # if os.path.exists(f"./{program}"):
        if check_output(['tail', '-n1', f'{LOGS_DIR}/xxx{i}']) != COMPILATION_ERROR:
            counter = counter + 1
            binary = f"{program.removesuffix(SUFFIX)}"
            os.system(f"./{BINARY_DIR}/{binary}")
            print()

            binaries.append(binary)

    # os.system(f"rm -rf {BINARY_DIR}")
    # os.rmdir(BINARY_DIR)

    # test_fn = partial(test_compile, counter, programs)

    print(f"Compiled {counter} from {len(programs)} programs.")

    return (binaries, programs)


def programs_output(inputs: list[str]) -> list[str]:
    not_test_files: list[str] = [ filename for filename in get_list_of_files() if filename.find('testing_data') == -1 ]
    # output: list[str] = [ check_output([f'./{BINARY_DIR}/{filename.removesuffix(SUFFIX)}', f'< {inp}']) for (inp, filename) in zip(inputs, not_test_files) ]
    output: list[str] = []
    for (inp, filename) in zip(inputs, not_test_files):
        check_output([f'./{BINARY_DIR}/{filename.removesuffix(SUFFIX)}']) 
        sys.stdout.write("".join(inp))

    print(output)
    return output


def parse_sort_test() -> DataTest:#list[tuple[str, str]]:
    # output: list[tuple[str, str]] = []
    output: list[DataTest] = []
    test_files: list[str] = [ filename for filename in get_list_of_files() if filename.find('testing_data') != -1 ]

    test_data: list[tuple[list[int]]] = [([], [])] * len(test_files)
    for i, filename in enumerate(test_files):
        with open(f'{DIR_PATH}/{FILES_DIR}/' + filename, "r") as file:
            lines = file.readlines()
            # tmp_in = [[ int(x) for x in line.split(' ')[:-1] ] for line in lines[:-2] ]
            # tmp_out = [ int(x) for x in lines[-1].split(' ')[:-1] ]
            # test_data[i] = (tmp_in, tmp_out) 
            # output.append((','.join(map(str, tmp_in)), ','.join(map(str, tmp_out))))
            tmp_in = lines[:-2]
            tmp_out = lines[-1]
            output.append(DataTest(tmp_out, tmp_in))

    return output


   
if __name__ == '__main__':
    # main()
    parse_sort_test()
