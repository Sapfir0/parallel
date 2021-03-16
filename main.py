import matplotlib.pyplot as plt

raw = """serial 1 100000 0.0181084
atomic 2 100000 0.0286803
atomic 3 100000 0.0149497
atomic 4 100000 0.0177285
atomic 5 100000 0.0179318
atomic 6 100000 0.0161278
atomic 7 100000 0.018824
parallelMutex 2 100000 0.0165309
parallelMutex 3 100000 0.0199195
parallelMutex 4 100000 0.0250316
parallelMutex 5 100000 0.0320693
parallelMutex 6 100000 0.0318917
parallelMutex 7 100000 0.0352808
sharedVariables 2 100000 0.0122813
sharedVariables 3 100000 0.0128984
sharedVariables 4 100000 0.0138137
sharedVariables 5 100000 0.0183395
sharedVariables 6 100000 0.0190186
sharedVariables 7 100000 0.0174331
serial 1 1000000 0.394883
atomic 2 1000000 0.255585
atomic 3 1000000 0.202101
atomic 4 1000000 0.196983
atomic 5 1000000 0.262815
atomic 6 1000000 0.245374
atomic 7 1000000 0.196857
parallelMutex 2 1000000 0.253629
parallelMutex 3 1000000 0.291546
parallelMutex 4 1000000 0.307338
parallelMutex 5 1000000 0.330139
parallelMutex 6 1000000 0.373339
parallelMutex 7 1000000 0.374449
sharedVariables 2 1000000 0.194899
sharedVariables 3 1000000 0.18292
sharedVariables 4 1000000 0.149915
sharedVariables 5 1000000 0.165216
sharedVariables 6 1000000 0.175834
sharedVariables 7 1000000 0.202868
serial 1 10000000 4.64155
atomic 2 10000000 3.0792
atomic 3 10000000 2.85799
atomic 4 10000000 4.33126
atomic 5 10000000 4.71289
atomic 6 10000000 3.13432
atomic 7 10000000 2.97651
parallelMutex 2 10000000 3.75005
parallelMutex 3 10000000 4.0485
parallelMutex 4 10000000 4.50492
parallelMutex 5 10000000 4.33122
parallelMutex 6 10000000 4.32856
parallelMutex 7 10000000 4.71381
sharedVariables 2 10000000 3.43019
sharedVariables 3 10000000 3.01991
sharedVariables 4 10000000 3.44454
sharedVariables 5 10000000 2.86772
sharedVariables 6 10000000 2.93454
sharedVariables 7 10000000 3.13343
"""

rows = raw.split("\n")

for row in rows:
    [name, threads, size, time] = row.split(" ")
    plt.plot(size, f"{name} {threads} {size}")


plt.xlabel('size')
plt.ylabel('time')

plt.legend(rows, loc=2)

plt.show()

# parallelMutex2 0.365488
# sharedVariables2 0.292728
# atomic2 0.234913
# parallelMutex3 0.28454
# sharedVariables3 0.222694
# atomic3 0.188915
# parallelMutex4 0.382962
# sharedVariables4 
# atomic4 0.177593
# parallelMutex5 
# sharedVariables5 0.284384
# atomic5 0.189578
# parallelMutex6 0.328889
# sharedVariables6 
# atomic6 
# parallelMutex7 0.344558
# sharedVariables7 
# atomic7 


