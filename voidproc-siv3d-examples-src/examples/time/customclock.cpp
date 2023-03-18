// Stopwatchを一括して停止・再開したり、遅く／速く進行させる（ISteadyClockの実装例）

#include <Siv3D.hpp> // OpenSiv3D v0.6.7

class CustomClock : public ISteadyClock
{
public:
	CustomClock(StartImmediately startImmediately = StartImmediately::No)
		: m_clock{ startImmediately }
	{
	}

	virtual ~CustomClock() {}

	virtual uint64 getMicrosec() override
	{
		return m_clock.us64();
	}

	void start()
	{
		m_clock.start();
	}

	void pause()
	{
		m_clock.pause();
	}

	bool isPaused() const
	{
		return m_clock.isPaused();
	}

	void setSpeed(const double speed)
	{
		m_clock.setSpeed(speed);
	}

	double getSpeed() const
	{
		return m_clock.getSpeed();
	}

private:
	VariableSpeedStopwatch m_clock;
};

void Main_customclock()
{
	Scene::SetBackground(ColorF{ 0, 0, 0 });

	Font font{ 32, Typeface::Medium };

	// 基準時刻
	CustomClock clock{ StartImmediately::Yes };

	// これらを一括で停止したり再開したり、速度を変えたりしたい
	Stopwatch stopwatch1{ StartImmediately::Yes, &clock };
	VariableSpeedStopwatch stopwatch2{ 0.3, StartImmediately::Yes, &clock };
	VariableSpeedStopwatch stopwatch3{ 1.5, StartImmediately::Yes, &clock };

	while (System::Update())
	{
		// [Enter]で停止・再開
		if (KeyEnter.down())
		{
			if (clock.isPaused())
			{
				clock.start();
			}
			else
			{
				clock.pause();
			}
		}

		// [↑][↓]でスピードアップ・ダウン
		const double clockSpeed = clock.getSpeed();

		if (KeyUp.down())
		{
			clock.setSpeed(Clamp(clockSpeed + 0.2, 0.2, 4.0));
		}
		else if (KeyDown.down())
		{
			clock.setSpeed(Clamp(clockSpeed - 0.2, 0.2, 4.0));
		}

		font(U"Speed: {:.1f}"_fmt(clock.getSpeed())).draw(8, 8);
		font(clock.isPaused() ? U"(Paused)" : U"").draw(200, 8);
		font(U"Stopwatch1: {:.1f}"_fmt(stopwatch1.sF())).draw(8, 24 + (32 + 12) * 1);
		font(U"Stopwatch2: {:.1f}"_fmt(stopwatch2.sF())).draw(8, 24 + (32 + 12) * 2);
		font(U"Stopwatch3: {:.1f}"_fmt(stopwatch3.sF())).draw(8, 24 + (32 + 12) * 3);
	}
}
