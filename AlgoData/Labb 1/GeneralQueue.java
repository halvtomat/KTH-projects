public class GeneralQueue<Item>{
    private Node head;

    private class Node{
        Item item;
        Node next;
    }
    /*Insert method inserts a new Node at the top of the queue and prints the whole queue*/
    public void Insert(Item item){
        Node node = new Node();
        node.item = item;
        if(head == null){
            head = node;
        } else if(head.next == head){
            head.next = node;
            node.next = head;
            head = node;
        } else {
           node.next = head;
           head = node;
        }
        System.out.print(Print());
    }
    /*RemoveAt method removes Node at the specified index in the queue and returns the item of the that Node, also prints the whole queue*/
    public Item RemoveAt(int index){
        Node n = head;
        if(index == 1){
            head = n.next;
        }
        else{
            for(int i = 1; i < index-1; i++){
               n = n.next;
            }
            Node m = n;
            n = n.next;
            m.next = n.next;
        }
        n.next = null;
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
        GeneralQueue<Integer> q = new GeneralQueue<Integer>();

        q.Insert(1);
        q.Insert(5);
        q.Insert(993);
        q.Insert(756);
        q.Insert(53);
        q.Insert(79542);
        assert (5 == q.RemoveAt(5));
        assert (756 == q.RemoveAt(3));
        assert (1 == q.RemoveAt(4));
        assert (79542 == q.RemoveAt(1));
        assert (993 == q.RemoveAt(2));
        assert (53 == q.RemoveAt(1));
        q = null;
    }
}