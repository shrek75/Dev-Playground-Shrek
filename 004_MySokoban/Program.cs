using System;
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace _004_MySokoban
{
    internal class Program
    {
        const int mapSizeX = 19; //맵 가로 사이즈
        const int mapSizeY = 11; //맵 세로 사이즈
        
        static char[,] loadedMap = new char[mapSizeY,mapSizeX]; //로딩한맵
        //아니 이거 왜 mapSizeY로는 할당 되면서 X까지 할려니까 안되는거임??
        // 배열의배열은 그럴필요가없으니까 안되는듯
        

        static List<Object> [,] nowMap; //오브젝트리스트의 2차원배열맵. 2차원배열로 어케함?

        void testFunc(char[] t)
        {
            t.
        }
        static void Main(string[] args)
        {

            char[] arr = new char[5];
            
            // 소코반은 FPS 개념이 필요가 없는게임이다.
            // 유저의 입력이 있을때만 Update와 Render를 돌려주면 된다.
            // 키입력확인, Update, Render / 3개의 단계로 구성된다.

            //로딩
            Console.OutputEncoding = Encoding.UTF8;

            //처음 씬 생성
            CbaseScene currentScene = new CsceneStart();
            //Player 생성
            Cplayer player = new Cplayer(new Position { _x = 0, _y = 0});

            //Player와 진행사항과 맵 로딩
            
            string t = File.ReadAllText(@"Map_sokoban\000.txt");
           // t.CopyTo(0,)
          

            //로딩한맵데이터에 따라 현재맵에 객체생성해주기
            for(int y=0; y< mapSizeY; y++)
            {
                for(int x=0; x<mapSizeX; y++)
                {
                    switch(loadedMap[y,x])
                    {
                        //player
                        case 'p':
                            //player는 좌표바꿔주기
                            player._position._x = x;
                            player._position._y = y;
                            break;

                        //Hole
                        case 'o':
                            nowMap[y,x].Add(new CHole(new Position { _x = x, _y = y }));
                            break;

                        //그냥 타일
                        case ' ':
                            break;

                        //bedrock
                        case '-':
                            nowMap[y,x].Add(new CBedrock(new Position { _x = x, _y = y }));
                            break;

                        //폭탄
                        case '!':
                            nowMap[y,x].Add(new CBomb(new Position { _x = x, _y = y }));
                            break;

                        default:
                            break;
                    }
                }
            }

            while (true)
            {

                //1. 키 입력 확인
                while (!currentScene.TryGetInput(out player._inputKey)) ;

                //2. Update
                currentScene.Update();

                //3. Render
                currentScene.Render();

                //Scene 전환이 필요하면 전환하기
                if(currentScene._changeSceneType != null)
                {
                    //근데 이게 소멸자는 언제호출되는거임?
                    currentScene = (CbaseScene)Activator.CreateInstance(currentScene._changeSceneType);
                    //다시 null로 초기화
                    currentScene._changeSceneType = null;
                }
            }


        }
    }
    
    struct Position
    {
        public int _x;
        public int _y;
    }

    //맵에 존재할 수 있는 오브젝트 전부 이 클래스를 상속하도록 함.
    class CObject
    {
        public CObject(Position pos)
        {
            _position = pos;
        }
        //오브젝트의 위치
        public Position _position;

        //기본 심볼
        public static char _symbol = 's';
    }
    class Cplayer : CObject
    {
        public Cplayer(Position pos) : base(pos)
        {
            _symbol = 'p';
        }

        //player가 가진 돈
        private int _money = 0;
        //player가 입력한 키
        public ConsoleKey _inputKey;
        //player의 stage진행상황
        public int _stage;

    }

    class CBomb : CObject
    {
        public CBomb(Position pos) : base(pos)
        {
            _symbol = '!';
        }
    }

    class CWall : CObject
    {
        public CWall(Position pos) : base(pos)
        {

        }
    }

    class CBox : CObject
    {
        public CBox(Position pos) : base(pos)
        {
        }
    }

    class CBedrock : CObject
    {
        public CBedrock(Position pos) : base(pos)
        {
            _symbol = '-';
        }
    }

    class CTile : CObject
    {
        public CTile(Position pos) : base(pos)
        {
        }
    }

    class CHole : CObject
    {
        public CHole(Position pos) : base(pos)
        {
            _symbol = 'o';
        }
    }

    class CButton : CObject
    {
        public CButton(Position pos) : base(pos)
        {
        }
    }

    class CDoor : CObject
    {
        public CDoor(Position pos) : base(pos)
        {
        }
    }





    //Scene의 부모 클래스, Scene의 공통 기능을 담당
    abstract class CbaseScene
    {
        //키입력확인 순수가상함수
        //키입력을 받으면 inputKey에 넣어주고, 게임에서 필요한 키가 입력되었는지 여부를 반환한다.
        public abstract bool TryGetInput(out ConsoleKey inputKey);
        //Update() 순수가상함수
        public abstract void Update();
        //Render() 순수가상함수
        public abstract void Render();

        //Scene 전환을 위한 변수인데 이렇게 하면되나?
        public Type _changeSceneType;

    }

    // 시작화면 Scene
    class CsceneStart : CbaseScene
    {

        public override bool TryGetInput(out ConsoleKey inputKey)
        {

            ConsoleKeyInfo keyInfo = Console.ReadKey(true);
            inputKey = keyInfo.Key;

            return inputKey == ConsoleKey.W ||
                   inputKey == ConsoleKey.A ||
                   inputKey == ConsoleKey.S ||
                   inputKey == ConsoleKey.D ||
                   inputKey == ConsoleKey.Q;

        }
        public override void Update()
        {
            string path = Directory.GetCurrentDirectory();
            Console.WriteLine( path);
        }
        public override void Render()
        {
            Console.WriteLine("SOKOBAN");
            //맵출력
            Console.WriteLine("Made by 김태욱(www.github.com/shrek75)");
            Console.WriteLine("😁😆😁🤣😗😘🤩🤢");
        }
    }
    // 상점 Scene
    class CsceneShop : CbaseScene
    {
        public override bool TryGetInput(out ConsoleKey inputKey)
        {

            ConsoleKeyInfo keyInfo = Console.ReadKey(true);
            inputKey = keyInfo.Key;

            return inputKey == ConsoleKey.W ||
                   inputKey == ConsoleKey.A ||
                   inputKey == ConsoleKey.S ||
                   inputKey == ConsoleKey.D ||
                   inputKey == ConsoleKey.Q;

        }
        public override void Update()
        {

        }
        public override void Render()
        {

        }

    }
    // 게임 Scene
    class CsceneGame : CbaseScene
    {
        public override bool TryGetInput(out ConsoleKey inputKey)
        {

            ConsoleKeyInfo keyInfo = Console.ReadKey(true);
            inputKey = keyInfo.Key;

            return inputKey == ConsoleKey.W ||
                   inputKey == ConsoleKey.A ||
                   inputKey == ConsoleKey.S ||
                   inputKey == ConsoleKey.D ||
                   inputKey == ConsoleKey.Q;

        }
        public override void Update()
        {

        }
        public override void Render()
        {

        }
    }
}
