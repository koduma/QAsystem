import MeCab
import os


classes_path = 'x.txt'
aaa = os.path.expanduser(classes_path)
with open(classes_path) as f:
    class_names = f.readlines()
    
classes_path = 'y.txt'
aaa = os.path.expanduser(classes_path)
with open(classes_path) as f:
    class_names2 = f.readlines()    

mecabTagger = MeCab.Tagger()

noun_count = {}
noun_count2 = {}

text=str(class_names)
text2=str(class_names2)

node = mecabTagger.parseToNode(text)
while node:
    word = node.surface
    hinshi = node.feature.split(",")[0]
    ippan = node.feature.split(",")[1]
    if word in noun_count.keys() and hinshi == "名詞" and ippan == "一般":
        noun_freq = noun_count[word]
        noun_count[word] = noun_freq + 1
    elif hinshi == "名詞" and ippan == "一般":
        noun_count[word] = 1
    else:
        pass
    node = node.next
    
noun_count = sorted(noun_count.items(), key=lambda x:x[1], reverse=True)

node2 = mecabTagger.parseToNode(text2)
while node2:
    word = node2.surface
    hinshi = node2.feature.split(",")[0]
    ippan = node2.feature.split(",")[1]
    if word in noun_count2.keys() and hinshi == "名詞" and ippan == "一般":
        noun_freq = noun_count2[word]
        noun_count2[word] = noun_freq + 1
    elif hinshi == "名詞" and ippan == "一般":
        noun_count2[word] = 1
    else:
        pass
    node2 = node2.next
    
noun_count2 = sorted(noun_count2.items(), key=lambda x:x[1], reverse=True)

score=0

for i in range(len(noun_count)):
    for j in range(len(noun_count2)):
        if noun_count[i][0] == noun_count2[j][0]:
            score+=1
            
f = open('score.txt', 'w')
f.write(str(score))
f.close()