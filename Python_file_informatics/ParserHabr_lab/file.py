import numpy as np
import matplotlib.pyplot as plt
from nltk.stem.snowball import SnowballStemmer
from nltk.corpus import stopwords
import nltk

nltk.download('stopwords')

stemmer = SnowballStemmer("russian")
russian_stopwords = stopwords.words("russian")


data = ['Британская полиция знает о местонахождении основателя WikiLeaks', 'В суде США начинается процесс против россиянина, рассылавшего спам', 'Церемонию вручения Нобелевской премии мира бойкотируют 19 стран', 'В Великобритании арестован основатель сайта Wikileaks Джулиан Ассандж', 'Украина игнорирует церемонию вручения Нобелевской премии', 'Шведский суд отказался рассматривать апелляцию основателя Wikileaks', 'НАТО и США разработали планы обороны стран Балтии против России', 'Полиция Великобритании нашла основателя WikiLeaks, но, не арестовала', 'В Стокгольме и Осло сегодня состоится вручение Нобелевских премий']

d = list(map(lambda el: el.lower(), data))
d = list(map(lambda el: el.replace(",", ""), d))
d = list(map(lambda el: el.replace(".", ""), d))
# d = list(map(lambda el: el.split(" "), d))

# s = list(map(lambda el: el.replace(",", ""), stop_word))
# s = list(map(lambda el: el.split(" "), s))
# res = []
# for x in s:
#     res.extend(x if isinstance(x, list) else [x])

# for el in russian_stopwords:
#     for item in d:
#         if el in item:
#             item.remove(el)
res= []
for el in d:
    res.append(' '.join([stemmer.stem(word) for word in el.split() if word not in russian_stopwords]))

res = list(map(lambda el: el.split(), res))
print(res)
print(d)

word = set()
for el in res:
    for subel in el:
        word.add(subel)
word

unique = []
for el in word:
    sum = 0
    for item in res:
        sum += item.count(el)
    if sum == 1:
        unique.append(el)

for el in res:
    for item in unique:
        if item in el:
            el.remove(item)
word.clear()
for el in res:
    for subel in el:
        word.add(subel)
w = list(word)
w = sorted(w, key = lambda el: el)


A = np.zeros((len(w),len(res)), dtype=int)
for i in range(len(w)):
    for j in range(len(res)):
        if w[i] in res[j]:
            A[i][j] = 1


U, W, VT = np.linalg.svd(A)
U1 = U[:,0:2]

VT1 = VT[0:2, :]

W1 = W[0:2]
W1=np.diag(W1)

R = np.matmul(np.matmul(U1, W1), VT1)



fig, ax = plt.subplots()
x = U1[:,0]
y=U1[:,1]

x1 = VT1[0,:]
y1 = VT1[1,:]
ax.set_xlim(-0.7,0.1)
ax.set_ylim(-0.7,0.1)
ax.text(x[0],y[0]-0.05, w[0])
ax.scatter(x[0],y[0], c='r')
ax.text(x[7],y[7], w[7])
ax.scatter(x[7],y[7], c='r')
ax.text(x[11],y[11], w[11])
ax.scatter(x[11],y[11], c='r')

for i in range(len(x1)):
    ax.text(x1[i], y1[i], 'T{}'.format(i+1))
    ax.scatter(x1[i], y1[i],c='b')

def min_ras(n):
    x0 = VT1[0,n-1]
    y0 = VT1[1,n-1]
    min = 1000000
    index = 0
    for i in range(len(VT1[0,:])):
        if i != n-1:
            current_min = np.sqrt( (x0-VT1[0,i])**2 + (y0-VT1[1,i])**2)
            if current_min <= min:
                min = current_min
                index = i+1
    return index

min_ras(7)

