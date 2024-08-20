import random
import itertools

def generate_polynomial(degree):
    """Generate a random polynomial of a given degree."""
    poly = [random.choice([0, 1]) for _ in range(degree + 1)]
    poly[-1] = 1  # Ensure the highest degree coefficient is 1
    return poly

def hamming_weight(poly):
    """Calculate the Hamming weight of a polynomial."""
    return sum(poly)

def generate_polynomials(degree, count):
    """Generate a list of random polynomials of a given degree."""
    polynomials = []
    for _ in range(count):
        polynomials.append(generate_polynomial(degree))
    return polynomials

def calculate_parameters(data_length, error_bits, constraint_length, polynomials):
    """Calculate the code rate and other parameters given constraints."""
    num_polynomials = len(polynomials)
    code_rate = 1 / num_polynomials
    return code_rate

def main():
    data_length = 1024
    error_bits = 100
    constraint_length = 15
    num_polynomials = 4

    polynomials = generate_polynomials(constraint_length, num_polynomials)
    code_rate = calculate_parameters(data_length, error_bits, constraint_length, polynomials)

    print("Generated Polynomials:")
    for poly in polynomials:
        print(poly)
    
    print(f"Code Rate: {code_rate:.2f}")

if __name__ == "__main__":
    main()
