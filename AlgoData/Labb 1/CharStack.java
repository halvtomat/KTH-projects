public class ItemStack<Item>{
    private Node head;

    private class Node{
        Item item;
        Node next;
    }

    /*  Push method adds another Node at the top of the ItemStack, the node contains a Item.
        Push requires a Item to be put in the new Node.*/
    public void Push(Item item){
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
    /*  Peek method returns the value of the head Node */
    public Item Peek(){
        return head.item;
    }

    /*  Pop method removes the Node at the top of the ItemStack and returns the item of the Node.
        Pop has no input parameters.*/
    public Item Pop(){
        Node n = head;
        head = n.next;
        return n.item;
    }
    /*  isEmpty method checks to see if there is a head Node in the ItemStack, if there isn't the ItemStack must be empty.
        Returns a boolean, false if the ItemStack contains a head Node and True if it doesn't. */
    public boolean isEmpty(){
        boolean empty = false;
        if(head == null) empty = true;
        return empty;
    }
    /* the main contains a number of tests to check that the ItemStack is working correctly. */
    public static void main(String[] args) {
        ItemStack cs = new ItemStack();

        assert cs.isEmpty();

        cs.Push('a');
        assert !cs.isEmpty();
        assert ('a' == cs.Pop());
        assert cs.isEmpty();

        cs.Push('1');
        cs.Push('k');
        cs.Push(',');
        cs.Push('+');
        cs.Push('\n');
        assert !cs.isEmpty();
        assert ('\n' == cs.Pop());
        assert ('+' == cs.Pop());
        assert (',' == cs.Pop());
        assert ('k' == cs.Pop());
        assert ('1' == cs.Pop());
        assert cs.isEmpty();
    }
}