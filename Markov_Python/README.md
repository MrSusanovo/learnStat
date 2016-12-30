HMM class implemented in python

An example of using it

``` python
# import HMM
from hmm import HMM 

# Create an HMM instance
h=HMM()

# Set the transition probability matrix 
h.setTrans({"Healthy":{"Healthy":0.7, "Fever":0.3},
            "Fever":{"Healthy":0.4, "Fever": 0.6}})

# Set the eimission probability matrix
h.setEmit({"Healthy":{"normal":0.5, "cold":0.4,"dizzy":0.1},
            "Fever":{"normal":0.1, "cold":0.3,"dizzy":0.6}})

# Set the initial state space
h.setState({"Healthy": 0.6, "Fever": 0.4})

# evaluate the probability of observing the following symptoms
# in the following 3 days

h.evaluate(["normal","cold","dizzy"])
# produces a number approximately 0.0381 

# evaluate the probability of observing dizzy and cold 
# AFTER observing normal cold dizzy in the first 3 days

h.evaluate(["normal","cold","dizzy"], ["dizzy","cold"])
# produces a number approximately 0.112

# produces a sequnce of Health/Fever (hidden status)
# which most likely generates the following observation

h.decode(["normal","cold","dizzy"])
# ["Healthy", "Healthy", "Fever"]

  ```
  
  Upcomming:  .learn()  - Figures out the parameters/the whole modle with given observation
  
