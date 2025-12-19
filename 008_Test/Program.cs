using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _008_Test
{
    internal class Program
    {
        static void Main(string[] args)
        {

            int[] arr = { 3, 2, 1, 4, 5 };
            Array.Sort(arr);

            foreach(int i in arr)
            {
                Console.Write($"{i} ");
            }
        }

    }
}
