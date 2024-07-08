from sys import setrecursionlimit

def compute_circle_len():
    all_lines = []
    with open("input.txt", "r") as file:
        for line in file.readlines():
            all_lines.append(list(line.strip()))
    
    # find S
    s_position = []
    for i in range(len(all_lines)):
        if "S" not in all_lines[i]:
            continue
        s_position = [i, all_lines[i].index("S")]

    ret = 0

    def dfs(i, row, col):
        nonlocal ret

        if row < 0 or col < 0:
            return None
        if row >= len(all_lines) or col >= len(all_lines[0]):
            return None

        all_lines[row][col] = 1
        ret = max(ret, i)

        # top
        if row > 0 and all_lines[row - 1][col] in ['|', 'F', '7']:
            dfs(i + 1, row - 1, col)

        # bottom
        if row < len(all_lines) - 1 and all_lines[row + 1][col] in ['|', 'J', 'L']:
            dfs(i + 1, row + 1, col)

        # left
        if col > 0 and all_lines[row][col - 1] in ['-', 'F', 'L']:
            dfs(i + 1, row, col - 1)

        # right
        if col < len(all_lines[0]) - 1 and all_lines[row][col + 1] in ['-', '7', 'J']:
            dfs(i + 1, row, col + 1)

    setrecursionlimit(30000)
    dfs(0, s_position[0], s_position[1])
    print("Answer:", (ret + 1) / 2)

compute_circle_len()
