using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace _008_Test
{
    internal class Program
    {
        static void Main(string[] args)
        {

            int[] numbers = { 1, 2, 3, 4, 5 };
            List<int> newNumbers = numbers.Where(n => n > 3).ToList();
            foreach (int n in newNumbers)
            {
                Console.WriteLine(n);
            }

            List<int> nn = new List<int> {1,2,3,4 };
            Console.WriteLine(nn.Where(n => n % 2 == 0).Sum());

            var newList = new List<int> { 1, 2, 3, 4 };
            Console.WriteLine(newList.Where(n=>n%2 ==1).Sum());

            int[] arr = { 1, 2, 3, 4, 5 };
            IEnumerable<int> t = arr.Where(a => a % 2 == 1);
            foreach(var n in t)
            { Console.Write(n); }

            bool[] blns = { true, false, true, false , true};

            Console.WriteLine(blns.Length);
            Console.WriteLine(blns.Count());
            Console.WriteLine(blns.Count(b=>b == true));
            Console.WriteLine(blns.Count(b => b == false)                                               );

        }

    }
}
