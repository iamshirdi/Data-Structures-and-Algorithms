import cs50
def inp():
    h = int(cs50.get_int("Height:"))
    return h
h = 0
while 8<h or h<1:
    h = inp()

for i in range(1,h+1):
    print(" "*(h-i),end="")
    print("#"*i,end="  ")
    print("#"*i,end="")
    print()
