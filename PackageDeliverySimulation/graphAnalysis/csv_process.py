def count_status(fname):
    fp = open(fname)
    packages = {}
    stolen_packages = []
    retrieved_packages = []
    theft_per_package = {}
    ends = {"D": 0, "S": 0, "R": 0}
    lines = fp.readlines()
    lines = lines[1:]
    fp.close()
    for line in lines:
        if "package" in line:
            print(line)
            line = line.split(",")
            packages[line[2]] = line[4]
            if line[4] == "Stolen\n":
                stolen_packages.append(line[2])
            if line[4] == "Retrieved\n":
                retrieved_packages.append(line[2])
            if line[-1] == "Stolen\n":
                if line[2] in theft_per_package:
                    theft_per_package[line[2]] += 1
                else:
                    theft_per_package[line[2]] = 1
    for package in packages:
        if packages[package] == "Delivered\n":
            ends["D"] += 1
        if packages[package] == "Stolen\n":
            ends["S"] += 1
        if packages[package] == "Retrieved\n":
            ends["R"] += 1
    print(ends)
    print(stolen_packages)
    print(retrieved_packages)



if __name__ == "__main__":
    count_status("astarStratData.csv")



