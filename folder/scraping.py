from bs4 import BeautifulSoup
import requests
import sys

memo=2526

def scraping(url):
    global memo
    header = {'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                        'AppleWebKit/537.36 (KHTML, like Gecko) '
                        'Chrome/51.0.2704.103 Safari/537.36'}
    req = requests.get(url,headers= header)
    if req.status_code == 404:
        memo=memo+1
        return 0    
    html = req.text
    soup = BeautifulSoup(html,'html.parser')
    elems = soup.select("#q_content > div.q_body > div.bodytext > p")
    q = str(elems[0].contents[0])
    elems2 = soup.find_all("p")
    a= str(elems2[1].contents[0])
    print(a)
    f = open(str(memo)+'_q.txt', 'w')
    f.write(q)
    f.close()
    f = open(str(memo)+'_a.txt', 'w')
    f.write(a)
    f.close()
    memo=memo+1
    
    return 1

while True:

    url2 = 'https://okwave.jp/qa/q'+str(9873782+(memo))+'.html'
    scraping(url2)
    print("memo="+str(memo))   