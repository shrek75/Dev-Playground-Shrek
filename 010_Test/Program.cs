using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Collections.Concurrent;


public class Program
{
    static void Main(string[] args)
    {
        CardDeck cardDeck = new CardDeck();
        cardDeck.MixCard();

        for (int i = 0; i < 52; i++)
        {
            cardDeck.ShowTop();
            cardDeck.Draw();
        }
        
        
    }
}

class Card
{
    public Card(Shape shape, int num)
    {
        _shape = shape;
        _number = num;
    }
    public enum Shape
    {
        Spade,
        Heart,
        Clover,
        Diamond
    }

    private Shape _shape;
    private int _number;

    //카드정보출력
    public void Print()
    {
        Console.WriteLine($"[{_number}] {_shape.ToString()} ");
    }
}
class CardDeck
{
    public CardDeck()
    {
        for (int i = 0; i < 52; i++)
        {
            _unusedCards[++_topIndex] = new Card((Card.Shape)(i / 13) , i % 13 + 1);
        }
    }

    private Card[] _usedCards = new Card[52];
    private Card[] _unusedCards = new Card[52];
    private int _topIndex = -1; //현재 unusedCards의 맨위 인덱스
    


    //맨위 카드 보기
    public void ShowTop()
    {
        Card card = _unusedCards[_topIndex];
        Console.Write($" 남은카드수-{_topIndex+1:00}\t ");
        card.Print();
    }
    //맨위 카드 뽑기
    public void Draw()
    {
        if (_topIndex < 0) return;
        _usedCards[52 - _topIndex - 1] = _unusedCards[_topIndex];
        _topIndex--;
    }

    //카드 섞기
    public void MixCard()
    {
        Random random = new Random();

        //새로운 배열 할당 (안하고 Swap으로 구현해도 되긴하는데..)
        Card[] _newArr = new Card[52];

        //현재 카드수만큼 반복
        for (int i = 0; i <= _topIndex; i++)
        {
            // 0 ~ 남은카드갯수 범위의 랜덤한 index값을 정한다.
            int index = random.Next(_topIndex - i + 1);
            // 새로운 배열의 i번째에 랜덤으로 정한 카드를 넣어준다.
            _newArr[i] = _unusedCards[index];
            // 기존배열에서 뽑힌카드의 자리에 topIndex자리의 카드를 넣어준다. 
            _unusedCards[index] = _unusedCards[_topIndex - i];
        }

        //새로운 배열을 멤버로 대입
        _unusedCards = _newArr;
    }
}
