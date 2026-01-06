using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _014_TEST
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Solution solution = new Solution();
            string[] p = { "SOO", "OOO", "OOO" };
            string[] r = { "E 2", "S 2", "W 1" };

            Console.WriteLine(solution.solution(p, r)[0]);
            Console.WriteLine(solution.solution(p, r)[1]);

        }
        public class Solution
        {
            public int[] solution(string[] park, string[] routes)
            {
                //S위치
                int[] answer = new int[] { -1, -1 };


                for(int i=0; i< park.Length; i++)
                {
                    for(int j=0; j < park[i].Length; j++ )
                    {
                        if (park[i][j] == 'S')
                        {
                            answer[0] = i;
                            answer[1] = j;
                            i = park.Length;
                            break;
                        }
                    }
                }

                foreach(string s in routes)
                {
                    //s : "E 2"
                    int targetX = answer[1];
                    int targetY = answer[0];

                    switch(s[0])
                    {
                        case 'E':
                            //범위벗어나면 원래대로
                            if (targetX + (s[2] - 48) > park[0].Length - 1) break;
                            for(int i =0; i < s[2] - 48; i++)
                            {
                                //X발견하면 원래대로
                                if (park[targetY][++targetX] == 'X')
                                {
                                    targetX = answer[1];
                                    break;
                                }
                            }
                            answer[1] = targetX;
                            answer[0] = targetY;
                            break;
                        case 'W':
                            //범위벗어나면 원래대로
                            if (targetX - (s[2] - 48) < 0) break;
                            for (int i = 0; i < s[2] - 48; i++)
                            {
                                //X발견하면 원래대로
                                if (park[targetY][--targetX] == 'X')
                                {
                                    targetX = answer[1];
                                    break;
                                }
                            }
                            answer[1] = targetX;
                            answer[0] = targetY;
                            break;
                        case 'S':
                            //범위벗어나면 원래대로
                            if (targetY + (s[2] - 48) > park.Length - 1) break;
                            for (int i = 0; i < s[2] - 48; i++)
                            {
                                //X발견하면 원래대로
                                if (park[++targetY][targetX] == 'X')
                                {
                                    targetY = answer[0];
                                    break;
                                }
                            }
                            answer[1] = targetX;
                            answer[0] = targetY;
                            break;
                        case 'N':
                            //범위벗어나면 원래대로
                            if (targetY - (s[2] - 48) < 0) break;
                            for (int i = 0; i < s[2] - 48; i++)
                            {
                                //X발견하면 원래대로
                                if (park[--targetY][targetX] == 'X')
                                {
                                    targetY = answer[0];
                                    break;
                                }
                            }
                            answer[1] = targetX;
                            answer[0] = targetY;
                            break;
                    }

                   
                }

                return answer;
            }
        }
    }
}
