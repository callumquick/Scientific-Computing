upper_bound = 1000
numbers = list(range(1,upper_bound+1))
new_list = []
for number in numbers:
    string = str(number)
    found = False
    for letter in string:
        if letter == "3":
            found = True
    if found:
        new_list.append(number)

print(new_list)
