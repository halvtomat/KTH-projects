import java.io.*;
import java.util.*;

public class DoubleLinkList{
    Node head;

    private class Node{
        int item;
        Node next;
        Node prev;
    }

    public void Insert(int item){
        Node node = new Node();
        node.item = item;
        if(head == null){
            node.next = node;
            node.prev = node;
            head = node;
        } else if(head.next == head){
            head.next = node;
            head.prev = node;
            node.next = head;
            node.prev = head;
            head = node;
        } else {
           node.prev = head.prev;
           node.next = head;
           head.prev.next = node;
           head.prev = node;
           head = node; 
        }
    }
    public int Pop(){
        Node n = head;
        n.next.prev = n.prev;
        n.prev.next = n.next;
        head = n.next;
        return n.item;
    }
    public int Size(){
        int size = 0;
        if(head == null) return size;
        else size++;
        Node n = head;

        while(n.next != head){
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
        }while(n.next != head);

        return out;
    }
}