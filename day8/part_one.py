with open("input.txt", "r") as file:
    instructions = file.readline().strip()

    # skip blank line
    file.readline()
    
    notebook = {}
    for line in file.readlines():
        tokens = line.strip().split(" = ")
        node = tokens[0]
        leftright = tokens[1][1:len(tokens[1]) - 1].split(", ")

        notebook[node] = leftright

    i = 0
    steps = 0
    current = "AAA"

    while True:
        if current == "ZZZ":
            break

        direction = instructions[i]
        steps += 1

        if direction == "L":
            current = notebook[current][0]
        else:
            current = notebook[current][1]

        i += 1
        if i == len(instructions):
            i = 0

    print("Answer", steps)


