import matplotlib.pyplot as plt

raw = """serial 1 1000000 0.425046
serial 1 2000000 0.932494
serial 1 3000000 1.16651
serial 1 4000000 1.82187
serial 1 5000000 2.18235
serial 1 6000000 2.55926
serial 1 7000000 3.44031
serial 1 8000000 3.79454
atomic 2 1000000 0.206293
atomic 2 2000000 0.465287
atomic 2 3000000 0.762891
atomic 2 4000000 1.04759
atomic 2 5000000 1.31913
atomic 2 6000000 1.76998
atomic 2 7000000 2.10872
atomic 2 8000000 2.37279
atomic 3 1000000 0.19194
atomic 3 2000000 0.43755
atomic 3 3000000 0.675156
atomic 3 4000000 1.01188
atomic 3 5000000 1.28301
atomic 3 6000000 1.52179
atomic 3 7000000 1.82351
atomic 3 8000000 2.3209
atomic 4 1000000 0.181836
atomic 4 2000000 0.412643
atomic 4 3000000 0.655296
atomic 4 4000000 0.886976
atomic 4 5000000 1.28343
atomic 4 6000000 1.5579
atomic 4 7000000 1.79399
atomic 4 8000000 2.09846
atomic 5 1000000 0.183194
atomic 5 2000000 0.413394
atomic 5 3000000 0.687277
atomic 5 4000000 0.925852
atomic 5 5000000 1.13921
atomic 5 6000000 1.62772
atomic 5 7000000 1.84734
atomic 5 8000000 2.35476
atomic 6 1000000 0.233026
atomic 6 2000000 0.445524
atomic 6 3000000 0.731561
atomic 6 4000000 0.97428
atomic 6 5000000 1.3121
atomic 6 6000000 1.91023
atomic 6 7000000 2.20422
atomic 6 8000000 2.39438
atomic 7 1000000 0.204028
atomic 7 2000000 0.440441
atomic 7 3000000 0.748516
atomic 7 4000000 1.10561
atomic 7 5000000 1.52409
atomic 7 6000000 1.63387
atomic 7 7000000 1.93104
atomic 7 8000000 2.28377
parallelMutex 2 1000000 0.226876
parallelMutex 2 2000000 0.556779
parallelMutex 2 3000000 0.920939
parallelMutex 2 4000000 1.20983
parallelMutex 2 5000000 1.58576
parallelMutex 2 6000000 2.05404
parallelMutex 2 7000000 2.43277
parallelMutex 2 8000000 2.75041
parallelMutex 3 1000000 0.270733
parallelMutex 3 2000000 0.616448
parallelMutex 3 3000000 0.893621
parallelMutex 3 4000000 1.35726
parallelMutex 3 5000000 1.76496
parallelMutex 3 6000000 2.16312
parallelMutex 3 7000000 2.36675
parallelMutex 3 8000000 3.00894
parallelMutex 4 1000000 0.266501
parallelMutex 4 2000000 0.637704
parallelMutex 4 3000000 0.998396
parallelMutex 4 4000000 1.32429
parallelMutex 4 5000000 1.79573
parallelMutex 4 6000000 2.17131
parallelMutex 4 7000000 2.48623
parallelMutex 4 8000000 2.87968
parallelMutex 5 1000000 0.29038
parallelMutex 5 2000000 0.651229
parallelMutex 5 3000000 1.0322
parallelMutex 5 4000000 1.37581
parallelMutex 5 5000000 1.76977
parallelMutex 5 6000000 2.29539
parallelMutex 5 7000000 2.72478
parallelMutex 5 8000000 3.21712
parallelMutex 6 1000000 0.314174
parallelMutex 6 2000000 0.73882
parallelMutex 6 3000000 1.07781
parallelMutex 6 4000000 1.54191
parallelMutex 6 5000000 1.99495
parallelMutex 6 6000000 2.28253
parallelMutex 6 7000000 2.87715
parallelMutex 6 8000000 3.2995
parallelMutex 7 1000000 0.333556
parallelMutex 7 2000000 0.748486
parallelMutex 7 3000000 1.10586
parallelMutex 7 4000000 1.65124
parallelMutex 7 5000000 2.08012
parallelMutex 7 6000000 2.71604
parallelMutex 7 7000000 3.07527
parallelMutex 7 8000000 3.58774
sharedVariables 2 1000000 0.192285
sharedVariables 2 2000000 0.48296
sharedVariables 2 3000000 0.919668
sharedVariables 2 4000000 1.12756
sharedVariables 2 5000000 1.39264
sharedVariables 2 6000000 1.86386
sharedVariables 2 7000000 2.02302
sharedVariables 2 8000000 2.48998
sharedVariables 3 1000000 0.196087
sharedVariables 3 2000000 0.442112
sharedVariables 3 3000000 0.692242
sharedVariables 3 4000000 1.05459
sharedVariables 3 5000000 1.22082
sharedVariables 3 6000000 1.57914
sharedVariables 3 7000000 1.80681
sharedVariables 3 8000000 2.36608
sharedVariables 4 1000000 0.186436
sharedVariables 4 2000000 0.399894
sharedVariables 4 3000000 0.705385
sharedVariables 4 4000000 0.909618
sharedVariables 4 5000000 1.20982
sharedVariables 4 6000000 1.51876
sharedVariables 4 7000000 2.08671
sharedVariables 4 8000000 2.05214
sharedVariables 5 1000000 0.154339
sharedVariables 5 2000000 0.45747
sharedVariables 5 3000000 0.672829
sharedVariables 5 4000000 0.896639
sharedVariables 5 5000000 1.18702
sharedVariables 5 6000000 1.45719
sharedVariables 5 7000000 1.80956
sharedVariables 5 8000000 2.24953
sharedVariables 6 1000000 0.185871
sharedVariables 6 2000000 0.461108
sharedVariables 6 3000000 0.667111
sharedVariables 6 4000000 1.00062
sharedVariables 6 5000000 1.25537
sharedVariables 6 6000000 1.54605
sharedVariables 6 7000000 1.95052
sharedVariables 6 8000000 2.35643
sharedVariables 7 1000000 0.224214
sharedVariables 7 2000000 0.432939
sharedVariables 7 3000000 0.712681
sharedVariables 7 4000000 1.10946
sharedVariables 7 5000000 1.30381
sharedVariables 7 6000000 1.55659
sharedVariables 7 7000000 1.79942
sharedVariables 7 8000000 2.5276"""

rows = raw.split("\n")

parsed = []
legend = []
for row in rows:
    [name, threads, size, time] = row.split(" ")
    parsed.append({'name': name, 'threads': int(threads), 'size': int(size), 'time': float(time)})

threads = set([i['threads'] for i in parsed if i['name'] == 'serial' or i['name'] == 'sharedVariables'])


plotData = {}
for parallelType in ['serial', 'atomic', 'parallelMutex', 'sharedVariables']:
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

