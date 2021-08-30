
from collections import defaultdict

from sys import stdin
input = stdin.readline


class Graph:
    def __init__ (self, count):
        self.vertCount  = count
        self.jointsList = defaultdict (set)
        self.iterDFG = 0 

    def addEdge (self, start, end):
        self.jointsList[start].add (end) 
        self.jointsList[end].add (start)

# Реализуем рекурсивную функцию void go(int curr, int prev), 
#        где curr — текущая вершина,
#        prev — вершина, из которой мы попали в текущую. 
# При первом вызове curr = r, prev = –1.

# 1 Запишем в num[curr] номер вершины curr в порядке обхода в глубину.
# 2 Запишем в low[curr] значение num[curr].
# 3 Переберем в цикле все вершины, в которые есть ребро из curr. 
#   Для каждой такой вершины i выполним следующие действия:
#      A) Если вершина i еще не посещена, вызовем рекурсивно функцию go с параметрами i, curr. Если после этого значение L[i] стало меньше, чем L[curr], присвоим L[curr] = L[i].
#      B) Если вершина i уже была посещена и ее номер number[i] < number[curr], и при этом i не равно prev (т.е. ребро (i, prev) обратное и возвращается в вершину с меньшим номером), то если L[curr] > number[i], присвоим L[curr] = number[i].
# Для вывода компонент ребро нужно на шагах 
#      3a добавлять ребро в стек перед рекурсивным вызовом
#      3b выталкивать из стека в поток вывода все ребра вплоть до текущего (curr, i), 
#         если на шаге 3а выяснилось, что для текущей вершины curr выполняется условие теоремы.


def biconnect (graph, curr, prev, low, num, stack):
    childs    = 0
    num[curr] = graph.iterDFG
    low[curr] = graph.iterDFG
    graph.iterDFG += 1

    for i in graph.jointsList[curr]:
        if num[i] == -1 :
            prev[i] = curr
            childs += 1
            stack.append ( (curr, i) )
            biconnect (graph, i, prev, low, num, stack)
            
            if (low[i] < low[curr]):
                low[curr] = low[i]

            if prev[curr] == -1 and childs > 1 or prev[curr] != -1 and low[i] >= num[curr]:
                w = -1
                while w != (curr, i):
                    w = stack.pop ()
                    print (str (w[0]) + " <-> " + str (w[1]), end="  ")
                print ("")

        elif i != prev[curr] and low[curr] > num[i]:
            low[curr] = min (low [curr], num[i])
            stack.append ((curr, i))


f = open ("I", 'r')
n = int (f.readline ())
g = Graph (n)
for i in range (n):
    a, b = map (int, f.readline ().split ())
    g.addEdge (a, b)
f.close ()

num     = [-1] * g.vertCount
low     = [-1] * g.vertCount
parent  = [-1] * g.vertCount
stack   = []

biconnect (g, 1, parent, low, num, stack)
if stack:
    while stack:
        w = stack.pop ()
        print (str (w[-1]) + " <-> " + str (w[1]), end="  ")
    print ("")


