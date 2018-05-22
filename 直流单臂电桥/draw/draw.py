import matplotlib.pyplot as plt

dtR = []
dtI = []
R0 = []

nA = 0.1

with open("SE.txt","r") as f:
    raw = f.readlines()
    dtR = list(map(float,raw[0].split()))
    dtI = list(map(float,raw[1].split()))
    R0 = list(map(float,raw[2].split()))

l = len(dtR)
S = [dtI[i]/nA*R0[i]/dtR[i] for i in range(l)]
vol = [0.5*i for i in range(l)]

print(S)
plt.plot(vol,S)
plt.xlabel("voltage/V")
plt.ylabel("precious")
plt.show()

