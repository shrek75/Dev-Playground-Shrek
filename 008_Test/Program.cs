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

            MyClass c = new MyClass();
            c.MyProperty = 1;
            Console.WriteLine(c.MyProperty);
            c.MyProp = 2;
            Console.WriteLine(c.MyProp);
          //  c.MyProp2 = 3;



            Console.WriteLine(c.MyProp2);
            Console.WriteLine(MyClass.Name);

            var anony = new { name = "김태욱", age = 27, height = 166 };
            Console.WriteLine(anony.name);
        }
        static void Hello() => Console.WriteLine("Hello");
        static int Doub(int x) => x * 2;
        
        
        
    }
    class MyClass
    {
        public int MyProperty { get; set; }
        private int MyValue { get; set; }

        private int myprop = 4; 
        public int MyProp
        {
            get { return myprop; }
            set {  myprop = value; }
        }

        public static string Name { get; set; } = "Hello";

        public int MyProp2 { get; } = 3;

        public int Age { get; private set; }
        
        
    }
}
