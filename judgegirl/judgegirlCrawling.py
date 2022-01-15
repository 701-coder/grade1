import requests
from tqdm import tqdm
from bs4 import BeautifulSoup
import json
import xlrd
import os
import pandas as pd
from tabulate import tabulate
import prettytable as pt
import xlsxwriter
from openpyxl import load_workbook

def printData(a):
    print(tabulate(a))
    print()
    return

def isNumber(c):
    s='0123456789'
    for i in range(len(s)):
        if c==s[i]:
            return 1
    return 0

def isUpperCase(c):
    s='ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    for i in range(len(s)):
        if c==s[i]:
            return 1
    return 0

def isLowerCase(c):
    s='abcdefghijklmnopqrstuvwxyz'
    for i in range(len(s)):
        if c==s[i]:
            return 1
    return 0

def isID(c):
    if len(c)!=9:
        return 0
    if isUpperCase(c[0])==0:
        return 0
    for i in range(1, 9):
        if isNumber(c[i])==0:
            return 0
    return 1


sheet1=pd.read_excel('name.xlsx', sheet_name='Sheet2')
num=list(sheet1.iloc[:, 0])
name=list(sheet1.iloc[:, 1])
data=[[num[i], name[i]]for i in range(len(num))]
sheet1=pd.read_excel('name.xlsx', sheet_name='Sheet3')
gp=list(sheet1.iloc[1:15, 4])
gpmember=list(sheet1.iloc[1:15, 6])
gpleadernum=list(sheet1.iloc[1:15, 7])
member=[[gp[i]]for i in range(len(gp))]
gpscore=[0 for i in range(len(gp))]
for i in range(len(gp)):
    for j in range(len(str(gpmember[i]))-8):
        s=''
        for k in range(9):
            s+=gpmember[i][j+k]
        if isID(s):
            member[i].append(s)
for i in range(len(data)):
    l=0
    for j in range(len(member)):
        for k in range(1, len(member[j])):
            if data[i][0]==member[j][k]:
                data[i].append(member[j][0])
                l=1
                break
        if l==1:
            break
    if l==0:
        data[i].append('Anonymous')

urlRead=open('url.txt', 'r').read()
urlWrite=open('url.txt', 'a')
urlData=urlRead.split('pypwd')

Person=[]
Score=[]
person=[]
score=[]


def upd():
    for i in range(len(data)):
        j=0
        while j<len(person):
            if data[i][0]==person[j]:
                break
            j+=1
        if j<len(person):
            data[i].append(score[j])
            score[j]=0
        else:
            data[i].append(0)

def crawl(url, live):
    soup=''
    print('Crawling ', url)
    if live==0:
        for i in range(len(urlData)):
            if urlData[i]==url:
                soup=urlData[i+1]
                break
    if len(soup)==0:
        res=requests.get(url)
        soup=BeautifulSoup(res.text, 'html.parser')
        soup=str(soup)
        if live==0:
            urlWrite.write(url+'pypwd'+soup+'pypwd')
    #goal='sid-header'
    #idx=soup.find(goal)
    #if idx==-1:
    #    print('Data not found')
    #    return
    #print('Founded')
    #rawData=[[]]
    #for i in range(3):
    #    rawData.append([])
    #while True:
    #    goal="sid"
    #    idx=soup.find(goal, idx)
    #    if idx==-1:
    #        break
    #    print("sid-founded")
    #    while isNumber(soup[idx])==0:
    #        ++idx
    #    s=''
    #    while isNumber(soup[idx])==1:
    #        s+=soup[idx]
    #        ++idx
    #    rawData[0].append(s)
    #    while isNumber(soup[idx])==0:
    #        ++idx
    #    s=''
    #    while isNumber(soup[idx])==1:
    #        s+=soup[idx]
    #        ++idx
    #    rawData[1].append(s)
    #print(rawData)
    goal='<a href="/user/'
    sc0='Accepted'
    sc1='score: '
    sc2='Compilation Error'
    for i in range(len(soup)):
        k=1
        for j in range(len(goal)):
            if soup[i+j]!=goal[j]:
                k=0
                break
        if k==1:
            while soup[i]!='>':
                i+=1
            i+=1
            s=''
            sc=0
            for j in range(9):
                s+=soup[i+j]
            j=i
            while True:
                k=1
                for l in range(len(sc0)):
                    if soup[j+l]!=sc0[l]:
                        k=0
                        break
                if k==1:
                    sc=100
                    break
                k=1
                for l in range(len(sc1)):
                    if soup[j+l]!=sc1[l]:
                        k=0
                        break
                if k==1:
                    l=j+7
                    ssc=''
                    while soup[l]!=')':
                        ssc+=soup[l]
                        l+=1
                    sc=int(ssc)
                    break
                k=1
                for l in range(len(sc2)):
                    if soup[j+l]!=sc2[l]:
                        k=0
                        break
                if k==1:
                    break
                j+=1
            j=0
            while j<len(person):
                if s==person[j]:
                    break
                j+=1
            if j<len(person):
                score[j]=max(score[j], sc)
            else:
                person.append(s)
                score.append(sc)
