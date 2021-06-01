import cs50
input = cs50.get_string("Text:")
words = 1
sentences = 0
letters = 0
for i in input:
    if i =='?' or i =='.' or i == '!':
        sentences+=1
    elif i == ' ':
        words+=1
    elif i not in ["'","’",",",";","?",'.','!',' ','-']:
        letters+=1
print(letters,words,sentences)
if words < 100:
    avg_l = (letters/words)*100
    avg_s = (sentences/words)*100
print(avg_l, avg_s)
index = 0.0588 * avg_l - 0.296 * avg_s - 15.8
print(index)
grade = round(index)
if grade > 16:
    print("Grade 16+")
elif grade <= 1:
    print("Before Grade 1")
else:
    print ("Grade:",grade)