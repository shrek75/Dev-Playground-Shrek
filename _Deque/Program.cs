using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _Deque
{
    internal class Program
    {
        static void Main(string[] args)
        {
            MyDeque<int> _deque = new MyDeque<int>();
            _deque.PushBack(1);
            _deque.PushBack(2);
            _deque.PushFront(3);
            _deque.PushFront(4);
            _deque.PushFront(5);
            // 54312
            Console.WriteLine(_deque.PopFront());
            Console.WriteLine(_deque.PopBack());
            Console.WriteLine(_deque.PopBack());


            Console.WriteLine(_deque.PopBack());
            Console.WriteLine(_deque.PopBack());


        }
    }

    //배열의 요소가 0개일 때 _front == -1 , _rear == -1
    //배열의 요소가 1개일 때 _front == _rear (-1은 아닌값)
    //배열이 꽉찼을 때       _front == _rear + 1
    class MyDeque<T>
    {
        private T[] _arr;
        private int _front = -1;
        private int _rear = -1;
        private int _capacity = 0;
        public MyDeque(int capacity = 10)
        {
            _arr = new T[capacity];
            _capacity = capacity;
        }

        //target기준 한칸 왼쪽 인덱스값을 얻어온다.
        private int GetLeftIndex(int target)
        {
            return target != 0 ? target - 1 : _capacity - 1;
        }
        //target기준 한칸 오른쪽 인덱스값을 얻어온다.
        private int GetRightIndex(int target)
        {
            return target != _capacity -1 ? target + 1 : 0;
        }

        //배열이 꽉찼을 때는 2배로 재할당한다.
        private void ReAlloc()
        {
            T[] newArr = new T[_capacity * 2];

            int i = 0;
            //재할당했으니 복사해주기
            while(_front != _rear)
            {
                newArr[i] = _arr[_front];
                _front = GetRightIndex(_front);
                i++;
            }

            //멤버 초기화
            _arr = newArr;
            _front = 0;
            _rear = _capacity - 1; 
        }

        

        public void PushFront(T element)
        {

            //배열에 아무값도 없을 때
            if (_front == -1 || _rear == -1)
            {
                _front = 1; //pushFront할때 front 왼쪽으로 한칸 옮길거라서 1로 초기화.
                _rear = 0;
            }

            //혹은 배열이 꽉차있을 때
            else if(GetRightIndex(_rear) == _front)
            {
                //새로할당
                ReAlloc();
            }

            //예외처리했으니 일반적인상황이 되었다.
            _front = GetLeftIndex(_front); 
            _arr[_front] = element;
        }

        public void PushBack(T element)
        {
            //배열에 아무값도 없을 때
            if (_front == -1 || _rear == -1)
            {
                _front = 0; 
                _rear = -1; //pushBack할때 _rear을 오른쪽으로 한칸 옮길거라서 -1로 초기화.
            }

            //혹은 배열이 꽉차있을 때
            else if (GetRightIndex(_rear) == _front)
            {
                //새로할당
                ReAlloc();
            }

            //예외처리했으니 일반적인상황이 되었다.
            _rear = GetRightIndex(_rear);
            _arr[_rear] = element;
        }
        public T PopFront() 
        {
            int ret = _front;

            //배열이 비었을 때
            if (_front == -1 || _rear == -1)
            {
                //이렇게 해도되나? 이러면 int가 0인데
                // return default(T);

                //그냥 예외던지자
                throw new Exception();
            }
            //배열에 1개만있을 때
            else if(_front == _rear)
            {
                _front = -1;
                _rear = -1;
                return _arr[ret];
            }

            //일반적인상황
            _front = GetRightIndex(ret);
            return _arr[ret];
        }
        
        public T PopBack()
        {
            int ret = _rear;

            //배열이 비었을 때
            if (_front == -1 || _rear == -1)
            {
                //return default(T);

                throw new Exception();
            }
            //배열에 1개만있을 때
            else if (_front == _rear)
            {
                _front = -1;
                _rear = -1;
                return _arr[ret];
            }

            //일반적인상황
            _rear = GetLeftIndex(ret);
            return _arr[ret];
        }

        public void Clear()
        {
            _front = -1;
            _rear = -1 ;
        }
        
    }
}







