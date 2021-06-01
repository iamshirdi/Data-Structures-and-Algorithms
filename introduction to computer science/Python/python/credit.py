import sys
from cs50 import get_string

i = get_string("Number:")
if len(i) not in [13,15,16]:
    print("INVALID")
    sys.exit(1)
add1 = 0
add2 = 0
for n in range(len(i)-2,-2,-2):
    print("count is ",n)
    if n > -1:
        add = int(i[n])*2
        if add < 10:
            add1+=add
            add1=int(add1)
            print('add1', add1)
        else:
            add1 = add1 + add%10 + add/10
            add1=int(add1)
            print('add1', add1)

    add2+=int(i[n+1])
    add2=int(add2)
    print(add2)

sum = add1 + add2
valid = (round(sum))%10
print(valid, "  ", len(i))


if valid != 0:
    print("INVALID")
elif len(i) == 15:
    print("AMEX")
elif len(i) == 16 and i[0] == '4':
    print("VISA")
else:
    print("MASTERCARD")


