from numpy import double
from scipy.misc import face


lt = ""




paths = [
    ["./title.stl",[250,150,80],[-5,-10,1]],
    ["./human.stl",[220,200,200],[-4,-10,0.5]],
]
deps = 1000

lt += "scene['title'] = "

lt += "["
for path in paths:
    with open(path[0]) as f:
        data = f.readlines()
    color = "["+str(path[1][0])+","+str(path[1][1])+","+str(path[1][2])+"],"
    fctl = []
    lfctl = []
    c = 0
    for l in data:
        if (l.startswith("vertex")):
            c+=1
            ld = l.replace("\n","").split(" ")
            lfctl.append(str(int(double(ld[1])*deps+path[2][0])/deps))
            lfctl.append(str(int(double(ld[2])*deps+path[2][1])/deps))
            lfctl.append(str(int(double(ld[3])*deps+path[2][2])/deps))
            if (c%3==0):
                fctl.append(lfctl)
                # print(lfctl)
                lfctl = []
    for i in range(len(fctl)):
        lt += "[ ["+fctl[i][0]+","+fctl[i][1]+","+fctl[i][2]+"],["+fctl[i][3]+","+fctl[i][4]+","+fctl[i][5]+"],["+fctl[i][6]+","+fctl[i][7]+","+fctl[i][8]+"],"
        lt += color
        lt += '],'
lt += "];\n"


paths = [
    ["./goal.stl",[250,150,80],[10,-1,1]],
]

lt += "scene['goal'] = "

lt += "["
for path in paths:
    with open(path[0]) as f:
        data = f.readlines()
    color = "["+str(path[1][0])+","+str(path[1][1])+","+str(path[1][2])+"],"
    fctl = []
    lfctl = []
    c = 0
    for l in data:
        if (l.startswith("vertex")):
            c+=1
            ld = l.replace("\n","").split(" ")
            lfctl.append(str(int(double(ld[1])*deps+path[2][0])/deps))
            lfctl.append(str(int(double(ld[2])*deps+path[2][1])/deps))
            lfctl.append(str(int(double(ld[3])*deps+path[2][2])/deps))
            if (c%3==0):
                fctl.append(lfctl)
                # print(lfctl)
                lfctl = []
    for i in range(len(fctl)):
        lt += "[ ["+fctl[i][0]+","+fctl[i][1]+","+fctl[i][2]+"],["+fctl[i][3]+","+fctl[i][4]+","+fctl[i][5]+"],["+fctl[i][6]+","+fctl[i][7]+","+fctl[i][8]+"],"
        lt += color
        lt += '],'
lt += "];\n"



path_w = './obj.js'

wf = open(path_w, mode='w')
wf.write(lt)