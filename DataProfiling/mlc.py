import pathlib
import subprocess
import pprint
import yaml

if __name__ == '__main__':
    pp = pprint.PrettyPrinter().pprint
    exe = pathlib.Path().cwd() / 'mlc' / 'mlc.exe'
    data = {}

    try:
        for rand in (False, True):
            random = 'random' if rand else 'sequential'
            data[random] = {}
            print(f':: ACCESS {random} ::')
            for simd in (False, True):
                default = 'AVX2' if simd else 'default'
                print(f':: SIMD {default} ::')
                data[random][default] = {}
                for access in ('-l64', '-l128', '-l256', '-l512'):
                    print(f':: ACCESS {access} ::')
                    data[random][default][access] = {}

                    for ratio in ('-R', '-W2', '-W3', '-W5', '-W6', '-W7', '-W8', '-W9', '-W10', '-W11', '-W12'):
                        print(f':: RATIO {ratio} ::')
                        command = [exe, '--loaded_latency', access, ratio]

                        if simd:
                            command.append('-Y')

                        if rand:
                            command.append('-r')

                        try:
                            temp = subprocess.check_output(command).decode().split('\r\n')[10:-1]
                        except Exception:
                            print('Skipped')
                        else:
                            data[random][default][access][ratio] = []
                            
                            for line in temp:
                                data[random][default][access][ratio].append(tuple(line.split()))
    except Exception as e:
        print(e)
    finally:
        with (pathlib.Path().cwd() / 'data.yaml').open('w') as file:
            val = yaml.safe_dump(data, file)

