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
    bits = struct.unpack('I', data)[0]
    mantissa = bits & 0x7FFFFF  # to seperate the 23 mantissa bits
    exponent = (bits >> 23) & 0xFF  #to seperate the 8 exponent bits



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
    perform_mutation = cases[selected_case_name]

    if ("m" in selected_case_name):
        mantissa = perform_mutation(mantissa, bits)

    if ("e" in selected_case_name):
        exponent = perform_mutation(exponent, bits)

    if ( selected_case_name == "flip_s"):
        bits = perform_mutation(bits)
        print("new bits" , bits)

    

    new_bits = (bits & 0x80000000) | (exponent << 23) | mantissa
    new_data = struct.pack('I', new_bits)

    mantissa = new_bits & 0x7FFFFF  # to seperate the 23 mantissa bits
    exponent = (new_bits >> 23) & 0xFF  #to seperate the 8 exponent bits


    if struct.unpack('f', new_data)[0] != struct.unpack('f', new_data)[0]:
        new_data = struct.pack('f', 0.0)

    return (new_data)


# test

# def test():
#     print("test")
    
# to flip the sign bit
def flip_s(bits):
    mask = 1 << 31
    new_bits = bits ^ mask
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
    random_int = random.randint(1, 32)
    new_exponent = exponent + random_int
    return new_exponent

def add_m(mantissa, bits):
    random_int = random.randint(1, 32)
    new_mantissa = mantissa + random_int
    return new_mantissa

def sub_e(exponent, bits):
    random_int = random.randint(1, 32)
    new_exponent = abs(exponent - random_int)
    return new_exponent

def sub_m(mantissa, bits):
    random_int = random.randint(1, 32)
    new_mantissa = abs(mantissa - random_int)
    return new_mantissa
    

