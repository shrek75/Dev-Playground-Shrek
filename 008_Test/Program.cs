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

        static IEnumerable<int> FindNumbers(Predicate<int> predicate)
        {
            for(int i= 0; i < 100; i++)
            {
                if (predicate(i)) yield return i;
            }
        }

        static void Main(string[] args)
        {
           var Numbers = FindNumbers((int i) => i % 33 == 0 );
           foreach(int i in Numbers)
                Console.WriteLine(i);
        }
        
        
        
    }
    
    
}
