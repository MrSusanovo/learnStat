class Markov(object):
    def __init__(self, state={}):
        self.__state=state
        total=0.0
        record={}
        pt={}
        single={}
        for k,v in state:
            single[k]=0
        for k in state:
            pt[k]=single.deepcopy()
        self.__pt=pt
        self.__last=None
    def fed(self, thing):
        # add to pt
        if not self.__pt.has_key(thing):
            self.__pt[thing]={thing:0}
        if self.__last==None:
            self.__pt[thing]={thing:0}
        else:
            if not self.__pt.has_key(self.__last):
                self.__pt[self.__last]={self.__last:0}
            elif not self.__pt[self.__last].has_key(thing):
                self.__pt[self.__last][thing]=1
            else:
                self.__pt[self.__last][thing]+=1
        # add to state
        if self.__state.has_key(thing):
            self.__state[thing]+=1
        else:
            self.__state[thing]=1
        # change last record
        self.__last=thing
    def display(self):
        print self.__state
        print self.__pt
