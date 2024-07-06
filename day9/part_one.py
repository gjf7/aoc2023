def compute_distances(numbers):
    return  [(numbers[i + 1] - numbers[i]) for i in range(len(numbers) - 1)]

def compute_next_value(numbers):
    distances = numbers
    last_numbers = [numbers[-1]]

    while True:
        distances = compute_distances(distances)
        last_numbers.append(distances[-1])
        if all(d == 0 for d in distances):
            return sum(last_numbers)
ret = 0
with open("input.txt", "r") as file:
    for line in file.readlines():
        numbers = list(map(lambda n:int(n), line.strip().split(" ")))
        ret += compute_next_value(numbers)
    print("Answer:", ret)

