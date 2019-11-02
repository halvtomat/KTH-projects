import java.io.*;
import java.util.*;

public class Test{
    public static void main(String[] args) {
        BinaryTree binTree = new BinaryTree();

        binTree.Insert(17);
        binTree.Insert(4);
        binTree.Insert(65);
        binTree.Insert(45);
        binTree.Insert(1);
        binTree.Insert(15);
        System.out.print("Inserted numbers, 17, 4, 65, 45, 1, 15 \n");

        System.out.print("PrefixPrint "+binTree.PrefixPrint());
        if(binTree.PrefixPrint().equals("17 4 1 15 65 45 ")) System.out.print(" PASS \n");
        else System.out.print(" FAIL \n");

        System.out.print("InfixPrint "+binTree.InfixPrint());
        if(binTree.InfixPrint().equals("1 4 15 17 45 65 ")) System.out.print(" PASS \n");
        else System.out.print(" FAIL \n");

        System.out.print("PostfixPrint "+binTree.PostfixPrint());
        if(binTree.PostfixPrint().equals("1 15 4 45 65 17 ")) System.out.print(" PASS \n");
        else System.out.print(" FAIL \n");

        System.out.print("Searching for 45 ...");
        if(binTree.Search(45)) System.out.print(        "FOUND \n");
        else System.out.print(        "NOT FOUND \n");

        System.out.print("Searching for 99 ...");
        if(binTree.Search(99)) System.out.print(        "FOUND \n");
        else System.out.print(        "NOT FOUND \n");

        System.out.print("Searching for 14 ...");
        if(binTree.Search(14)) System.out.print(        "FOUND");
        else System.out.print(        "NOT FOUND");

    }
}