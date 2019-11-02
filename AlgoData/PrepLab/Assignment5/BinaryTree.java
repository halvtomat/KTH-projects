public class BinaryTree{
    Node head;

    private class Node{
        int key;
        Node left;
        Node right;
    }

    private void OtherNodes(Node root,Node newNode){
        if(newNode.key < root.key){
            if(root.left == null) root.left = newNode;
            else OtherNodes(root.left, newNode);  
        }
        else{
            if(root.right == null) root.right = newNode;
            else OtherNodes(root.right,newNode);
        }
    }

    public void Insert(int key){
        Node node = new Node();
        node.key = key;
        if(head == null){
            head = node;
        }
        else{
            OtherNodes(head,node);
        }
    }

    public String PrefixPrint(){
        String out = "";
        out = PrefixTraverse(out, head);
        return out;
    }
    public String InfixPrint(){
        String out = "";
        out = InfixTraverse(out, head);
        return out;
    }
    public String PostfixPrint(){
        String out = "";
        out = PostfixTraverse(out, head);
        return out;
    }
    private String PrefixTraverse(String out, Node root){
        if( root != null){
            out = out+root.key + " ";
            out = PrefixTraverse(out, root.left);
            out = PrefixTraverse(out, root.right);
        }
        return out;
    }
    private String InfixTraverse(String out, Node root){
        if( root != null){
            out = InfixTraverse(out, root.left);
            out = out+root.key + " ";
            out = InfixTraverse(out, root.right);
        }
        return out;
    }
    private String PostfixTraverse(String out, Node root){
        if( root != null){
            out = PostfixTraverse(out, root.left);
            out = PostfixTraverse(out, root.right);
            out = out+root.key + " ";
        }
        return out;
    }

    public Boolean Search(int key){
        Boolean found = false;
        found = SearchTree(head, key, found);
        return found;
    }
    private Boolean SearchTree(Node root, int key, Boolean found){
        if(root == null) found = false;
        else if(root.key == key) found = true;
        else if( root.key > key) found = SearchTree(root.left, key, found);
        else  found = SearchTree(root.right, key, found);
        return found;
    }
}