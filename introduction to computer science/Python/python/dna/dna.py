import sys
import csv

# dna = ['AGATC','TTTTTTCT','AATG','TCTAG','GATA','TATC','GAAA','TCTG']
# dna = ['AGATC']

if len(sys.argv)!=3:
    print("missing arguments")

database = []
with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        database.append(row)

    
# print(database[0])

f = open (sys.argv[2],"r")
person = f.read()
dna=[]
for key in database[0]:
    dna.append(key)
dna.remove('name')
# print(person)
# dna2 = {'AGATC':0,'TTTTTTCT':0,'AATG':0,'TCTAG':0,'GATA':0,'TATC':0,'GAAA':0,'TCTG':0}
dna2={}
for a in dna:
    dna2[a]=0
# print("dna is ",dna,"dna2 is",dna2)

for d in dna:
   # for each new dna use while loop to locate longest consequtive find 
    counter = 0
    i = 0
    #repeat till you find more
    person2 = person
    while (counter < len(person)):
        if person2.find(d) != -1:
            max = 0
            i = person2.index(d)
            l = len(d)
            d2 = person2[i:i+l]
            # print("d2 is ",d2,"i is",i)
            while d2 == d :
                # print(d2,d)
                max+=1
                # print("before index",i,"length is ",l)
                i = i+l
                # print("after index",i)
                
                d2 = person2[i:i+l]
                # print(d2,d)

                #reset max consequitive
            # print("maximum", max)
            if dna2[d]<max:
                dna2[d] = max
            #reset i
            # print("lenth", len(person2))
            person2 = person2[i:]
        # to skip index counter   
        if i>counter:
            counter = i
        else:
            counter+=1
     
# print(dna2)

# print("database is",database[0])



match = False
for row in database:
    c=0
    for row2 in dna:
        # print("row2 is prinitng",row2)
        # print("printing",row[row2], dna2[row2])
        if int(row[row2]) == dna2[row2]:
            c+=1
    if c== len(dna):
        print(row['name'])
        match = True
        break


            


        
if not match:        
    print("No Match")
# for name in database:
#     if name['name']=='Lavender':
#         print(name)
# print(person[778:800])
# sys.exit(1)