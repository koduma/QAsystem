import MeCab
import os
from collections import defaultdict
import re

cwd = os.getcwd()

xxx_dict = dict()
yyy_dict = dict()
zzz_dict = defaultdict(list)
result = defaultdict(list)
prob = dict()

counter=1
l=60000
dp = [[0 for i in range(10005)] for j in range(10005)]

for memo in range(l):
    ac=0
    if memo%4000==0:
        ac=int(memo/4000)
    else:
        ac=int(memo/4000)+1
    classes_path = cwd +'/dir'+str(ac)+'/'+str(memo)+'_a.txt'
    is_file = os.path.isfile(classes_path)
    if is_file==False:
        continue    
    aaa = os.path.expanduser(classes_path)
    with open(classes_path, 'r', encoding='utf-8', errors='ignore') as f:
        class_names = f.readlines()   
        
    mecabTagger = MeCab.Tagger()
    noun_count = {}
    text=str(class_names)
    node = mecabTagger.parseToNode(text)
    while node:
        word = node.surface
        flag = word not in xxx_dict.keys()    
        if flag == False:#辞書にwordがある
            pass
        else:
            xxx_dict[word]=counter
            yyy_dict[counter]=word
            prob[counter]=1
            counter+=1    
        node = node.next

for memo in range(l):
    ac=0
    if memo%4000==0:
        ac=int(memo/4000)
    else:
        ac=int(memo/4000)+1
    classes_path = cwd +'/dir'+str(ac)+'/'+str(memo)+'_a.txt'
    is_file = os.path.isfile(classes_path)
    if is_file==False:
        continue    
    aaa = os.path.expanduser(classes_path)
    with open(classes_path, 'r', encoding='utf-8', errors='ignore') as f:
        class_names = f.readlines()   
        
    mecabTagger = MeCab.Tagger()
    noun_count = {}
    text=str(class_names)
    node = mecabTagger.parseToNode(text)
    node2 = node.next
    while node and node2:
        word = node.surface
        word2 = node2.surface
        flag = word not in xxx_dict.keys()
        flag2 = word2 not in xxx_dict.keys()
        if flag == False and flag2 == False:
            zzz_dict[xxx_dict[word]].append(xxx_dict[word2])
            prob[xxx_dict[word]]=prob[xxx_dict[word]]+1
            prob[xxx_dict[word2]]=prob[xxx_dict[word2]]+1
            if 70000 < xxx_dict[word] and xxx_dict[word] <= 80000 and 70000 < xxx_dict[word2] and xxx_dict[word2] <= 80000:
                dp[xxx_dict[word]-70000][xxx_dict[word2]-70000]+=1
        node = node.next
        node2 = node.next

for i in range(1,10001,1):
    for j in range(1,10001,1):
        if dp[i][j]>0:
            with open('dp.txt','a') as f:
                f.write(str(i+70000)+','+str(j+70000)+','+str(dp[i][j])+'\n')
    #with open('prob.txt', 'a') as f:
        #f.write(str(prob[i])+'\n')
    #with open('yyy_dict.txt', 'a') as f:
        #f.write(yyy_dict[i]+'\n')
    #with open('xxx_dict.txt', 'a') as f:
        #f.write(xxx_dict[i]+'\n')    
    #with open('zzz_dict.txt', 'a') as f:
        #s=str(set(zzz_dict[i]))
        #f.write(s[1:-1]+'\n')    