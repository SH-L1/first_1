#pragma once

// 보스에 어그로 시스템이 추가
// 1. 어그로라는게 무엇(무슨 정보가 필요한가)
// - 누가 때렸는지
// - 얼만큼 때렸는지

struct PlayerInfo
{
	bool operator<(const PlayerInfo& other) const
	{
		if (totalDamage < other.totalDamage)
			return true;
		return false;
	}

	weak_ptr<Creature>	player;
	int			totalDamage;
};

class Boss : public Goblin
{
public:
	Boss(int hp, int atk);

	void BossRangeAttack();
	virtual void TakeDamage(shared_ptr<Creature> attcker, int amount) override;

private:
	void AggroUI();

	vector<PlayerInfo> _playerTable;

	int _attackRange = 4;
};

