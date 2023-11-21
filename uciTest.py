import sys

while True:
    data = sys.stdin.readline().strip()
    print("Child received:", data)
    sys.stdout.flush()
