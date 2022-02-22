import pathlib
import timeit

import pandas as pd

if __name__ == "__main__":
    cantrbry = [
        file
        for file in pathlib.Path(".").glob("cantrbry/*")
        if (file.is_file() and file.suffix not in {".dat", ".zst"})
    ]
    table = {
        "File": [],
        "Filetype": [],
        "Attempt": [],
        "nThreads": [],
        "Og.Size [KB]": [],
        "Comp.Size [KB]": [],
        "Ratio": [],
        "Time [s]": [],
        "Time Per KB [s/KB]": [],
    }
    for file in cantrbry:
        print(f"Compressing {str(file)}")
        for nThreads in range(2, 16):
            for attempt in range(20):
                command = f'subprocess.run(args=["./main.o", "{file}", "{file.with_suffix(".zst")}", "{nThreads}"], timeout=60)'
                runtime = timeit.timeit(
                    stmt=command, setup="import subprocess", number=1
                )
                table["File"].append(str(file))
                table["Filetype"].append(str(file.suffix))
                table["nThreads"].append(nThreads)
                table["Attempt"].append(attempt)
                table["Og.Size [KB]"].append(file.stat().st_size / 1024)
                table["Comp.Size [KB]"].append(
                    file.with_suffix(".zst").stat().st_size / 1024
                )
                table["Ratio"].append(
                    file.stat().st_size / file.with_suffix(".zst").stat().st_size
                )
                table["Time [s]"].append(runtime)
                table["Time Per KB [s/KB]"].append(1024 * runtime / file.stat().st_size)
    df = pd.DataFrame(data=table)
    df.to_csv(pathlib.Path().cwd() / "data.csv")
