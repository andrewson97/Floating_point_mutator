import my_mutator_2 as cm
#import numpy as np

# random_float = np.float32(np.random.rand())
# print(random_float)
# cm.afl_custom_mutator()

import random
import struct
#import binascii
# Generate a random 32-bit integer
random_int = random.randint(0, (1 << 32) - 1)
print(random_int)
# Convert the integer to a float
x = struct.pack('I', random_int)
print("x",x)


print("input float", struct.unpack("f", x))

while True:

    x,m_l = cm.afl_custom_mutator(x)

    print("output float", struct.unpack("f" , x))
    print("l", m_l)


# print(bin(bits))

# random_float = struct.unpack('f', x)[0]
# print("r_f",random_float)

# y = struct.pack('f', random_float)
# print("y", y)

# # binary_string = binascii.hexlify(y)
# # print("b_s", binary_string)

# bits = struct.unpack('f', y)[0]
# print("bits", bits)

# z = struct.pack('f', bits)
# print("z", z)

# f = struct.unpack('f', z)[0]
# print("f",f)

#mantissa = bits & 0x7FFFFF
# Print the generated float
#
#print(x)

#

# print(bin(bits))
# #print(bin(mantissa))
# #print(mantissa)

# print(''.join([bin(byte)[2:].zfill(8) for byte in y]))







