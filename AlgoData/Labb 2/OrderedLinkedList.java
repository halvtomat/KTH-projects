public class OrderedLinkedList{
    private Node head;

    private class Node{
        int item;
        Node next;
    }
    /*Insert method inserts a new Node in the correct order of the queue and prints the whole queue*/
    public void Enqueue(int item){
        Node n = new Node();
        n.item = item;
        if(head == null) head = n;
        else if(head.next == null){
            if(head.item > n.item){
                n.next = head;
                head = n;
            }else head.next = n;
        }
        else{
            Node m = head;
            m = FindPlace(n, m);
            n.next = m.next;
            m.next = n;
        }
        System.out.print(Print());
    }
    /*Recursive method to find the right place for the new Node */
    private Node FindPlace(Node n, Node m){
        if(n.item > m.item && m.next != null && n.item > m.next.item) m = FindPlace(n,m.next);
        return m;
    }
    /*Print method prints the whole queue*/
    public String Print(){
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
    public static void main(String[] args) {
        OrderedLinkedList q = new OrderedLinkedList();

        q.Enqueue(5);
        q.Enqueue(1);
        q.Enqueue(993);
        q.Enqueue(756);
        q.Enqueue(53);
        q.Enqueue(79542);
        q = null;
    }
}