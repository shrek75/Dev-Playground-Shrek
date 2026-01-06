using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _013_Test
{
    internal class Program
    {
        static void Main(string[] args)
        {
            d.Solution("LULLLLLLU");
        }
    }
    
    
    public static class d
    {
        struct Pos
        {
            public int x;
            public int y;
        }
        public static int Solution(string dirs)
        {

            HashSet<Pos> SetRight = new HashSet<Pos>();
            HashSet<Pos> SetUp = new HashSet<Pos>();
            
            Pos nowPos = new Pos { x = 0, y = 0 };
            Pos plusPos = new Pos();
            foreach (char c in dirs)
            {
                switch(c)
                {
                    case 'U': { plusPos.x = 0; plusPos.y = 1; break; }
                    case 'D': { plusPos.x = 0; plusPos.y = -1; break; }
                    case 'R': { plusPos.x = 1; plusPos.y = 0; break; }
                    case 'L': { plusPos.x = -1; plusPos.y = 0; break; }
                }

                if (nowPos.x + plusPos.x > 5 || nowPos.x + plusPos.x < -5) continue;
                if (nowPos.y + plusPos.y > 5 || nowPos.y + plusPos.y < -5) continue;

                if(plusPos.y == 1) SetUp.Add(nowPos);
                if(plusPos.x == 1) SetRight.Add(nowPos);
                nowPos.x += plusPos.x;
                nowPos.y += plusPos.y;

                if(plusPos.y == -1) SetUp.Add(nowPos);
                if (plusPos.x == -1) SetRight.Add(nowPos);

            }


            return SetUp.Count + SetRight.Count;


        }
    }
}
