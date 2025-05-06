class setBuilder:
    def __init__(self):
         self.set = set()
    
    def addElements(self):
        n = int(input("No. of elements to insert: "))
        for i in range(n):
            element = input(f"Enter element {i}: ")
            if element not in self.set:
                self.set.add(element)

    def removeElement(self,element):
         self.set.remove(element)
    
    def setUnion(self, s2):
        unionSet = set()
        unionSet = self.set.copy()
        for element in s2.set:
            if element not in self.set:
                unionSet.add(element)
        return unionSet

    def setIntersection(self, set2):
        intersectionSet = set()
        for element in self.set:
            if element in set2.set:
                intersectionSet.add(element)
        return intersectionSet  
    
    def setDifference(self, set2):
        differenceSet = set()
        for element in self.set:
            if element not in set2.set:
                differenceSet.add(element)
        return differenceSet
    
    def checkMembership(self, ch):
        element = input("Enter element to check: ")
        if element in self.set:
            print(f"{element} is present in Set{ch}")
        else:
            print(f"{element} is not present in Set{ch}")

def main():
     set1 = setBuilder()
     set2 = setBuilder()
     while True:
        print("**SET OPERATIONS**")
        print("1. Insert elements")
        print("2. Remove element")
        print("3. Display both sets")
        print("4. Find union of set 1 and set 2")
        print("5. Set Intersection")
        print("6. Set Difference")
        print("7. Check membership")
        print("8. Exit")
        choice = input("Enter your choice: ")
        if choice == '1':
            ch = input("Insert elements in Set '1' or Set '2'?")
            if ch == '1':
                print("Enter data for Set1")
                set1.addElements()
            elif ch == '2':
                print("Enter data for Set2")
                set2.addElements()
        elif choice == '2':
            ch = input("Remove element from  Set '1' or Set '2'?")
            if ch == '1':
                ele = input("Enter element to remove: ")
                set1.removeElement(ele)
            elif ch == '2':
                ele = input("Enter element to remove: ")
                set2.removeElement(ele)
        elif choice == '3':
            print("Set 1: ", set1.set)
            print("Set 2: ", set2.set)
        elif choice == '4':
            print("Set 1: ", set1.set)
            print("Set 2: ", set2.set)
            unionSet = set1.setUnion(set2)
            print("Union of Set1 and Set2: " , unionSet)
        elif choice == '5':
            print("Set 1: ", set1.set)
            print("Set 2: ", set2.set)
            iSet = set1.setIntersection(set2)
            print("Intersection of Set1 and Set2: ", iSet)
        elif choice == '6':
            print("Set 1: ", set1.set)
            print("Set 2: ", set2.set)
            dSet = set1.setDifference(set2)
            print("Difference of Set1 and Set2: ", dSet)
        elif choice == '7':
            ch = input("Check membership in Set '1' or Set '2'?")
            if ch == '1':
                set1.checkMembership(ch)
            elif ch == '2':
                set2.checkMembership(ch)
        elif choice == '8':
            break
        else:
            print("Invalid choice. Please try again...")


if __name__ == "__main__":
     main()

