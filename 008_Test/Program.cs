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
            Random random = new Random();

            //로또 당첨번호 만들기
            int[] lotto = new int[6];
            for(int i = 0; i < 6; i++)
            {
                lotto[i] = random.Next(1, 46);
                for(int j=0;j<i;j++)
                {
                    if (lotto[j] == lotto[i])
                    {
                        i--;
                        break;
                    }
                }
            }
            //로또번호 정렬
            var iter1 = lotto.OrderBy(x => x);
   
            int count = 0; //몇번 반복하는지 count

            //1등당첨될때까지 반복
            while (true)
            {
                count++;
                if(count % 1_000_000 == 0) Console.WriteLine($"{count:#,#}회 구매했습니다.");

                // 내 로또번호 뽑기
                int[] myLotto = new int[6];
                for (int i = 0; i < 6; i++)
                {
                    myLotto[i] = random.Next(1, 46);
                    for (int j = 0; j < i; j++)
                    {
                        if (myLotto[j] == myLotto[i])
                        {
                            i--;
                            break;
                        }
                    }
                }

                //내 로또번호 정렬
                var iter2 = myLotto.OrderBy(x => x);
                iter2.ElementAt(0);

                //비교
                if (iter1.SequenceEqual(iter2)) break;
            }

            Console.WriteLine($"count : {count}");
            Console.WriteLine($"{((long)1000 * count):c} 원 사용");

        }



    }
    
    
}
