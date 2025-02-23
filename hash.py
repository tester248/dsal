def run():
    hashtable_linear = [None] * 10
    hashtable_quadratic = [None] * 10
    n = int(input("Enter number of Phone Numbers: "))
    for _ in range(n):
        key = int(input("Enter Mobile Number: "))
        position = key % 10
        if hashtable_linear[position] is None:
            hashtable_linear[position] = [key]
        else:
            hashtable_linear = linearProbe(key, hashtable_linear, position)
            print("Linear Probing for empty slot..")
        if hashtable_quadratic[position] is None:
            hashtable_quadratic[position] = [key]
        else:
            hashtable_quadratic = quadraticProbe(key, hashtable_quadratic, position)
            print("Quadratic Probing for empty slot..")
        display(hashtable_linear, "Linear Probing")
        display(hashtable_quadratic, "Quadratic Probing")
    return hashtable_linear, hashtable_quadratic

def linearProbe(key, ht, pos):
    i = 1
    while i < 10:
        probe_position = (pos + i) % 10
        if ht[probe_position] is None:
            ht[probe_position] = [key]
            return ht
        i += 1
    print("Hash table is full")
    return ht

def quadraticProbe(key, ht, pos):
    i = 1
    while i < 10:
        probe_position = (pos + i * i) % 10
        if ht[probe_position] is None:
            ht[probe_position] = [key]
            return ht
        i += 1
    print("Hash table is full")
    return ht

def display(ht, method):
    print(f"\n{method} Hash Table:")
    for pos in range(10):
        val = ht[pos]
        print(f"Position {pos}: {val}")

def search(key, ht, method):
    comparisons = 0
    pos = key % 10
    if ht[pos] is not None and ht[pos][0] == key:
        comparisons += 1
        return pos, comparisons
    i = 1
    while i < 10:
        comparisons += 1
        if method == "linear":
            probe_position = (pos + i) % 10
        else:
            probe_position = (pos + i * i) % 10
        if ht[probe_position] is not None and ht[probe_position][0] == key:
            return probe_position, comparisons
        i += 1
    return -1, comparisons

def main():
    ht_linear, ht_quadratic = None, None
    while True:
        print("\nMenu:")
        print("1. Insert Phone Numbers")
        print("2. Search Phone Number")
        print("3. Exit")
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            ht_linear, ht_quadratic = run()
        elif choice == 2:
            if ht_linear is None or ht_quadratic is None:
                print("Please insert phone numbers first.")
            else:
                key = int(input("\nEnter Phone Number to search: "))
                pos_linear, comparisons_linear = search(key, ht_linear, "linear")
                pos_quadratic, comparisons_quadratic = search(key, ht_quadratic, "quadratic")
                if pos_linear != -1:
                    print(f"Linear Probing: Phone Number found at position {pos_linear} with {comparisons_linear} comparisons.")
                else:
                    print("Linear Probing: Phone Number not found.")
                if pos_quadratic != -1:
                    print(f"Quadratic Probing: Phone Number found at position {pos_quadratic} with {comparisons_quadratic} comparisons.")
                else:
                    print("Quadratic Probing: Phone Number not found.")
        elif choice == 3:
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()