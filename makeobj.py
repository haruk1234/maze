from numpy import double
from scipy.misc import face


lt = ""




paths = [
    ["./title.stl",[250,150,80],[-5,-10,1]],
    ["./human.stl",[220,200,200],[-4,-10,0.5]],
]

lt += "scene['title'] = "
lt += "[ [0],"
lt += "["

for path in paths:
    with open(path[0]) as f:
        data = f.readlines()

    color = "[0],["+str(path[1][0])+"],["+str(path[1][1])+"],["+str(path[1][2])+"],"

    fctl = []
    lfctl = []
    c = 0

    for l in data:
        if (l.startswith("vertex")):
            c+=1
            ld = l.replace("\n","").split(" ")
            lfctl.append(str(double(ld[1])+path[2][0]))
            lfctl.append(str(double(ld[2])+path[2][1]))
            lfctl.append(str(double(ld[3])+path[2][2]))
            if (c%3==0):
                fctl.append(lfctl)
                # print(lfctl)
                lfctl = []
    for i in range(len(fctl)):
        lt += '['
        lt += "["+fctl[i][0]+","+fctl[i][1]+","+fctl[i][2]+"],["+fctl[i][3]+","+fctl[i][4]+","+fctl[i][5]+"],["+fctl[i][6]+","+fctl[i][7]+","+fctl[i][8]+"],"
        lt += color
        lt += "[0],"
        lt += '],'

lt += "]];\n"


paths = [
    ["./goal.stl",[250,150,80],[-5,-10,1]],
]

lt += "scene['goal'] = "
lt += "[ [0],"
lt += "["

for path in paths:
    with open(path[0]) as f:
        data = f.readlines()

    color = "[0],["+str(path[1][0])+"],["+str(path[1][1])+"],["+str(path[1][2])+"],"

    fctl = []
    lfctl = []
    c = 0

    for l in data:
        if (l.startswith("vertex")):
            c+=1
            ld = l.replace("\n","").split(" ")
            lfctl.append(str(double(ld[1])+path[2][0]))
            lfctl.append(str(double(ld[2])+path[2][1]))
            lfctl.append(str(double(ld[3])+path[2][2]))
            if (c%3==0):
                fctl.append(lfctl)
                # print(lfctl)
                lfctl = []
    for i in range(len(fctl)):
        lt += '['
        lt += "["+fctl[i][0]+","+fctl[i][1]+","+fctl[i][2]+"],["+fctl[i][3]+","+fctl[i][4]+","+fctl[i][5]+"],["+fctl[i][6]+","+fctl[i][7]+","+fctl[i][8]+"],"
        lt += color
        lt += "[0],"
        lt += '],'

lt += "]];\n"






path_w = './obj.js'

wf = open(path_w, mode='w')
wf.write(lt)