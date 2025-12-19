using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace _008_Test
{
    internal class Program
    {
        static void Main(string[] args)
        {

            Stack myStack = new Stack();
            myStack.Push(1);
            myStack.Push(2);

            Console.WriteLine(myStack.Peek());
            Console.WriteLine(myStack.Pop());
            Console.WriteLine(myStack.Pop());
        }

    }
}
