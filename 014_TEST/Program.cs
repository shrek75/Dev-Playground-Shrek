using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _014_TEST
{
    internal class Program
    {
        static void Main(string[] args)
        {
            myClass[] coll = new myClass[3]
            {
                new myClass(),
                new myClass(),
                new myClass()
            };

            
            UseCollection(coll);
        }

        public static void UseCollection (System.Collections.IEnumerable theCollection)
        {
            foreach (Ma t in theCollection)
            {
                
            }
        }

    }

    public class myClass
    {
        const int a = 1;

        readonly DateTime d = new DateTime();

        readonly int b;
        //myClass(int value)
        //{
        //    b = value;
        //    
        //}

        public void Foo()
        {
            Console.WriteLine("afds");
        }
        public static implicit operator Ma(myClass m)
        { return new Ma(); }
    }

    public class Ma
    {
        public static void MyFunc(string s)
        {
            System.Console.WriteLine(s); 
        }

        
    }

    
}


