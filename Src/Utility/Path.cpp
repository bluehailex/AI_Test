#include "Path.h"

namespace ait
{
	Path::Path(int wayPointCount, double minX, double minY, double maxX, double maxY, bool looped)
	{
		CreateRandomPath(wayPointCount, minX, minY, maxX, maxY);
		mCurrentWaypoint = mWaypoints.begin();
	}


	std::list< Vector2D<double> > Path::CreateRandomPath(int wayPointCount, double minX, double minY, double maxX, double maxY)
	{
		mWaypoints.clear();

		double midX = (maxX+minX)/2.0;
		double midY = (maxY+minY)/2.0;

		double smaller = Min(midX, midY);
		double spacing = PI*2.0/(double)wayPointCount;

		for (int n=0; n<wayPointCount; n++)
		{
			double radialDist = RandInRange(smaller*0.2f, smaller);
			Vector2D<double> temp(radialDist, 0.0f);
			temp.x += midX;
			temp.y += midY;

			mWaypoints.push_back(temp);
		}

		return mWaypoints;
	}

	void Path::Set(std::list< Vector2D<double> > newPath)
	{
		mWaypoints = newPath;
		mCurrentWaypoint = mWaypoints.begin();
	}

	void Path::Set(Path path)
	{
		mWaypoints = path.GetPath();
		mCurrentWaypoint = mWaypoints.begin();
	}


	void Path::Draw()
	{
		//TODO implement
	}


	void Path::AddWaypoint(Vector2D<double> newWayPoint)
	{
		mWaypoints.push_back(newWayPoint);//TODO this was an implied implementation
	}

	Vector2D<double> Path::GetCurrentWaypoint()
	{
		return *mCurrentWaypoint;
	}

	void Path::SetNextWaypoint()
	{
		if (++mCurrentWaypoint == mWaypoints.end())
		{
			if (mLooped)
				mCurrentWaypoint = mWaypoints.begin();
		}
	}
};