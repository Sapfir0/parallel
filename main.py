import matplotlib.pyplot as plt

parallelMutex = [ 0.28427, 0.289129, 0.323148,  0.355737, 0.332423, 0.347704]
atomic  = [0.243361, 0.216916, 0.171087, 0.191297, 0.192129, 0.20461]
shared  = [0.26066, 0.229732, 0.232619, 0.26152, 0.247485, 0.327568]
threads = [2,3,4,5, 6, 7]
plt.xlabel('threads')
plt.ylabel('time')
plt.plot(threads, parallelMutex, )
plt.plot(threads, atomic)
plt.plot(threads, shared)
plt.legend(["mutex", "atomic", "shared"], loc=2)

plt.show()

# parallelMutex2 0.365488
# shared variables2 0.292728
# atomic2 0.234913
# parallelMutex3 0.28454
# shared variables3 0.222694
# atomic3 0.188915
# parallelMutex4 0.382962
# shared variables4 
# atomic4 0.177593
# parallelMutex5 
# shared variables5 0.284384
# atomic5 0.189578
# parallelMutex6 0.328889
# shared variables6 
# atomic6 
# parallelMutex7 0.344558
# shared variables7 
# atomic7 


