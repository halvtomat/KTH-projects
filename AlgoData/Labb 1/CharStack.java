public class CharStack{
    private Node head;

    private class Node{
        char c;
        Node next;
    }

    /*  Push method adds another Node at the top of the charStack, the node contains a char.
        Push requires a char to be put in the new Node.*/
    public void Push(char c){
        Node node = new Node();
        node.c = c;
        if(head == null){
            node.next = null;
            head = node;
        } else{
            node.next = head;
            head = node;
        }
    }
    /*  Peek method returns the value of the head Node */
    public char Peek(){
        return head.c;
    }

    /*  Pop method removes the Node at the top of the charStack and returns the char of the Node.
        Pop has no input parameters.*/
    public char Pop(){
        Node n = head;
        head = n.next;
        return n.c;
    }
    /*  isEmpty method checks to see if there is a head Node in the charStack, if there isn't the charStack must be empty.
        Returns a boolean, false if the charStack contains a head Node and True if it doesn't. */
    public boolean isEmpty(){
        boolean empty = false;
        if(head == null) empty = true;
        return empty;
    }
    /* the main contains a number of tests to check that the charStack is working correctly. */
    public static void main(String[] args) {
        CharStack cs = new CharStack();

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