import sys

while True:
    data = sys.stdin.readline().strip()
    if (data == "exit"): break

    print("Child received:", data)
    sys.stdout.flush()