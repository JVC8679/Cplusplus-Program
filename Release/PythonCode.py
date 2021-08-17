import re
import string

# Open file and builds dictionary of items with counts then displays those counts
def printlist():
    
    with open('itemlist.txt') as text: 
    
        d = dict()

        for line in text:
            line = line.strip()
            words = line.split(" ")

            for word in words:
               if word in d:
                   d[word] = d[word] + 1
               else:
                  d[word] = 1
        for key in list(d.keys()):
           print(key, d[key])
        
 
    

    
# Opens file and builds dictionary of items then searches for user input an returns amount
def printitem(v):
    with open('itemlist.txt') as text: 
        v = v.capitalize()
        d = dict()

        for line in text:
            line = line.strip()
            words = line.split(" ")

            for word in words:
               if word in d:
                   d[word] = d[word] + 1
               else:
                  d[word] = 1
    return d[v]





# Opens file and builds dictionary of items then writes that file to a .dat for C++ to use 
def itemprinter():
   
    with open('frequency.dat', "w") as freq:    
        with open('itemlist.txt') as text:
            d = dict()

            for line in text:
                line = line.strip()
                words = line.split(" ")

                for word in words:
                    if word in d:
                        d[word] = d[word] + 1
                    else:
                        d[word] = 1
            for key in list(d.keys()):
                freq.write('%s %d\n' % (key, d[key]))



    


def SquareValue(v):
    return v * v



    
