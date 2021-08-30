from math import inf
from collections import defaultdict

from sys import stdin
input = stdin.readline

class Node:
    def __init__ (self):
        self.opt_w  = inf
        self.viewed = False
        self.joints = set()

    def addJoint (self, node, weight):
        self.joints.add(NodeJ(node, weight))

class NodeJ:
    def __init__ (self, node, weight):
        self.node   = node
        self.weight = weight

class Graph:
    def __init__ (self, count):
        self.vertCount  = count
        self.jointsList = defaultdict(Node)

    def addEdge (self, start, end, w):
        self.jointsList[start].addJoint(end, w)
        self.jointsList[end].addJoint(start, w)


def dijkstra (g, start):
    g.jointsList[start].opt_w = 0
    neigb = []
    curr = start
    sn = []
    for join in g.jointsList[curr].joints:
        if not g.jointsList[join.node].viewed:
            sn.append(join)
    sn = sorted(sn, key=lambda i: i.weight)
    for i in sn:
        neigb.append(i)
        if g.jointsList[i.node].opt_w > i.weight + g.jointsList[curr].opt_w:
            g.jointsList[i.node].opt_w = i.weight + g.jointsList[curr].opt_w
    g.jointsList[curr].viewed = True
    while len(neigb) > 0:
        curr = neigb.pop(0).node
        sn = []
        for join in g.jointsList[curr].joints:
            if not g.jointsList[join.node].viewed:
                sn.append(join)
        sn = sorted(sn, key=lambda i: i.weight)
        for i in sn:
            neigb.append(i)
            if g.jointsList[i.node].opt_w > i.weight + g.jointsList[curr].opt_w:
                g.jointsList[i.node].opt_w = i.weight + g.jointsList[curr].opt_w
        g.jointsList[curr].viewed = True
    for i in g.jointsList:
        print("{:d} <-> {:d} :: opt weight {:d}".format(start, i, g.jointsList[i].opt_w))

    for i in g.jointsList:
        opt_way = []
        j = i
        if g.jointsList[i].opt_w == 0:
            print("{:d} <-> {:d} :: opt way".format(start,start))
            print([start, start])
            print("")
        else:
            while j != start:
                for join in g.jointsList[j].joints:
                    if join.weight == g.jointsList[j].opt_w - g.jointsList[join.node].opt_w:
                        opt_way.append(join.node)
                        j = join.node
                        break
            opt_way.insert(0,i)
            print("{:d} <-> {:d} :: opt way".format(start,i))
            print(list(reversed(opt_way)))
            print("")







f = open ("I", 'r')
n = int (f.readline ())
g = Graph (n)
for i in range (n):
    a, b, w = map (int, f.readline ().split ())
    g.addEdge (a, b, w)
f.close ()

dijkstra (g, 4)


