public class OrderedQueue{
    private Node head;

    private class Node{
        int item;
        Node next;
    }
    /*Insert method inserts a new Node in the correct order of the queue and prints the whole queue*/
    public void Insert(int item){
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
    /*Remove method removes the top Node in the queue and returns the item of the that Node, also prints the whole queue*/
    public int Remove(){
        Node n = head;
        if(n.next == null) head = null;
        else head = n.next;
        System.out.print(Print());
        return n.item;
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
        OrderedQueue q = new OrderedQueue();

        q.Insert(5);
        q.Insert(1);
        q.Insert(993);
        q.Insert(756);
        q.Insert(53);
        q.Insert(79542);
        assert (1 == q.Remove());
        assert (5 == q.Remove());
        assert (53 == q.Remove());
        assert (756 == q.Remove());
        assert (993 == q.Remove());
        assert (79542 == q.Remove());
        q = null;
    }
}