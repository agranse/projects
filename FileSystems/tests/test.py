from subprocess import run, PIPE
import sys
import filecmp

# run create 129 times, return error when no more inodes available
def testCreateLimits():
    fileSystem = "tests/" + sys.argv[1]
    blocks = sys.argv[2]
    args = ("./simplefs", fileSystem, blocks)
    input = "create\n" * 130
    p = run(args, stdout=PIPE,input="format\nmount\n" + input + "exit\n", encoding='ascii')
    print(p.stdout)

# copy in image of cat, copy out image of cat, compare to same operations in provided solution
def testDiffs():
    fileSystem = sys.argv[1]
    blocks = sys.argv[2]

    # run our version on cat.png
    args = ("./simplefs", fileSystem, blocks);
    run(args, stdout=PIPE, input="format\nmount\ncreate\ncopyin cat.png 0\ncopyout 0 ./tests/simpleFSCat.png\nexit", encoding='ascii')

    # run provided solution on cat.png
    args = ("./simplefs-solution", fileSystem, blocks);
    run(args, stdout=PIPE, input="format\nmount\ncreate\ncopyin cat.png 1\ncopyout 1 ./tests/solutionCat.png\nexit", encoding='ascii')

    print("The SimpleFS-Solution file is equal to the SimpleFS file: ", end ="")
    if filecmp.cmp("./tests/simpleFSCat.png", "./tests/solutionCat.png"):
        print("\033[92m {}\033[00m" .format("True"))    
    else:
        print("\033[91m {}\033[00m" .format("False"))
    

if __name__ == "__main__":
    
    if sys.argv[3] == '1':
        testDiffs()
    else:
        testCreateLimits()
