
#include <vector>
#include <algorithm>

/*
Given an NxN chessboard and a Knight at position (x,y). 
The Knight has to take exactly K steps, where at each 
step it chooses any of the 8 directions uniformly at 
random. What is the probability that the Knight remains 
in the chessboard after taking K steps, with the condition 
that it can’t enter the board again once it leaves it.
*/
struct KnightBoard
{
	double CalculateProbability(int x, int y, int n)
	{
		const int newSize = HalfArea * n;
		m_probabilityStore.clear();
		m_probabilityStore.reserve(newSize);
		m_probabilityStore.assign(newSize, -1);

		return getProbability(x, y, n);
	}

private:
	const int Side = 8;
	const int HalfSide = Side / 2;
	const int HalfArea = HalfSide * HalfSide;

	constexpr bool onBoard(int x, int y)
	{
		return x >= 0 && x < Side && y >= 0 && y < Side;
	}

	void mirror(int& x, int& y)
	{
		x = std::min(x, Side - 1 - x);
		y = std::min(y, Side - 1 - y);
	}

	const int getStoreIndex(int x, int y, int n)
	{
		mirror(x, y);
		return (n - 1) * HalfArea + x * HalfSide + y;
	}

	double storedProbability(int x, int y, int n)
	{
		return m_probabilityStore[getStoreIndex(x, y, n)];
	}

	void storeProbability(int x, int y, int n, double value)
	{
		m_probabilityStore[getStoreIndex(x, y, n)] = value;
	}

	double getProbability(int x, int y, int n)
	{
		if (!onBoard(x, y))
			return 0;

		if (n == 0)
			return 1;

		if (double p = storedProbability(x, y, n); p != -1)
			return p;

		double p = (
			getProbability(x - 2, y - 1, n - 1)
			+ getProbability(x - 2, y + 1, n - 1)
			+ getProbability(x + 2, y - 1, n - 1)
			+ getProbability(x + 2, y + 1, n - 1)
			+ getProbability(x - 1, y - 2, n - 1)
			+ getProbability(x + 1, y - 2, n - 1)
			+ getProbability(x - 1, y + 2, n - 1)
			+ getProbability(x + 1, y + 2, n - 1)
			) / 8;

		storeProbability(x, y, n, p);
		return p;
	}

	std::vector<double> m_probabilityStore;
};
