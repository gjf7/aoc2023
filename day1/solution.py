def partOne():
    with open("input.txt", encoding="utf-8") as f:
        lines = f.readlines()
        sumMax = 0
        currentSum = 0
        for line in lines:
            if line == "\n":
                sumMax = max(currentSum, sumMax)
                currentSum = 0
            else:
                currentSum += int(line)
        return max(currentSum, sumMax)


def partTwo():
    with open("input.txt", encoding="utf-8") as f:
        lines = f.readlines()
        topThree = [0] * 3
        currentSum = 0
        for i in range(len(lines)):
            line = lines[i]
            if line != "\n":
                currentSum += int(line)
                if i != len(lines):
                    continue
            if currentSum > min(topThree):
                topThree.remove(min(topThree))
                topThree.append(currentSum)
            currentSum = 0
        return sum(topThree)


print(partOne())
print(partTwo())
