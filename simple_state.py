def check(state, word):
    if len(word) == 0:
        return state == 2
    
    current = word[0]
    if state == 0:
        if current == 'a':
            return check(1, word[1:])
        else:
            return False
    elif state == 1:
        if (current == 'a'):
            return check(1, word[1:])
        elif (current == 'b'):
            return check(2, word[1:])
        else:
            return False
    elif state == 2:
        return False
        
        
print(check(0, "aaab"))    # true
print(check(0, "aaaaaab")) # true
print(check(0, "aaaba"))   # false
print(check(0, "aaabb"))   # false
print(check(0, "aaaaaa"))  # false
