input = "Callum"


def name_badge(input):
    length = len(input) + 4
    border = "-" * length
    name = input.center(length, "-")
    print(border)
    print(name)
    print(border)

name_badge(input)
