using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web;

namespace _009_Test
{
    class Trainer
    {

        //생성자
        public Trainer(string name)
        {
            _name = name;
        }

        //몬스터 최대마리수
        private const int MAX_MONSTER = 6;

        //이름
        private string _name;
        //몬스터가방
        private Monster[] _myMonsters = new Monster[MAX_MONSTER];
        //몬스터 몇마리 있는지
        private int _monstersCount = 0;

        //현재 필드에 있는 몬스터. 이렇게하면 걍 GetValue같은 메서드처럼 동작하는건가
        private Monster SelectedMonster
        {
            get
            {
                return _myMonsters[0]; 
            }
        }
        
        
        public bool Add(Monster monster)
        {
            //최대마리수면 return
            if (_monstersCount == MAX_MONSTER) return false;


            _myMonsters[_monstersCount++] = monster;
            return true;
        }
        
        //Remove 버전1. 매개변수 monster
        public bool Remove(Monster monster)
        {
            int deleteIndex = -1;

            //몬스터 없으면 삭제안해요.
            if (_monstersCount == 0) return false;

            for (int i=0; i<_monstersCount;i++)
            {
                //삭제할려는 거 찾았으면
                if(_myMonsters[i] == monster)
                {
                    deleteIndex = i;
                    break;
                }
            }
            //삭제할려는거 못찾았으면 삭제안해요.
            if(deleteIndex == -1) return false;

            //배열땡기기로 삭제          
            _monstersCount--;
            for (int i = deleteIndex; i < _monstersCount; i++)
            {
                _myMonsters[i] = _myMonsters[i + 1];
            }
            return true;
        }

        //Remove 버전2. index로 삭제
        public bool Remove(int index)
        {

            //몬스터 없으면 삭제안해요.
            if (_monstersCount == 0) return false;

            //인덱스 잘못되도 삭제안해요.
            if (index < 0 || index >= _monstersCount) return false;

            //배열땡기기로 삭제          
            _monstersCount--;
            for (int i = index; i < _monstersCount; i++)
            {
                _myMonsters[i] = _myMonsters[i + 1];
            }
            return true;
        }
        
        public void PrintAll()
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine($"\n현재 {_name}님이 보유하신 몬스터는 총 {_monstersCount} 마리 입니다.");
            Console.ResetColor();
            Console.WriteLine($"---------------------------------------------------");
            for(int i=0; i<_monstersCount; i++)
            {
                _myMonsters[i].Print();
            }
            Console.WriteLine($"---------------------------------------------------\n");

        }
        
        //나와있는 몬스터에게 공격명령내리기
        public void Attack()
        {
            SelectedMonster?.Attack();
        }
       
        //나와있는 몬스터에게 스킬쓰게하기
        public void Skill()
        {
            SelectedMonster?.Skill();
        }
       
    }

    class Monster
    {

        //class밖에서 생성못하게 막고, 하위클래스에서는 Monster()호출 허용.
        protected Monster(string name, int level)
        {
            _name = name;
            _level = level;
        }

        private int _level;
        protected string _name;
        protected int _power = 1;

        //몬스터 정보 출력
        public void Print()
        {
            Console.WriteLine($"레벨 [ {_level} ]\t 공격력 [ {_power} ]\t 이름 [ {_name} ]");
        }
        
        //몬스터 공격기능
        public void Attack()
        {
            Console.WriteLine($"[ {_name} ] : [ {_level * _power} ] 데미지로 공격");
        }

        //몬스터 스킬기능
        public virtual void Skill()
        {
            Console.WriteLine("기본스킬 입니다");
        }
    }

    class LongStone : Monster
    {
        public LongStone(string name, int level = 50) : base(name, level) { }
        public override void Skill()
        {
            Console.WriteLine($"가랏! {_name}의 돌떨구기!");
        }
    }
    class Picachu : Monster
    {
        public Picachu(string name, int level = 10) : base(name, level) { }
        public override void Skill()
        {
            Console.WriteLine($"가랏! {_name}의 백만볼트!");
        }
    }
    class Bul : Monster
    {
        public Bul(string name, int level = 33) : base(name, level) { }
        public override void Skill()
        {
            Console.WriteLine($"가랏! {_name}의 불대문자!");
        }
    }

    class Legend : Monster
    {
        public Legend(string name, int level = 100) : base(name, level) { }
        public override void Skill()
        {
            Console.WriteLine($"가랏! {_name}의 전설빔!");
        }
    }

    class Ori : Monster
    {
        public Ori(string name, int level = 0) : base(name, level) { }
        public override void Skill()
        {
            Console.WriteLine($"가랏! {_name}의 파닥거리기!");
        }
    }

    class P
    {
        static void Main(string[] args)
        {
            Console.WriteLine($"포켓몬 월드에 온 걸 환영한다!");
            Console.WriteLine($".");
            Console.Write($"너의 이름을 알려줘! 이름 : ");
            string input = Console.ReadLine();

            Trainer taeuk = new Trainer(input);

            taeuk.Add(new LongStone("롱스톤"));
            taeuk.Add(new Picachu("피카츄"));
            taeuk.Add(new Bul("불꽃숭이"));
            taeuk.Add(new Legend("레전드"));
            taeuk.Add(new Ori("오리"));



            taeuk.PrintAll();
            for (int i = 0; i < 5; i++)
            {
                taeuk.Skill();
                taeuk.Attack();
                taeuk.Remove(0);
            }
            taeuk.PrintAll();

        }

    }

}
