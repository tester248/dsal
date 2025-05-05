def run():
    htable_linear = [None] * 10
    htable_quadratic = [None] * 10
    n = int(input("Enter number of Phone Numbers: "))
    for _ in range(n):
        key = int(input("Enter Mobile Number: "))
        position = key % 10
        if htable_linear[position] is None:
            htable_linear[position] = [key]
        else:
            htable_linear = linear_probe(key, htable_linear, position)
            print("Linear Probing for empty slot..")
        if htable_quadratic[position] is None:
            htable_quadratic[position] = [key]
        else:
            htable_quadratic = quadric_probe(key, htable_quadratic, position)
            print("Quadratic Probing for empty slot..")
        
        display(htable_linear, "Linear Probing")
        display(htable_quadratic, "Quadratic Probing")
    return htable_linear, htable_quadratic

def linear_probe(key, htable, pos):
    for i in range(1, 10):
        proble_position = (pos + i) % 10
        if htable[proble_position] is None:
            htable[proble_position] = [key]
            return htable
    print("Hash table is full")
    return htable

def quadric_probe(key, htable, pos):
    for i in range(1, 10):
        probe_position = (pos + i * i) % 10
        if htable[probe_position] is None:
            htable[probe_position] = [key]
            return htable
    print("Hash table is full")
    return htable

def display(htable, method):
    print(f"\n{method} Hash Table:")
    for pos in range(10):
        val = htable[pos]
        print(f"Position {pos}: {val}")

def search(key, ht, method):
    comparisons = 0
    pos = key % 10
    if ht[pos] is not None and ht[pos] == key:
        comparisons += 1
        return pos, comparisons
    for i in range(1, 10):
        comparisons += 1
        if method == "linear":
            probe_position = (pos + i) % 10
        else:
            if method == "quadratic":
                probe_position = (pos + i * i) % 10
        if ht[probe_position] is not None and ht[probe_position] == key:
            return probe_position, comparisons
    return -1, comparisons

def main():
    ht_linear, ht_quadratic = None, None
    while True:
        print("\nMenu:")
        print("1. Insert Phone Number")
        print("2. Search Phone Number")
        print("3. Exit")
        choice = int(input("Enter your choice: "))

        if choice == 1:
            if ht_linear is None and ht_quadratic is None:
                ht_linear, ht_quadratic = run()
            else:
                print("Phone numbers already inserted.")
        elif choice == 2:
            if ht_linear is None and ht_quadratic is None:
                print("No phone numbers to search.")
            else:
                key = int(input("Enter Mobile Number to search: "))
                pos, comparisons = search(key, ht_linear, "linear")
                if pos != -1:
                    print(f"Phone number {key} found at position {pos} in Linear Probing with {comparisons} comparisons.")
                else:
                    print(f"Phone number {key} not found in Linear Probing with {comparisons} comparisons.")

                pos, comparisons = search(key, ht_quadratic, "quadratic")
                if pos != -1:
                    print(f"Phone number {key} found at position {pos} in Quadratic Probing with {comparisons} comparisons.")
                else:
                    print(f"Phone number {key} not found in Quadratic Probing with {comparisons} comparisons.")
        elif choice == 3:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()



        

