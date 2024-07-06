def compute_distances(numbers):
    return  [(numbers[i + 1] - numbers[i]) for i in range(len(numbers) - 1)]

def compute_next_value(numbers):
    first_numbers = [numbers[0]]
    distances = numbers

    while True:
        distances = compute_distances(distances)
        first_numbers.insert(0, distances[0])
        if all(d == 0 for d in distances):
            ret = 0
            for n in first_numbers:
                ret = n - ret
            return ret

ret = 0
with open("input.txt", "r") as file:
    for line in file.readlines():
        numbers = list(map(lambda n:int(n), line.strip().split(" ")))
        ret += compute_next_value(numbers)

    print("Answer:", ret)

