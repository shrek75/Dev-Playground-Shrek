

public class MatrixGraph
{
    private readonly bool[,] matrix;

    private int _vertextCount;

    public MatrixGraph(int vertextCount)
    {
        _vertextCount = vertextCount;
        matrix = new bool[vertextCount, vertextCount];
    }

    public void AddEdge(int from, int to)
    {
        matrix[from, to] = true;
        matrix[to, from] = true;
    }

    public bool HasEdge(int from, int to) => matrix[from, to];

    //public List<int> BFS(int start)
    //{
    //}
    //
    //public List<int> DFS(int start)
    //{
    //}

}