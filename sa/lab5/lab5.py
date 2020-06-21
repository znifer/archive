from itertools import *
import numpy as np
import matplotlib.pyplot as plt
import math
import scipy 
import scipy.optimize as opt
import scipy.integrate as integrate

def r0(x1,x2):
  return 0
def r1(x1,x2):
  return 1
def rx1(x1,x2):
  return x1
def rx2(x1,x2):
  return x2
def rx1_2(x1,x2):
  return x1*x1
def rx2_2(x1,x2):
  return x2*x2
def rx2x1(x1,x2):
  return x2*x1
def rx1_2x2(x1, x2):
  return x1 ** 2 * x2
def rx1x2_2(x1, x2):
  return x1 * x2 ** 2
arm=[rx1,rx2,rx2_2,rx2x1]

def Get_F(i:int,RRR):#возвр.матр. F
  count_r=len(RRR[i])
  F=np.zeros((n1,count_r  ))#M: 12 x кол-во регрессоров
  for it in range(n1):
    for j in range(count_r):
      F[it][j]=RRR[i][j](X1[it][0],X2[it][0])
  return F

def Get_res_s(it:int,A):
  xx0=[]
  xx1=[]
  xx2=[]
  yy0=[]
  yynew=[]
  for i in range(n1):
    xx0.append(i)
    xx1.append(X1[i][0])
    xx2.append(X2[i][0])
    yy0.append(Y0[i][0])
    tmp=0.0
    for j in range(len(A)):
      tmp+=A[j][0]*RRR[it][j](X1[i][0],X2[i][0])  #Y^=Fa^
    yynew.append(tmp) #y^=sum<i=1, k>(a^_i*f_i(x))
  return xx0,xx1,xx2,yy0,yynew

def Get_Grafic(xx0,yy0,yynew):
  fig, ax = plt.subplots()
  ax.scatter(xx0, yy0)
  ax.plot(xx0, yy0, 'r', lw=2, label="Theoretical")
  ax.plot(xx0, yynew, 'b', lw=2, label="Fit")
  ax.legend()
  ax.set_xlim(0, 13)
  ax.set_xlabel(r"$x$", fontsize=18)
  ax.set_ylabel(r"$y$", fontsize=18)
  plt.show()
  return

n1=12
n2=10
##вектор x1,x2,y
X1=np.array([
   [13.0],
   [3.0],
   [12.0],
   [2.0],
   [12.0],
   [11.0],
   [5.0],
   [17.0],
   [4.0],
   [11.0],
   [9.0],
   [4.0],
   [1.0]
])

X2=np.array([
   [11.0],
   [7.0],
   [18.0],
   [11.0],
   [3.0],
   [6.0],
   [7.0],
   [12.0],
   [8.0],
   [2.0],
   [17.0],
   [14.0],
   [12.0]
])

Y0=np.array([
   [337.2582443],
   [63.3701193],
   [515.5767566],
   [132.0114992],
   [198.5223412],
   [202.0669770],
   [95.8270967],
   [503.0365417],
   [96.0823941],
   [183.3386634],
   [410.8476550],
   [231.4226067],
])

Y=np.array([
   146.1908194,#142.4072056,
   149.6165511,#145.5690592,
   148.0149887,#144.0908624,
   150.5093942,#146.3931282,
   152.3339211,#148.0771151,
   152.8967778,#148.5966160,
   146.3115603,#142.5186460,
   146.3516791,#142.5556745,
   153.6590343,#149.3001572,
   151.1223078#146.9588302
])

def Get_Qo(yy0,yynew):
  Qo=0.0 #Q остаток
  for i in range(n1):
    Qo+=(yy0[i]-yynew[i])**2
  return Qo

def Get_RRR():
  tf=[]
  for i in range(2, len(arm)):
    j = combinations(arm, i)  
    tf+=list(j)
  return tf

global r_min
r_min=999999.9
global r_num
r_num=0
RRR=Get_RRR()
print(RRR)
for iterat in range(len(RRR)):
  F=Get_F(iterat,RRR)
  A=(np.linalg.inv(((F.transpose()).dot(F))).dot(F.transpose())).dot(Y0)
  xx0,xx1,xx2,yy0,yynew=Get_res_s(iterat,A)
  Qoo=Get_Qo(yy0,yynew)
  print('i =', iterat,'Q_ост =', Qoo)
  if(r_min>Qoo):
    r_min=Qoo
    r_num=iterat

F=Get_F(r_num,RRR)
print('F =\n',F)
A=(np.linalg.inv(((F.transpose()).dot(F))).dot(F.transpose())).dot(Y0)  #a^
print('A =\n',A)
xx0,xx1,xx2,yy0,yynew=Get_res_s(r_num,A)

print('i =', r_num, 'Q_ост =', r_min, 'func =', RRR[r_num])   #STR_RRR
Get_Grafic(xx0,yy0,yynew)

############################################################################

my_t=np.mean(yy0)#MY теор
print('мат. ожидание теор. =',my_t)
Q=0.0  #Q теор
Qr=0.0 #Q реал
Qo=0.0 #Q остаток

for i in range(n1):
  Q += (yy0[i]-my_t)**2
  Qr += (yynew[i]-my_t)**2
  Qo += (yy0[i]-yynew[i])**2

R_2=Qr/Q
R_22=1.0-Qo/Q

print('Q_ост =', Qo,'Q_реал =', Qr,'Q_теор=', Q)
print('R^2 =',R_2,'=',R_22)
K = len(A)  #кол-во регрессоров
Sr_2 = Qr/(K-1)
So_2 = Qo/(n1-K)
FF = Sr_2/So_2
print('F =', FF)
print('K =', K, '; N - K =', n1 - K, '; F_t({}, {}, {}) = 4,26'.format(0.05, K-1, n1-K))

y_13_22=np.average(Y)
q_e_2=0.0 #(σ^)^2_e
l=len(Y)
for i in range(l):
  q_e_2+=((Y[i]-y_13_22)**2)/(l-1)
q_e_2=np.sqrt(q_e_2)

#print(F)
#print(q_e_2)
C = np.abs(np.linalg.inv(np.dot(F.transpose(),F)))
print(C)
q_a = np.zeros(len(C))
for i  in range(len(q_a)):
  q_a[i] = np.sqrt(C[i][i])*q_e_2
print('σ^_a:\n', q_a)
q_a = q_a**2

T = np.zeros(len(q_a))
sk = np.abs(np.sqrt(A[0][0]*A[0][0]+A[1][0]*A[1][0]+A[2][0]*A[2][0]))
for i in range(len(q_a)):
  T[i] = sk/q_a[i]
print('T =', T)
q_a = np.sqrt(q_a)
t_r = 2.2621
for i in range(len(q_a)):
  print("Довер.интервалы  t[{}];".format(i+1), "   ", A[i][0]-t_r*q_a[i], " <= ", A[i][0], " <= ", A[i][0]+t_r*q_a[i])
print(q_e_2)