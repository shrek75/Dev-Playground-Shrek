using System;
using System.Linq;

public class Solution
{
    
    static void Main(string[] args)
    {
        MyClass.Func();
        MyClass myClass = new MyClass();
       
    }
}

class MyClass
{
    public static void Func()
    {
        Console.WriteLine("Hello");
    }

    public class m2
    {
        public static void Func2()
        {
            Console.WriteLine("Hello");
        }
    }
    class m3 : m2
    {
        public static void Func3()
        {
            Console.WriteLine("Hello");
        }
    }
}
