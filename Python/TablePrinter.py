"Takes an input list of lists and print them as a table"

TABLE_DATA = [['apples', 'oranges', 'cherries', 'banana'],
              ['Alice', 'Bob', 'Carol', 'David'],
              ['dogs', 'cats', 'moose', 'goose'],
              ['man', 'woman', 'alien', 'AI']]

def table_printer(lists):
    "Prints the table"
    number_lists = len(lists)
    number_items = len(lists[0])
    max_length = 0
    for listof in lists:
        for item in listof:
            if len(item) > max_length:
                max_length = len(item)
    col_widths = max_length

    for i in range(number_items):
        line = ""
        for j in range(number_lists):
            line += (lists[j][i].rjust(col_widths))
        print(line)

table_printer(TABLE_DATA)
