
import numpy as np
from numpy.core.fromnumeric import size
import matplotlib.pyplot as plt
import random
import time

from joblib import Parallel, delayed

data=[]

N_samples = 10000
box_size = 100
N_boxes = int(N_samples/box_size)
acc=0.95
biais=0.6

epochs = 2000


def random_biais():

    if(np.random.rand()>biais):
        return 1
    else:
        return 0


i=0
while(i<N_samples):
    data.append({'ID' : str(i), 'value' : random_biais(), 'selections' : 0, 'box_ID':0})
    i += 1
    
def assign_data_to_box(i):
    counter=0
    while counter<box_size:    
        random_sample = np.random.random_sample([elem for elem in data if elem['box_ID'] == 0])
        data[data.index(random_sample)]['box_ID'] = i+1
        counter += 1
    return

def assign_data_to_boxes():
    
    for i in range(N_boxes):
        counter=0
        while counter<box_size:    
            random_sample = np.random.randint(0, N_samples)
            if(data[random_sample]['box_ID'] == 0):
                data[random_sample]['box_ID'] = i+1
                counter += 1
    
    #Parallel(n_jobs=3)(delayed(assign_data_to_box)(i) for i in range(N_boxes))

    return
def check_if_interesting():
    for i in range(N_boxes):
        data_aux=[elem for elem in data if elem['box_ID']==i]
       # print(data_aux)
        flow_percentage=sum([elem['value'] for elem in data_aux])
        flow_percentage/=box_size
        if(flow_percentage > 0.5 and np.random.rand() < acc):
            for elem in [elem for elem in data if elem['box_ID']==i]:
                elem['selections'] += 1
        elif(flow_percentage < 0.5 and np.random.rand() > acc):
            for elem in [elem for elem in data if elem['box_ID']==i]:
                elem['selections'] += 1
                
    return 

def reinitialize():
    for sample in data:
        sample['box_ID']=0
    return 

def plot():
    positives = [elem['selections']/epochs for elem in data if elem['value']==1]
    negatives = [elem['selections']/epochs for elem in data if elem['value']==0]
    plt.figure()
    plt.hist(positives, color='blue', alpha=0.8, label= 'Flow', bins=50)
    plt.hist(negatives, color='red',  alpha=0.8, label= 'Non-Flow', bins=50)
    plt.xlabel('N_selections/N_epochs')
    plt.ylabel('# entries')
    plt.legend(loc='best', fontsize=9.)
    plt.title('epochs='+str(epochs)+', '+'samples='+str(N_samples)+', '+'boxsize='+str(box_size))
    plt.savefig('Desktop/plots/'+str(epochs)+'_'+str(N_samples)+'_'+str(box_size)+'_'+'0_6')
    plt.show()


def simulate():
    ep = 0
    time_start=time.time()
    while(ep<epochs):

        assign_data_to_boxes()
        check_if_interesting()
        reinitialize()

        ep+=1
        if(ep%50==0):
            print(ep)
    plot()
    print('delay= ', time.time()-time_start)

simulate()
