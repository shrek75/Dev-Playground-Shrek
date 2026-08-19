using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _015_게임구조생각
{
    internal class SceneManager
    {
        private bool quitRequested = false;
        private 
        //SceneManager에게 게임종료를 요청하는 메서드
        public void RequestQuit()
        {
            quitRequested = true;
        }
        
        //현재 활성화된 Scene을 돌려주는 메서드
        public bool Run()
        {

            if (quitRequested) return false;
            return true;
        }

    }


}
