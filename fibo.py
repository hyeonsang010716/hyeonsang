import time
import random
def iterfibo(n):    #반복적으로 구현한 피보나치 함수
    fibo = [0, 1]

    if n == 1:

        return fibo[0]

    else:

        for i in range(0, n - 1):
            new_fibo = fibo[i] + fibo[i + 1]

            fibo.append(new_fibo)

        return fibo[n - 2] + fibo[n - 1]

def fibo(n):
    if n <= 1:
        return n
    return fibo(n - 1) + fibo(n - 2)


while True:
    nbr = int(input("Enter a number: "))
    if nbr == -1:
        break
    ts = time.time()
    fibonumber = iterfibo(nbr)
    ts = time.time() - ts
    print("IterFibo(%d)=%d, time %.6f" % (nbr, fibonumber, ts))
    ts = time.time()
    fibonumber = fibo(nbr)
    ts = time.time() - ts
    print("Fibo(%d)=%d, time %.6f" % (nbr, fibonumber, ts))