import time


def get_mapped_pos(the_map, seed):
    for current_range in the_map:
        if current_range[1] < seed:
            continue
        if seed < current_range[0]:
            continue
        return current_range[2] + (seed - current_range[0])
    return seed


def pairwise(iterable):
    a = iter(iterable)
    return zip(a, a)


def part1():
    print("Day 5, Part 1: ", end="")
    file = open("input.txt")
    lines = file.readlines()
    file.close()

    seeds = list(map(lambda x: int(x.strip()), lines[0].split(": ")[1].split(" ")))
    lines.pop(0)

    maps = []
    map_names = []
    current_map = []
    need_name = True

    for line in lines:
        if line.isspace():
            if len(current_map) != 0:
                current_map.sort(key=lambda x: x[0])
                maps.append(current_map)
                current_map = []
                need_name = True
            continue

        if need_name:
            map_names.append(line.split(" ")[0])
            need_name = False
            continue

        line = line.strip()
        tokens = line.split(" ")
        length = int(tokens[2])
        dest_start = int(tokens[0])
        source_start = int(tokens[1])

        current_map.append([source_start, source_start + length, dest_start])  #

    if len(current_map) != 0:
        current_map.sort(key=lambda x: x[0])
        maps.append(current_map)

    lowest = -1
    for seed in seeds:
        for i, the_map in enumerate(maps):
            # print(the_map)
            # oldSeed = seed
            seed = get_mapped_pos(the_map, seed)
            # print(f"{map_names[i]}: {oldSeed} maps to {seed}")

        if lowest < 0:
            lowest = seed
        elif seed < lowest:
            lowest = seed

    print(f"Lowest location: {lowest}")


def part2():
    print("Day 5, Part 2: ", end="")
    file = open("input.txt")
    lines = file.readlines()
    file.close()

    seeds = list(map(lambda x: int(x.strip()), lines[0].split(": ")[1].split(" ")))
    lines.pop(0)

    maps = []
    map_names = []
    current_map = []
    lowest_length = -1
    need_name = True

    for line in lines:
        if line.isspace():
            if len(current_map) != 0:
                current_map.sort(key=lambda x: x[0])
                maps.append(current_map)
                current_map = []
                need_name = True
            continue

        if need_name:
            map_names.append(line.split(" ")[0])
            need_name = False
            continue

        line = line.strip()
        tokens = line.split(" ")
        length = int(tokens[2])
        dest_start = int(tokens[0])
        source_start = int(tokens[1])

        if lowest_length == -1 or length < lowest_length:
            lowest_length = length

        current_map.append([source_start, source_start + length, dest_start])  #

    if len(current_map) != 0:
        current_map.sort(key=lambda x: x[0])
        maps.append(current_map)

    lowest = []
    for (seed_start, range_len) in pairwise(seeds):
        # 3 nested for loops… ouch
        # Yeah, no, not in python.
        # for seed in range(seed_start, seed_start + range_len):
        #     for the_map in maps:
        #         seed = get_mapped_pos(the_map, seed)
        #
        #     if lowest == -1 or seed < lowest:
        #         lowest = seed
        seed_end = seed_start + range_len
        while seed_start < seed_end - 1:
            mapped_start = seed_start
            for the_map in maps:
                mapped_start = get_mapped_pos(the_map, mapped_start)
            if len(lowest) == 0 or mapped_start < lowest[0]:
                lowest = [mapped_start, seed_start]

            seed_start = min(seed_end - 1, seed_start + lowest_length)

    factor = 10000
    while True:
        old_lowest = lowest[0]
        old_lowest_unmapped = lowest[1]
        lowest[1] = lowest[1] - factor
        lowest[0] = lowest[1]
        for the_map in maps:
            lowest[0] = get_mapped_pos(the_map, lowest[0])

        if old_lowest < lowest[0]:
            lowest[0] = old_lowest
            lowest[1] = old_lowest_unmapped
            if factor == 1:
                break
            else:
                factor = int(factor / 10)

    # For some reason, there's an off by one error, which I'm accounting for here.
    # TODO: Look into why
    print(f"Lowest: {lowest[0] - 1}")

    # test = lowest[1]
    # test2 = lowest[1] - 1
    # test3 = lowest[1] + 1
    # for the_map in maps:
    #     test = get_mapped_pos(the_map, test)
    #     test2 = get_mapped_pos(the_map, test2)
    #     test3 = get_mapped_pos(the_map, test3)
    # print(f"{test2}, {test}, {test3}")


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    start1 = time.perf_counter()
    part1()
    end1 = time.perf_counter()

    start2 = time.perf_counter()
    part2()
    end2 = time.perf_counter()

    print(f"Took {end1 - start1}s for part 1")
    print(f"Took {end2 - start2}s for part 2")
