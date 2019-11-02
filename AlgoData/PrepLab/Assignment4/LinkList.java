import java.io.*;
import java.util.*;

public class LinkList{
    Node head;

    private class Node{
        int item;
        Node next;
    }

    public void Insert(int item){
        Node node = new Node();
        node.item = item;
        if(head == null){
            node.next = null;
            head = node;
        } else{
            node.next = head;
            head = node;
        }
    }
    public void InsertAt(int item, int index){
        Node node = new Node();
        node.item = item;
        if(head == null){
            head = node;
            return;
        }

        Node n = head;
        for(int i = 1; i < index; i++){
            if (n.next == null){
                break;
            }
            n = n.next;
        }
        Node n2 = n.next;
        node.next = n2;
        n.next = node;
    }
    public int Pop(){
        Node n = head;
        head = n.next;
        return n.item;
    }
    public int Size(){
        int size = 0;
        if(head == null) return size;
        else size++;
        Node n = head;

        while(n.next != null){
            size++;
            n = n.next;
        }
        return size;
    }
    public String Print(){
        String out = "";
        if(head == null){
            return out;
        }
        Node n = head;
        out = n.item + " ";
        do{
            n = n.next;
            out = out + n.item + " ";
        }while(n.next != null);

        return out;
    }
}