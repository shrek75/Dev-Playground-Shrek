using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int i = 2_147_418_113;
            char c = (char)i;

            Console.WriteLine((int)c);
        }
    }
}
