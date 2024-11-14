#include "../framework.h"
#include "Knight.h"

// Knight는 자기체력이 50프로 이하일 때 공격력 2배
Knight::Knight(int hp, int atk, string name)
// 자식의 생성자에서 암시적으로 부모의 기본생성자를 호출
: Player(hp, atk, name)
, _maxHp(hp)
{
// 부모의 멤버변수는 빠른 초기화 영역에서 초기화하지 못한다.
}

Knight::~Knight()
{
}

void Knight::Attack(shared_ptr<Creature> other)
{
	// :: 범위 지정 연산자
	Creature::Attack(other);

	// maxHp
	// hp
	float ratio = (float)_hp / (float)_maxHp;
	if (ratio < 0.5f)
	{
		cout << "Knight의 연속 공격!!!" << endl;
		Creature::Attack(other);
	}
}
