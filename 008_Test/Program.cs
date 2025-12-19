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
            Console.WriteLine("시작");

            try
            {
                Console.WriteLine("try실행");
                throw new Exception();
            }
            catch
            {
                Console.WriteLine("캣치~!");
            }
            finally
            {
                Console.WriteLine("finally실행");
            }
        }
    }
}
