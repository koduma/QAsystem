import MeCab
import os


classes_path = 'z.txt'
with open(classes_path, 'r', encoding='utf-8', errors='ignore') as f:
    class_names = f.readlines()

mecabTagger = MeCab.Tagger()

text=str(set(class_names))

node = mecabTagger.parseToNode(text)

l=[]

while node:
    word = node.surface
    hinshi = node.feature.split(",")[0]
    ippan = node.feature.split(",")[1]
    #print(str(word)+","+str(hinshi)+","+str(ippan))
    if hinshi == "名詞":#and ippan == "一般":
        l.append(word)
    node = node.next

file=open("w.txt","w")

for line in l:
    file.write(line+"\n")

file.close()