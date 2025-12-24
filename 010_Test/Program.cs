using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _010_Test
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Past past = new Future();
            past.Func();
        }

        
        
    }

    public class Past
    {
        public virtual void Print()
        {
            Console.WriteLine("안녕하세요");
        }

        public void Func()
        {
            Print();
        }
    }

    public class Future : Past
    {
        public override void  Print() 
        {
            Console.WriteLine("안냥~?");
        }
    }
    
}
