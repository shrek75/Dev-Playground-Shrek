using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;

namespace _006_c_다차원배열__c__다차원배열_차이점
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //2차원char배열 myArray 선언 및 할당
            char[,] myArray = new char[5, 10];

            //Func함수를 호출하고싶은데 컴파일에러가 뜹니다.
            Func(myArray[3]);    // 왜 안되나요? myArray[3]이면 char[] 형식 아닌가요?
            Func(&(myArray[3, 0])); // 왜 안되나요? &(myArray[3,0])이면 char[] 형식 아닌가요?
        }
        void Func(char[] arr)
        {

        }
    }
}

