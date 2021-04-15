import matplotlib.pyplot as plt

raw = """1 10000000 0.845072
1 30000000 2.5077
1 50000000 4.32637
1 70000000 6.10753
1 10000000 0.786891
1 30000000 2.67596
1 50000000 4.35115
1 70000000 6.18766
2 10000000 0.410553
2 30000000 1.54318
2 50000000 2.37996
2 70000000 3.3128
3 10000000 0.303205
3 30000000 0.897741
3 50000000 1.67554
3 70000000 2.7644
4 10000000 0.294957
4 30000000 0.887076
4 50000000 1.5505
4 70000000 1.89344
5 10000000 0.280883
5 30000000 0.765033
5 50000000 1.23821
5 70000000 1.99448
6 10000000 0.318053
6 30000000 0.731593
6 50000000 1.11254
6 70000000 1.82497
7 10000000 0.283511
7 30000000 0.719137
7 50000000 1.29924
7 70000000 1.72501
8 10000000 0.264687
8 30000000 0.710121
8 50000000 1.32144
8 70000000 1.56829
9 10000000 0.264091
9 30000000 0.762196
9 50000000 1.19827
9 70000000 1.92771
10 10000000 0.299328
10 30000000 0.795858
10 50000000 1.27934
10 70000000 1.70343
11 10000000 0.312549
11 30000000 0.862603
11 50000000 1.24505
11 70000000 1.71365
12 10000000 0.30156
12 30000000 0.742429
12 50000000 1.45045
12 70000000 2.10691"""

rows = raw.split("\n")

parsed = []
legend = []
for row in rows:
    [name, threads, size, time] = row.split(" ")
    parsed.append({'name': name, 'threads': int(threads), 'size': int(size), 'time': float(time)})

threads = set([i['threads'] for i in parsed if i['name'] == '' or i['name'] == 'Parallel'])


plotData = {}
for parallelType in ['', 'Parallel']:
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

