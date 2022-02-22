import pandas as pd
import pathlib

if __name__ == '__main__':
    df = pd.read_csv(pathlib.Path().cwd() / 'data.csv')

    nThreads = df.groupby(by='nThreads').mean()
    bar = nThreads.plot.bar(y='Time Per KB [s/KB]', rot=0);
    bar.figure.savefig('thread_perf.png')

    ratio = df.groupby(by='Filetype').mean()
    bar = ratio.plot.bar(y='Ratio', rot=0);
    bar.figure.savefig('type_ratio.png')

    ratio = df.groupby(by='Filetype').mean()
    bar = ratio.plot.bar(y='Time Per KB [s/KB]', rot=0);
    bar.figure.savefig('type_perf.png')