import java.util.Iterator;
import java.io.*;

public class MyLinkedList<Item> implements Iterable<Item>{
    private Node head;

    private class Node{
        Item item;
        Node next;
    }
    /*Insert method inserts a new Node at the end of the queue*/
    public void insert(Item item){
        Node node = new Node();
        node.item = item;
        if(head == null){
            node.next = null;
            head = node;
        } else {
            Node last = head;
            while(last.next != null){
                last = last.next;
            }
            node.next = null;
            last.next = node; 
        }
        
    }
    public boolean empty(){
        if(head != null) return true;
        else return false;
    }
    public Item getHead(){
        return head.item;
    }
    public boolean hasNode(Item item){
        Node n = head;
        do{
            if(n.item.equals(item)) return true;
            n = n.next;
        }while(n != null);
        return false;
    }
    /*Print method prints the whole queue*/
    public String print(){
        String out = "";
        if(head == null){
            return out;
        }
        Node n = head;
        out = n.item + " ";
        while(n.next != null){
            n = n.next;
            out = out + n.item + " ";
        }

        return out+"\n";
    }
    public int size(){
        int size = 0;
        Node n = head;
        while(n != null){
            size++;
            n = n.next;
        }
        return size;
    }
    /*Iterator implementation copied from book*/
    public Iterator<Item> iterator(){ return new ListIterator();}

    private class ListIterator implements Iterator<Item>{
        private Node current = head;

        public boolean hasNext() { return current.next != null;}
        public Item next(){
            Item item = current.item;
            current = current.next;
            return item;
        }
    }
}