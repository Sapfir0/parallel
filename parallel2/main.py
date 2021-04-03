import matplotlib.pyplot as plt

raw = """serial 1 10000 0.157359
serial 1 20000 0.195243
serial 1 30000 0.495341
serial 1 40000 1.30047
serial 1 50000 2.65186
Parallel 1 10000 0.0498486
Parallel 1 20000 0.178714
Parallel 1 30000 0.548146
Parallel 1 40000 1.15379
Parallel 1 50000 2.62982
Parallel 2 10000 0.0478002
Parallel 2 20000 0.1455
Parallel 2 30000 0.558057
Parallel 2 40000 1.06003
Parallel 2 50000 2.29392
Parallel 3 10000 0.0395178
Parallel 3 20000 0.123334
Parallel 3 30000 0.420402
Parallel 3 40000 0.816006
Parallel 3 50000 2.04806
Parallel 4 10000 0.0452679
Parallel 4 20000 0.13541
Parallel 4 30000 0.424034
Parallel 4 40000 0.990177
Parallel 4 50000 1.90939
Parallel 5 10000 0.0382401
Parallel 5 20000 0.124749
Parallel 5 30000 0.366749
Parallel 5 40000 0.974008
Parallel 5 50000 2.52385
Parallel 6 10000 0.0507158
Parallel 6 20000 0.148096
Parallel 6 30000 0.4504
Parallel 6 40000 1.25158
Parallel 6 50000 1.72993
Parallel 7 10000 0.0416484
Parallel 7 20000 0.13462
Parallel 7 30000 0.407898
Parallel 7 40000 0.779557
Parallel 7 50000 1.67472"""

rows = raw.split("\n")

parsed = []
legend = []
for row in rows:
    [name, threads, size, time] = row.split(" ")
    parsed.append({'name': name, 'threads': int(threads), 'size': int(size), 'time': float(time)})

threads = set([i['threads'] for i in parsed if i['name'] == 'serial' or i['name'] == 'Parallel'])


plotData = {}
for parallelType in ['serial', 'Parallel']:
    for thread in threads:
        timings = [i['time'] for i in parsed if i['name'] == parallelType and i['threads']== thread]
        sizes = [i['size'] for i in parsed if i['name'] == parallelType and i['threads']== thread]

        if len(sizes) != 0 and len(timings) != 0:
            plt.plot(sizes, timings)
            legend.append(f"{parallelType} {thread}")
        # plotData.update({parallelType: {'size': sizes, 'time': timings}})



plt.xlabel('size')
plt.ylabel('time')

plt.legend(legend, loc=2)

plt.show()

