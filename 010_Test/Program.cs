using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Collections.Concurrent;


public class Program
{
    static void Main(string[] args)
    {
        int[,] maps = new int[,] { { 1, 0, 1, 1, 1 }, { 1, 0, 1, 0, 1 }, { 1, 0, 1, 1, 1 }, { 1, 1, 1, 0, 1 }, { 0, 0, 0, 0, 1 } };
        int a = Solution.solution(maps);
        Console.WriteLine(a);
    }
}

static class Solution
{
    public static int solution(int[,] maps)
    {
        Node[,] myArr = new Node[maps.GetLength(0),maps.GetLength(1)];
        for(int y = 0; y< maps.GetLength(0); y++)
        {
            for(int x = 0; x< maps.GetLength(1); x++)
            {
                myArr[y, x] = new Node();
                myArr[y,x].wall = maps[y,x];
                myArr[y, x].x = x;
                myArr[y, x].y = y;
            }
        }

        Queue<Node> stack = new Queue<Node>();
        stack.Enqueue(myArr[0,0]);
        while(stack.Count>0)
        {
            Node node = stack.Dequeue();

            //목적지 찾았으면
            if(node == myArr[myArr.GetLength(0) -1 ,myArr.GetLength(1) - 1]  )
            {
                return node.length +1;
            }

            // 못찾았으면 인접노드들 push
            int targetX = node.x - 1;
            int targetY = node.y;

            if(targetX >= 0)
            {
                if (myArr[targetY,targetX].wall == 1 && myArr[targetY, targetX].length == 0)
                {
                    myArr[targetY, targetX].length = myArr[node.y, node.x].length + 1;
                    stack.Enqueue(myArr[targetY,targetX]);
                }
            }

            targetX = node.x + 1;
            targetY = node.y;

            if (targetX <= myArr.GetLength(1) - 1)
            {
                if (myArr[targetY, targetX].wall == 1 && myArr[targetY, targetX].length == 0)
                {
                    myArr[targetY, targetX].length = myArr[node.y, node.x].length + 1;
                    stack.Enqueue(myArr[targetY, targetX]);

                }
            }


            targetX = node.x;
            targetY = node.y - 1;

            if (targetY >= 0)
            {
                if (myArr[targetY, targetX].wall == 1 && myArr[targetY, targetX].length == 0)
                {
                    myArr[targetY, targetX].length = myArr[node.y, node.x].length + 1;
                    stack.Enqueue(myArr[targetY, targetX]);

                }
            }

            targetX = node.x;
            targetY = node.y + 1;

            if (targetY <= myArr.GetLength(0) - 1)
            {
                if (myArr[targetY, targetX].wall == 1 && myArr[targetY, targetX].length == 0)
                {
                    myArr[targetY, targetX].length = myArr[node.y, node.x].length + 1;
                    stack.Enqueue(myArr[targetY, targetX]);

                }
            }

        }

        return -1;
    }

    class Node
    {
        public int x;
        public int y;
        public int wall;
        public int length = 0;
    }
}
