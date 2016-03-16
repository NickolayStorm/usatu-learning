#! /usr/bin/python

def main():

    S = [(1, 2), (1, 3), (1, 4), (2, 3), (2, 5), (3, 5), (4, 6), (5, 6)]
    T = [3, 2, 3, 5, 3, 4, 1, 2]

    t = [0, 0, 0, 0, 0, 0, 0, 0]

    chars = ["A", "B", "C", "D", "E", "F", "G", "H"]

    #maximum
    iterCount = 0
    while(True):
        iterCount += 1
        print ("\niter count: {}".format(iterCount))
        prevT = t[:]
        ind = 0
        for i, j in S:
            tmp = max([t[j], t[i] + T[ind]])
            print("{}({}, {}): t[{}] = max({}, {} + {}) = {}".format(chars[ind], i, j, j, t[j], t[i], T[ind], tmp))
            t[j] = tmp
            ind += 1
        print("X = {}".format(t[1:]))
        flag = True
        for i, j in zip(t, prevT):
            if i != j:
                flag = False
                break
        if flag == True:
            break


    print("\n\n REVERSE")
    #minimum

    maxx = max(t)

    newT = []

    for i in range(0, len(t)):
        newT.append(maxx)

    t = newT


    iterCount = 0
    while(True):
        iterCount += 1
        print ("\niter count: {}".format(iterCount))
        prevT = t[:]
        ind = 0
        for i, j in S:
            tmp = min([t[i], t[j] - T[ind]])
            print("{}({}, {}): t[{}] = min({}, {} - {}) = {}".format(chars[ind], i, j, i, t[i], t[j], T[ind], tmp))
            t[i] = tmp
            ind += 1
        print("X = {}".format(t[1:]))
        flag = True
        for i, j in zip(t, prevT):
            if i != j:
                flag = False
                break
        if flag == True:
            break

if __name__ == '__main__':
    main()
