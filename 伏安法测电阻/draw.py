import matplotlib.pyplot as plt

dtU = []
dtI = []

with open("R.txt","r") as f:
    raw = f.readlines()
    dtU = list(map(float,raw[0].split()))
    dtI = list(map(float,raw[1].split()))

dtDU = []
dtDI = []
with open("dp.txt","r") as f:
    raw = f.readlines()
    dtDU = list(map(float,raw[0].split()))
    dtDI = list(map(float,raw[1].split()))
with open("dn.txt","r") as f:
    raw = f.readlines()
    dtDU = dtDU + [i for i in reversed(list(map(float,raw[0].split())))]
    dtDI = dtDI + [-i for i in reversed(list(map(float,raw[1].split())))]

plt.subplot(211)
plt.plot(dtI,dtU)
plt.ylabel("voltage/V")
plt.xlabel("current/mA")

plt.subplot(212)
plt.plot(dtDI,dtDU)
plt.ylabel("voltage/V")
plt.xlabel("current/mA")
plt.show()

