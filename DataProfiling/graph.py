import pathlib
import pprint

import matplotlib.pyplot as plt
import yaml

__COMMAND_TRANSLATION = {
    "-R": "1R:0W",
    "-W2": "2R:1W",
    "-W3": "3R:1W",
    "-W5": "1R:1W",
    "-W6": "0R:1W (non-temporal)",
    "-W7": "2R:1W (non-temporal)",
    "-W8": "1R:1W (non-temporal)",
    "-W9": "3R:1W (non-temporal)",
    "-W10": "2R:1W (non-temporal)",
    "-W11": "3R:1W",
    "-W12": "4R:1W",
    "default": "SSE2",
    "AVX2": "AVX2",
    "random": "rand",
    "sequential": "seq",
}


POS = {
    "SSE2_64B": (0, 0),
    "SSE2_128B": (0, 1),
    "SSE2_256B": (0, 2),
    "SSE2_512B": (0, 3),
    "AVX2_64B": (1, 0),
    "AVX2_128B": (1, 1),
    "AVX2_256B": (1, 2),
    "AVX2_512B": (1, 3),
}

LABELS = [
    "1R:0W",
    "2R:1W",
    "3R:1W",
    "1R:1W",
    "0R:1W (non-temporal)",
    "2R:1W (non-temporal)",
    "1R:1W (non-temporal)",
    "3R:1W (non-temporal)",
    "2R:1W (non-temporal)",
    "3R:1W",
    "4R:1W",
]
if __name__ == "__main__":
    plt.rcParams["figure.figsize"] = 9.5, 7

    pp = pprint.PrettyPrinter().pprint

    with (pathlib.Path().cwd() / "data.yaml").open("r") as file:
        data = yaml.safe_load(file)

    for k, v in data.items():
        fig = plt.figure()
        fig.set_tight_layout(True)

        gs = fig.add_gridspec(4, 2, hspace=0, wspace=0)
        axs = gs.subplots(sharex="col", sharey="row")
        plt.xlabel("Bandwidth (MB/s)")
        plt.ylabel("Latency (ns)")
        fig.suptitle(f"Latency/Throughput Comparison For Memory ({k} access)")

        lines = []
        for ke, va in v.items():
            for key, val in va.items():
                col, row = POS[
                    "_".join(
                        (
                            __COMMAND_TRANSLATION[ke],
                            key.lstrip("-l") + "B",
                        )
                    )
                ]
                for keys, vals in val.items():
                    label = " ".join(
                        (
                            __COMMAND_TRANSLATION[k],
                            __COMMAND_TRANSLATION[ke],
                            key.lstrip("-l") + "B",
                            __COMMAND_TRANSLATION[keys],
                        )
                    )
                    x = [float(bandwidth[2]) for bandwidth in vals]
                    y = [float(latency[1]) for latency in vals]
                    lines.append(axs[row][col].plot(x, y, linewidth=1, label=label)[0])
                plt.gca().set_prop_cycle(None)
                axs[row][col].grid(True)
                axs[row][col].set_title(
                    f'{__COMMAND_TRANSLATION[ke]} {key.lstrip("-l")}B', x=0.115, y=0.8
                )
        fig.legend(
            labels=LABELS,
            loc="upper right",
            borderaxespad=0.1,
        )
        plt.savefig(f"{k}.png")
        plt.show()
        plt.figure().clear()
        plt.close()
        plt.cla()
        plt.clf()
