# include <Siv3D.hpp> // OpenSiv3D v0.6.6

struct MotionKey
{
	int32 time;        // 移動開始する時間[ms]
	Vec2 to;           // 移動先
	double smoothTime;
};

struct Motion
{
	Array<MotionKey> keys;

	const MotionKey& get(int32 time_ms) const
	{
		return *(std::upper_bound(keys.cbegin(), keys.cend(), time_ms, [](int32 a, const MotionKey& b) { return a < b.time; }) - 1);
	}
};

const Array<Motion> MOTION = {
   {
	   {
		   {0, Vec2(400, 400), 0.8},
		   {3000, Vec2(200, 200), 0.5},
		   {4500, Vec2(600, 200), 0.5},
		   {6000, Vec2(100, 100), 0.5},
		   {7000, Vec2(700, 100), 0.5},
		   {8000, Vec2(700, 500), 0.5},
		   {9000, Vec2(100, 500), 0.5},
		   {10000, Vec2(100, 500), 0.5},
		   {12000, Vec2(100, -100), 1.0},
	   }
   },
};

class Enemy
{
	Vec2 m_pos;
	Vec2 m_vel;
	Vec2 m_posTo;
	const Motion& m_motion;
	Stopwatch m_time{ StartImmediately::Yes };

public:
	Enemy(const Vec2& pos, const Motion& motion) : m_pos(pos), m_vel(), m_posTo(pos), m_motion(motion)
	{
	}

	void update()
	{
		const auto& m = m_motion.get(m_time.ms());
		m_posTo = m.to;
		m_pos = Math::SmoothDamp(m_pos, m_posTo, m_vel, m.smoothTime, unspecified, Scene::DeltaTime());
	}

	void draw() const
	{
		RectF(60)
			.setCenter(m_pos)
			.rotated(m_time.sF() * (0.8 + Math::Log(1 + m_vel.length()) * 0.6))
			.draw(ColorF(0.30));
	}
};

void Main_motion()
{
	Scene::SetBackground(ColorF(0.95, 0.95, 0.95));

	Enemy enemy{ Vec2(400, -200), MOTION[0] };

	while (System::Update())
	{
		enemy.update();
		enemy.draw();

		for (const auto& key : MOTION[0].keys)
		{
			Circle(key.to, 8).draw(ColorF(0.5, 0.5));
		}
	}
}
