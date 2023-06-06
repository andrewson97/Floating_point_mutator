import random
import struct


def fuzz(buf, add_buf, max_size):

    mutated_out = afl_float_mutator_32(buf,add_buf,max_size)


    return mutated_out


def init(seed):
    """
    Called once when AFLFuzz starts up. Used to seed our RNG.

    @type seed: int
    @param seed: A 32-bit random value
    """
    random_int = random.randint(0, (1 << 32) - 1)
    x = struct.pack('I', random_int)
    #print("initial seed" , seed)

    random.seed(x)


def deinit():
    pass

def afl_float_mutator_32(data,add_buff,maz_size):
    #print("lendata" , len(data), "type", type(data))
    # to Get the exponent and mantissa bits from the input data
    #bits = struct.unpack('f', data)[0] 
    bits = struct.unpack('I', data)[0]
    #print("bis", struct.pack("f", bits))
    mantissa = bits & 0x7FFFFF  # to seperate the 23 mantissa bits
    exponent = (bits >> 23) & 0xFF  #to seperate the 8 exponent bits
    # print("ex" , bin(exponent) , "msa", bin(mantissa), "bits" , bin(bits))
    # print("ex" , exponent , "msa", mantissa, "bits" , bits)
    #print("1")



    cases = { 
        "flip_m": flip_m,
        "flip_e": flip_e,
        "flip_s": flip_s,
        "add_e": add_e,
        "add_m": add_m,
        "sub_m": sub_m,
        "sub_e": sub_e
    }

    selected_case_name = random.choice(list(cases.keys()))
    #print(selected_case_name)
    perform_mutation = cases[selected_case_name]

    if ("m" in selected_case_name):
        mantissa = perform_mutation(mantissa, bits)
        #print("new mant", mantissa)

    if ("e" in selected_case_name):
        exponent = perform_mutation(exponent, bits)
        #print("new ex", exponent)

    if ( selected_case_name == "flip_s"):
        bits = perform_mutation(bits)
        #print("new bits" , bits)

    
    # to store the new bits into a floating point value
    #print("nn", bin(bits), "nn", bin(bits & 0x80000000))
    new_bits = (bits & 0x80000000) | (exponent << 23) | mantissa
    #print("len", len(bin(new_bits)))
    new_data = struct.pack('I', new_bits)
    #print("new bits", new_bits, "new_data", new_data)

    #mantissa = new_bits & 0x7FFFFF  # to seperate the 23 mantissa bits
    #exponent = (new_bits >> 23) & 0xFF  #to seperate the 8 exponent bits
    #print("new__  ex" , bin(exponent) , "msa", bin(mantissa), "bits" , bin(bits))
    #print("new__  ex" , exponent , "msa", mantissa, "bits" , new_bits)

    # Check for NaN values and replace with 0
    if struct.unpack('f', new_data)[0] != struct.unpack('f', new_data)[0]:
        new_data = struct.pack('f', 0.0)

    # Return the mutated data and size
    #print("newdata" ,new_data)
    #print("mutation happned and output is:", new_data)
    return (new_data)


# test

# def test():
#     print("test")
    
# to flip the sign bit
def flip_s(bits):
    #print("flip_ssss" , bits)
    mask = 1 << 31
    #print("mask", mask)
    new_bits = bits ^ mask
    #print("flip_sss", new_bits)
    return new_bits


#to Flip a random bit in the exponent and mantissa
def flip_e(exponent, bits):
    exponent_bit = 1 << random.randint(0, 7)
    exponent ^= exponent_bit
    return exponent

def flip_m(mantissa, bits):
    mantissa_bit = 1 << random.randint(0, 22)
    mantissa ^= mantissa_bit
    return mantissa


def add_e(exponent, bits):
    #exponent_as_int = int(''.join(map(str, exponent)), 2)
    random_int = random.randint(1, 32)
    new_exponent = exponent + random_int
    #exponent_bit = tuple(map(int, bin(new_exponent_as_int)[2:].zfill(len(bits))))
    #print(new_exponent, "printing now")
    return new_exponent

def add_m(mantissa, bits):
    #mantissa_as_int = int(''.join(map(str, mantissa)), 2)
    random_int = random.randint(1, 32)
    new_mantissa = mantissa + random_int
    #mantissa_bit = tuple(map(int, bin(new_mantissa_as_int)[2:].zfill(len(bits))))
    return new_mantissa

def sub_e(exponent, bits):
    #exponent_as_int = int(''.join(map(str, exponent)), 2)
    random_int = random.randint(1, 32)
    new_exponent = abs(exponent - random_int)
    #exponent_bit = tuple(map(int, bin(new_exponent)[2:].zfill(len(bits))))
    return new_exponent

def sub_m(mantissa, bits):
    #mantissa_as_int = int(''.join(map(str, mantissa)), 2)
    random_int = random.randint(1, 32)
    new_mantissa = abs(mantissa - random_int)
    #mantissa_bit = tuple(map(int, bin(new_mantissa_as_int)[2:].zfill(len(bits))))
    return new_mantissa