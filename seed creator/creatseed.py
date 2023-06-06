import struct

# Floating-point value to be used as a seed
values = [-0.0, 0.0, float('inf'), float('-inf'), float('nan')]

name = "a"
# Convert the floating-point value to binary representation and write as binary seeds
for value in values:
    binary_representation = struct.pack('!f', value)
    with open(name, 'wb') as file:
        file.write(binary_representation)
    name += "a"
