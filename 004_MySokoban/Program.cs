using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _004_MySokoban
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // 소코반은 FPS 개념이 필요가 없는게임이다.
            // 유저의 입력이 있을때만 Update와 Render를 돌려주면 된다.
            // 키입력확인, Update, Render / 3개의 단계로 구성된다.

            //로딩

            //처음 씬 생성
            CbaseScene currentScene = new CsceneStart();
            //Player 생성
            Cplayer player = new Cplayer();

            //Player와 진행사항과 맵 로딩

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
        public int X;
        public int Y;
    }

    class Cplayer
    {
        //player의 모습
        private char _symbol = 'P';
        //player가 가진 돈
        private int _money = 0;
        //player의 좌표
        private Position _position = new Position { X = 0, Y = 0 };
        //player가 입력한 키
        public ConsoleKey _inputKey;
        //player의 stage진행상황
        public int _stage;

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
            
        }
        public override void Render()
        {
            Console.WriteLine("SOKOBAN");
            //맵출력
            Console.WriteLine("Made by 김태욱(www.github.com/shrek75)");
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
