import sys

try:
    with open('/home/edgar/Desktop/GNURadio_Simulations/Model_Generation/navigation_message.py', 'r') as f:
        print(f.read())
except Exception as e:
    print(e)
