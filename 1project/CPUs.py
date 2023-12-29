import random
a = open("CPUs.txt", "w")
PF = ("INTEL", "AMD")
YN = ("yes", "no")
RAM = ("DDR", "DDSR")
for i in range(101):
    if i == 0:
        a.write("|        COST |             DEV NAME |     SOCKET |   FAM PROC | CORES |     I CORE | GAME |  R YEAR | R TYPE |   CPU HZ |     TDP | PCI\n")
        print(len("|        COST |             DEV NAME |     SOCKET |   FAM PROC | CORES |     I CORE | GAME |  R YEAR | R TYPE |   CPU HZ |     TDP | PCI"))
    else:
        c = random.randint(0, 9999999)
        d = random.randint(0, 999999)
        e = random.choice(PF)
        f = random.randint(1, 99)
        g = e+"-"+str(random.randint(1, 999))
        h = random.choice(YN)
        x = random.choice(RAM)
        y = str(random.randint(1, 99))
        hz = str(random.randint(1, 99999))
        tdp = str(random.randint(10, 1500))
        z = random.choice(YN)
        a.write("| "+" "*(7-(len(str(c))))+str(c)+"руб."+" | "+" "*(20-(10+len(str(i))))+"Processor_"+str(i)+" | "+" "*(7-len(str(d)))+"SK-"+str(d)+" | "+" "*(10-len(e))+e+" | "+" "*(5-len(str(f)))+str(f)+" | "+" "*(10-len(g))+g+" | "+" "*(4-len(h))+h+" |  "+str(random.randint(2000, 2023))+"г. | "+" "*(6-(len(x)+len(y)))+x+y+" | "+" "*(5-len(hz))+hz+"ГГц | "+" "*(5-len(tdp))+str(tdp)+"Вт | "+" "*(3-len(z))+z+"\n")
a.close()
