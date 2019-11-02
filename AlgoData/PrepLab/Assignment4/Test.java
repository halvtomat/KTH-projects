import java.io.*;

public class Test{
    public static void main(String[] args) {
        int numberoftestspassed = 0;
        LinkList list = new LinkList();

        list.Insert(7);
        System.out.print("Inserting 7 \n");
        list.Insert(3);
        System.out.print("Inserting 3 \n");
        list.Insert(15);
        System.out.print("Inserting 15 \n");
        list.Insert(4);
        System.out.print("Inserting 4 \n");

        System.out.print(list.Print() + "\n");
        if(list.Print().equals("4 15 3 7 ")){
            System.out.print("Insert and Print methods PASS \n");
            numberoftestspassed++;
        } else System.out.print("Insert and Print methods FAIL \n");

        list.InsertAt(99,3);
        System.out.print("Inserting item 99 at index 3 \n");

        System.out.print(list.Print() + "\n");
        if(list.Print().equals("4 15 3 99 7 ")){
            System.out.print("InsertAt method PASS \n");
            numberoftestspassed++;
        } else System.out.print("InsertAt method FAIL \n");

        System.out.print("Popping \n");
        int popped = list.Pop();
        
        System.out.print(popped + "\n");
        if(list.Print().equals("15 3 99 7 ")){
            System.out.print("Pop method PASS \n");
            numberoftestspassed++;
        } else System.out.print("Pop method FAIL \n");

        System.out.print("Size of list = " +list.Size() + "\n");
        if(list.Size() == 4){
            System.out.print("Size method PASS \n");
            numberoftestspassed++;
        } else System.out.print("Size method FAIL \n");

//______________________________________________________________________________________
// Double linked List test below

        DoubleLinkList doblist = new DoubleLinkList();

        doblist.Insert(7);
        System.out.print("Inserting 7 \n");
        doblist.Insert(3);
        System.out.print("Inserting 3 \n");
        doblist.Insert(15);
        System.out.print("Inserting 15 \n");
        doblist.Insert(4);
        System.out.print("Inserting 4 \n");

        System.out.print(doblist.Print() + "\n");
        if(doblist.Print().equals("4 15 3 7 ")){
            System.out.print("Insert and Print methods PASS \n");
            numberoftestspassed++;
        } else System.out.print("Insert and Print methods FAIL \n");

        System.out.print("Popping \n");
        popped = doblist.Pop();
        
        System.out.print(popped + "\n");
        if(doblist.Print().equals("15 3 7 ")){
            System.out.print("Pop method PASS \n");
            numberoftestspassed++;
        } else System.out.print("Pop method FAIL \n");

        System.out.print("Size of list = " +doblist.Size() + "\n");
        if(doblist.Size() == 3){
            System.out.print("Size method PASS \n");
            numberoftestspassed++;
        } else System.out.print("Size method FAIL \n");

//______________________________________________________________________________________
// Binary Tree test below

        BinaryTree binTree = new BinaryTree();

        binTree.Insert(17);
        binTree.Insert(4);
        binTree.Insert(65);
        binTree.Insert(45);
        binTree.Insert(1);
        binTree.Insert(15);
        System.out.print("Inserted numbers, 17, 4, 65, 45, 1, 15 \n");

        System.out.print("PrefixPrint "+binTree.PrefixPrint());
        if(binTree.PrefixPrint().equals("17 4 1 15 65 45 ")){
            System.out.print(" PASS \n");
            numberoftestspassed++;
        }else System.out.print(" FAIL \n");

        System.out.print("InfixPrint "+binTree.InfixPrint());
        if(binTree.InfixPrint().equals("1 4 15 17 45 65 ")){
            System.out.print(" PASS \n");
            numberoftestspassed++;
        }else System.out.print(" FAIL \n");

        System.out.print("PostfixPrint "+binTree.PostfixPrint());
        if(binTree.PostfixPrint().equals("1 15 4 45 65 17 ")){ 
            System.out.print(" PASS \n");
            numberoftestspassed++;
        }else System.out.print(" FAIL \n");

        System.out.print("Searching for 45 ...");
        if(binTree.Search(45)){
        System.out.print(        "FOUND \n");
        numberoftestspassed++;
        }else System.out.print(        "NOT FOUND \n");
        
        System.out.print("Searching for 99 ...");
        if(binTree.Search(99)) System.out.print(        "FOUND \n");
        else{
        System.out.print(        "NOT FOUND \n");
        numberoftestspassed++;
        }

        System.out.print("Searching for 14 ...");
        if(binTree.Search(14)) System.out.print(        "FOUND");
        else{
        System.out.print(        "NOT FOUND");
        numberoftestspassed++;
        }

        System.out.print("\n\n\n"+ numberoftestspassed + "/13 tests PASSED");
        if(numberoftestspassed == 13) System.out.print(" Congratulations");
    }
}