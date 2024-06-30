from collections import Counter;

def value_freq(d, target_value):
    return list(d.values()).count(target_value)

def sorter(hand):
    value = 0
    for c in hand[0]:
        value = value * 20 + cards_index[c]
    return value


cards = ['J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A']

cards_index = {}
for index, item in enumerate(cards):
    cards_index[item] = index

five_kind  = []
four_kind  = []
full_house = []
three_kind = []
two_pair   = []
one_pair   = []
high_card  = []

with open("input.txt", "r") as file:
    lines = file.readlines()
    for line in lines:
        hand = line.strip().split(" ");
        has_joker = "J" in hand[0]
        joker_count = hand[0].count("J")
        hand_without_j = hand[0].replace("J", "")
        char_freq_dict = dict(Counter(hand_without_j))

        hand_type = None
        if value_freq(char_freq_dict, 5):
            hand_type = five_kind
        elif value_freq(char_freq_dict, 4):
            if joker_count == 1:
                hand_type = five_kind
            else:
                hand_type = four_kind
        elif value_freq(char_freq_dict, 3):
            if value_freq(char_freq_dict, 2):
                hand_type = full_house
            else:
                if joker_count == 1:
                    hand_type = four_kind
                elif joker_count == 2:
                    hand_type = five_kind
                else:
                    hand_type = three_kind
        elif value_freq(char_freq_dict, 2) == 2:
            if joker_count == 1:
                hand_type = full_house
            else:
                hand_type = two_pair
        elif value_freq(char_freq_dict, 2) == 1:
            if joker_count == 1:
                hand_type = three_kind
            elif joker_count == 2:
                hand_type = four_kind
            elif joker_count == 3:
                hand_type = five_kind
            else:
                hand_type = one_pair
        else:
            if joker_count == 1:
                hand_type = one_pair
            elif joker_count == 2:
                hand_type = three_kind
            elif joker_count == 3:
                hand_type = four_kind
            elif joker_count == 4 or joker_count == 5:
                hand_type = five_kind
            else:
                hand_type = high_card

        hand_type.append(hand)


    five_kind.sort(key=sorter)
    four_kind.sort(key=sorter)
    full_house.sort(key=sorter)
    three_kind.sort(key=sorter)
    two_pair.sort(key=sorter)
    one_pair.sort(key=sorter)
    high_card.sort(key=sorter)


    ret = 0
    i = 0
    for hand_type in [high_card, one_pair, two_pair, three_kind, full_house, four_kind, five_kind]:
        for hand in hand_type:
            i += 1
            ret += i * int(hand[1])

    print("Answer:", ret)