totalT=20
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10281', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10283', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10282', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10284', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10285', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10286', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10287', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10290', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10289', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10288', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10291', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10292', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10294', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10296', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10295', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10297', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10298', 0)
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10299', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10300', 0)
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10303', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10301', 0)
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10304', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10302', 0)
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10305', 0)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10306', 1)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10307', 1)
upd()
for T in range(1, totalT):
    crawl('http://judgegirl.csie.org/submissions?page='+str(T)+'&pid=10308', 1)
upd()


#for i in range(len(Person)):
    #for j in range(len(Person)-1):
        #if Person[j]>Person[j+1]:
            #Person[j], Person[j+1]=Person[j+1], Person[j]
            #Score[j], Score[j+1]=Score[j+1], Score[j]

printData(data)
os.system("read -p 'Press Enter to continue...' var")

num1=15
num2=12

for i in range(len(data)):
    k=0
    for j in range(3, len(data[i])):
        k+=data[i][j]
    data[i].append(k)
    if i<80:
        data[i].append(k/num1)
    else:
        for j in range(3+num2, 3+num1):
            data[i][j]=-1
        data[i].append(k/num2)

for i in range(len(data)):
    data[i].append(1)
for i in range(len(data)):
    for j in range(len(data)):
        if data[i][len(data[i])-2]>data[j][len(data[j])-2]:
            data[j][len(data[j])-1]+=1

for i in range(len(data)):
    data[i].append(1)
for i in range(len(data)):
    for j in range(len(data)):
        if data[i][2]==data[j][2] and data[i][len(data[i])-3]>data[j][len(data[j])-3]:
            data[j][len(data[j])-1]+=1

for i in range(len(data)):
    for j in range(len(gp)):
        if data[i][2]==gp[j]:
            gpscore[j]+=data[i][len(data[j])-3]

gpdata=[]
for i in range(len(gp)):
    j=0
    while j<len(gpdata):
        if gpdata[j][0]==gp[i]:
            break
        j+=1
    if j<len(gpdata):
        continue
    idx=len(gpdata)
    gpdata.append([])
    gpdata[idx].append(gp[i])
    gpdata[idx].append(0)
    for j in range(len(data)):
        if data[j][2]==gpdata[idx][0]:
            gpdata[idx][1]+=1
    gpdata[idx].append(round(gpscore[i]/gpdata[idx][1], 2))

printData(data)
os.system("read -p 'Press Enter to continue...' var")

for i in range(len(data)):
    for j in range(len(data)-i-1):
        if data[j][len(data[j])-3]<data[j+1][len(data[j+1])-3]:
            data[j], data[j+1]=data[j+1], data[j]

printData(data)
os.system("read -p 'Press Enter to continue...' var")

for i in range(len(data)):
    for j in range(len(data)-i-1):
        if data[j][2]<data[j+1][2] or (data[j][2]==data[j+1][2] and data[j][len(data[j])-3]<data[j+1][len(data[j+1])-3]):
            data[j], data[j+1]=data[j+1], data[j]

printData(data)
printData(gpdata)
os.system("read -p 'Press Enter to continue...' var")
