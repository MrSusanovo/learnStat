from copy import deepcopy

class HMM(object):
    def __init__(self, trans={}, state={}, emission={}):
        self.trans=trans
        self.state=state
        self.emission=emission
    def setTrans(self,t):
        if type(t)==type({}):
            self.trans=t
    def setTKey(self,tk=[]):
        if type(tk)==type([]):
            self.trans={}
            # set up rows
            for item in tk:
                self.trans.append({item: {}})
            # set up each row
            for k,v in self.trans.iteritems():
                v=map(lambda x: {x: 0.0}, tk)
    def setTProb(self, tv={}):
        # note: tv must have the form of
        # {key: {k : v}} where key, k, are string ,
        # v is float 
        if type(tv)==type({}):
            for k,v in tv:
                self.trans[k]=v
    def setEmit(self, e):
        if type(e)==type({}):
            self.emission = e
    def setEKey(self, ek):
        if type(ek)==type([]):
            self.trans={}
            # set up rows
            for item in ek[0]:
                self.emission.append({item: {}})
            # set up each row
            for k,v in self.emission.iteritems():
                v=map(lambda x: {x: 0.0}, ek[1])
    def setEProb(self, ev={}):
        # note: ev must have the form of
        # {key: {k : v}} where key, k, are string ,
        # v is float
        if type(ev)==type({}):
            for k,v in ev:
                self.emission[k]=v
    def setState(self, s):
        if type(s)==type({}):
            self.state=s
    def decode(self, observation):
        module = {k:0.0 for k, v in self.trans.iteritems()}
        state_prob = [deepcopy(module)]
        state_seq = []
        index = 0
        
        for i in observation:
            # update the probability dictionary 
            # at the beginning, only one observation
            if index == 0:
                # update the state_prob list 
                for k in state_prob[index]:
                    # state_prob[index][k]=P(k->i)
                    state_prob[index][k]=self.state[k]*self.emission[k][i]
            # if it is not the beginning 
            else:
                for k in state_prob[index]:
                    # state_prob[index][k]=P( k->i | last->k )*P(last)
                    last_hidden = state_seq[index-1]
                    last_prob = state_prob[index-1][last_hidden]
                    k_to_i = self.emission[k][i]
                    last_to_k = self.trans[last_hidden][k]
                    state_prob[index][k] = last_prob * last_to_k * k_to_i
            # update complete, finde the maximum prob and update it to sequnce
            maxed = False
            maxProb = 0.0
            for k in state_prob[index]:
                if not maxed:
                    maxed = True
                    maxProb=state_prob[index][k]
                    state_seq.append(k)
                elif state_prob[index][k] > maxProb:
                    maxProb=state_prob[index][k]
                    state_seq[index] = k
                else:
                    continue
            index+=1
            state_prob.append(deepcopy(module))
        return state_seq

            

# test code
h=HMM()
h.setTrans({"Healthy":{"Healthy":0.7, "Fever":0.3},
            "Fever":{"Healthy":0.4, "Fever": 0.6}})
h.setEmit({"Healthy":{"normal":0.5, "cold":0.4,"dizzy":0.1},
            "Fever":{"normal":0.1, "cold":0.3,"dizzy":0.6}})
h.setState({"Healthy": 0.6, "Fever": 0.4})
