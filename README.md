# programmingLanguage
programming language class (2017-1, Hanyang Univ)

### Homework 1 
- DFA
- NFA

### Homework 2 
- LR Parser
- Function that builds DFA from a regular expression string

### Homework 3 
- Haskell problem
- problem 1. Finding Primes
- problem 2. Flip Coins   
    SeulGi has a stack of coins. She has a strange hobby, which is to make all coins’ face same direction.    
    Without scattering coins, she is supposed to make all coins head up by flipping the stack repeatedly.   
    Let’s see following example, where H means Head and T means Tail.   
    flip " HTTHT HH" 5    
    " HTHHT HH"   
    flip " HTHH THH" 4    
    " TTHT THH"   
    First, flipping 5 coins changes “HTTHT” into “HTHHT” (=not “THTTH”) because the order is reversed   
    and each coins’ face is flipped. In the same manner, flipping 4 coins makes “HTHH” become “TTHT”.   
    Make a function that lists the indices of flipping to make all coins face same way as following described   
    rule.

