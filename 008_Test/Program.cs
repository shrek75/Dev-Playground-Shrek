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

            Nullable<int> i1 = null;
            int? i2 = null;

            Console.WriteLine(i1.HasValue);
           // Console.WriteLine(i1.Value);
            Console.WriteLine(i2.HasValue);
            //   Console.WriteLine(i2.Value);

            string s1 = null;
            //   string? s2 = null;
            if (s1 == null) ;
            string s3 = s1 ?? "하이욤";
            Console.WriteLine(s3);

            int? x = null;
            int y = x ?? default;


            bool? unknown = null;
            if (unknown ?? true)
                Console.WriteLine("히히 NULL이거나 true였지롱");
            unknown = true;
            if(!unknown ?? true)
                Console.WriteLine("히히 근데 우선순위가 뭐부터지");

            double? d = 1.5;
            Console.WriteLine(d?.ToString());
            Console.WriteLine(d?.ToString("#.00"));

            int? len;
            string message;

            message = null;
            len = message?.Length ?? 0;
            Console.WriteLine(len);


            message = "안녕";
            len = message?.Length;
            Console.WriteLine(len);
            Console.Write("a");
            Console.Write("a");

            int[] numbers = { 1, 2, 3 };
            numbers.Sum();

            
        }

    }
}
