import java.util.Scanner;

public class Test{
    
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        DirectedGraph graph = new DirectedGraph(100);
        while(scanner.hasNext()){
            String v1 = scanner.next();
            String v2 = scanner.next();
            graph.addEdge(v1, v2);
        }
        scanner.close();
        graph.findCycle(args[0]);
    }
}