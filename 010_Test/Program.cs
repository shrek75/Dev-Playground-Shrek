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

        List<int> test = new List<int>() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        foreach (int i in test)
        {
            test.Add(i + 10);
            Console.Write($"{i}\t");
        }


    }


}

