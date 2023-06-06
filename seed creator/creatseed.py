import struct

# Floating-point value to be used as a seed
value = -0.0

# Convert the floating-point value to binary representation
binary_representation = struct.pack('!f', value)
#binary_representation = value


# Write the binary representation to a seed file
with open('nz.bin', 'wb') as file:
    file.write(binary_representation)