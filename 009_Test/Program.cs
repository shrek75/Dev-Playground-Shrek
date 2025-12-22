using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _009_Test
{
    internal class Program
    {
        static void Main(string[] args)
        {
            MyClass m = new MyClass();
            Console.WriteLine(m.MyMoney);
            m.MyHealth = 2;
            m.height = 3;
        }
    }
    class MyClass
    {
        int myMoney = 0;
        public int MyMoney
        {
            get { return myMoney; }
            set { myMoney = value; }
        }
        public int MyHealth { get; set; } = 100;

        public int height = 200;
    }
}
