import os
from subprocess import check_output
from functools import partial
import pytest
# import rich


DIR_PATH = os.path.dirname(os.path.realpath(__file__))
FILES_DIR = 'ps_files'
LOGS_DIR = 'logs_dir'
BINARY_DIR = 'binary'
COMPILATION_ERROR = b'Fatal: Compilation aborted\n'
SUFFIX = '.pas'


def get_list_of_files() -> list[str]:
    output: list[str] = []
    for root, dirs, files in os.walk(DIR_PATH):
        if root == f'{DIR_PATH}/{FILES_DIR}':
            output = [ file for file in files ]
    return output


def solve() -> tuple[list[str], list[str]]:
    programs: list[str] = get_list_of_files()
    binaries: list[str] = []

    # os.system('pwd')
    os.chdir(f'{FILES_DIR}')
    os.mkdir(BINARY_DIR)

    counter: int = 0
    for i, program in enumerate(programs):
        os.system(f'fpc -Fe{LOGS_DIR}/xxx{i} -FE{BINARY_DIR} {program} > /dev/null')
        # if os.path.exists(f"./{program}"):
        if check_output(['tail', '-n1', f'{LOGS_DIR}/xxx{i}']) != COMPILATION_ERROR:
            counter = counter + 1
            binary = f"{program.removesuffix(SUFFIX)}"

            os.system(f"./{BINARY_DIR}/{binary}")
            print()

            binaries.append(binary)

    os.system(f"rm -rf {BINARY_DIR}")
    os.chdir("../")
    # os.rmdir(BINARY_DIR)

    # test_fn = partial(test_compile, counter, programs)

    print(f"Compiled {counter} from {len(programs)} programs.")

    return (binaries, programs)

if __name__ == '__main__':
    main()
