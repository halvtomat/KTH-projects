import java.util.Iterator;

/* Graph API
    addEdge adds an edge to the graph, takes two strings "labels" as arguments and returns void.
    hasConnection checks whether two vertexes in the graph has a connecting edge or not, takes two strings "labels" as argument and returns a boolean.
    DFS finds a path between two vertexes using DFS, takes two strings as argument, first is starting vertex, second is destination vertex.
    BFS finds a path between two vertexes using BFS, takes two strings as argument, first is starting vertex, second is destination vertex.
*/
public class DirectedGraph{
    int SIZE = 100;   

    DirectedGraph(int size){
        this.SIZE = size;
    }
    private class VertexList extends MyLinkedList<String>{}
    private MyLinkedList<String>[] connections = new VertexList[SIZE];

    public void addEdge(String v1,String v2){
        int vi = findVertex(v1);
        if(vi != -1 && connections[vi].hasNode(v2))return;
        if(vi == -1){
            addVertex(v1);
            vi = findVertex(v1);
        }
        connections[vi].insert(v2);  
        vi = findVertex(v2);    
        if(vi == -1){
            addVertex(v2);
            vi = findVertex(v2);
        }   
        //connections[vi].insert(v1);   
    }
    public boolean hasConnection(String v1, String v2){
        if(connections[findVertex(v1)].hasNode(v2)) return true;
        else return false;
    }
    private void addVertex(String v){
        for(int i = 0; i < SIZE; i++){
            if(connections[i]== null){
                connections[i] = new VertexList();
                connections[i].insert(v);
                break;
            }
        }
    }
    private boolean hasVertex(String v){
        for(int i = 0; i < SIZE;i++){
            if(connections[i]== null) break;
            if(connections[i].getHead().equals(v)) return true;
        }
        return false;
    }
    private int findVertex(String v){
        if(hasVertex(v) == false) return -1;
        for(int i = 0; i < SIZE; i++){
            if(connections[i].getHead().equals(v)) return i;
        }
        return -1;
    }
    public void DFS(String v, String d){
        ItemStack<String> is = new ItemStack<String>();
        boolean[] visited = new boolean[SIZE];
        DFS_Util(findVertex(v),findVertex(d), visited,is);
        String s = "";
        while(is.isEmpty() != true){
            s = is.Pop() +" "+ s;
        }
        System.out.print(s);
    }
    private void DFS_Util(int v,int d, boolean[] visited, ItemStack<String> is){
        visited[v] = true;
        is.Push(connections[v].getHead());

        Iterator<String> i = connections[v].iterator();
        while(i.hasNext()){
            int n = findVertex(i.next());
            if(n == d){
                is.Push(connections[d].getHead());
                return;
            }
            if(!visited[n]) DFS_Util(n, d, visited, is);
            if(is.Peek().equals(connections[d].getHead())) return;
        }
        is.Pop();
    }
    public void findCycle(String v){
        ItemStack<String> is = new ItemStack<String>();
        boolean[] visited = new boolean[SIZE];
        findCycle_Util(findVertex(v),findVertex(v), visited,is);
        String s = "";
        if(is.isEmpty()){ 
            System.out.print("No cycle found");
            return;
        }
        while(is.isEmpty() != true){
            s = is.Pop() +" "+ s;
        }
        System.out.print(v+" "+s);
    }
    private void findCycle_Util(int v,int d, boolean[] visited, ItemStack<String> is){
        visited[v] = true;
        if(v != d)is.Push(connections[v].getHead());
        Iterator<String> i = connections[v].iterator();
        for (int j = 0; j < connections[v].size();j++){
            String s = i.next();
            int n = findVertex(s);
            if(n == d && s != connections[v].getHead()){
                is.Push(connections[d].getHead());
                return;
            }
            if(!visited[n]) findCycle_Util(n, d, visited, is);
            if(is.Peek() == null)continue;
            if(is.Peek().equals(connections[d].getHead())) return;
        }
        if(v != d)is.Pop();
    }
    public void BFS(String v, String d){
        ItemStack<String> is = new ItemStack<String>();
        FIFOqueue<Integer> fq = new FIFOqueue<Integer>();
        boolean[] visited = new boolean[SIZE];
        BFS_Util(findVertex(v), findVertex(d),visited, fq, is);
        String s ="";
        while(is.isEmpty() != true){
            s =is.Pop()+ " "+ s;
        }
        System.out.print(s);
    }
    private void BFS_Util(int v, int d,boolean[] visited,FIFOqueue<Integer> fq,ItemStack<String> is){
        visited[v] = true;
        is.Push(connections[v].getHead());

        Iterator<String> i = connections[v].iterator();
        while(i.hasNext()){
            int n = findVertex(i.next());
            if(n == d){
                is.Push(connections[n].getHead());
                return;
            }
            if(!visited[n]){
                fq.Insert(n);
                visited[n] = true;
            }
        }
        Integer n = fq.Delete();
        if(n == null) return;
        BFS_Util(n.intValue(), d, visited, fq, is);
        //kolla alla grannar
        //om inte visited, lägg till i fq
        //gå vidare till nästa i kön
        //om d är funnet, return
    }
    public static void main(String[] args) {
        DirectedGraph g = new DirectedGraph(10);
        g.addEdge("a", "b");
        g.addEdge("b", "c");
        g.addEdge("c", "a");
        g.addEdge("c", "e");
        g.addEdge("e", "d");
        g.addEdge("d", "f");
        g.addEdge("d", "g");
        assert(!g.hasConnection("a", "c"));
        assert(g.hasConnection("b", "c"));
        assert(!g.hasConnection("e", "c"));
        assert(!g.hasConnection("f", "d"));
        assert(!g.hasConnection("g", "d"));
        assert(g.hasConnection("a", "b"));
        assert(g.hasConnection("e", "d"));
        assert(g.hasConnection("d", "g"));
        assert(!g.hasConnection("b", "a"));
        assert(!g.hasConnection("d", "e"));
        g.findCycle("a");
    }
}