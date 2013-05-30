#include "..\Main.h"

#ifndef _aitest_STEERING_BEHAVIOR_H
#define _aitest_STEERING_BEHAVIOR_H

namespace ait
{
	//the radius of the constraining circle for the wander behavior
	const double gWanderRadius = 1.2;

	//the distance the wander circle is projected in front of the angent
	const double gWanderDistance = 2.0;

	//the maximium amount of displacement along the circle each frame
	const double gWanderJitterPerSec = 80.0;

	//used in path following
	const double gWaypointSeekDistance = 20.0;


	class SteeringBehavior
	{
	public:
		enum SummingMethod
		{
			WeightedAverage,
			Prioritized,
			Dithered
		};

	private:
		enum BehaviorType
		{
			None				= 0x00000,
			Seek				= 0x00002,
			Flee				= 0x00004,
			Arrive				= 0x00008,
			Wander				= 0x00010,
			Cohesion			= 0x00020,
			Separation			= 0x00040,
			Allignment			= 0x00080,
			ObstacleAvoidance	= 0x00100,
			WallAvoidance		= 0x00200,
			FollowPath			= 0x00400,
			Pursuit				= 0x00800,
			Evade				= 0x01000,
			Interpose			= 0x02000,
			Hide				= 0x04000,
			Flock				= 0x08000,
			OffsetPursuit		= 0x10000
		};

		Vehicle *mVehicle;
		Vehicle *mTargetAgent1;
		Vehicle *mTargetAgent2;

		Vector2D<double> mSteeringForce;
		Vector2D<double> mTarget;
		double mBoxLength;
	
		std::vector< Vector2D<double> > mFeelers;
		double mWallDetectionFeelerLength;
		Vector2D<double> mWanderTarget;

		double mWanderJitter;
		double mWanderRadius;
		double mWanderDistance;

		//multipliers that effect the strength of the appropriate behavior
		double mWeightSeparation;
		double mWidthCohesion;
		double mWeightAlignment;
		double mWeightWander;
		double mWeightObstacleAvoidance;
		double mWeightWallAvoidance;
		double mWeightSeek;
		double mWeightFlee;
		double mWeightArrive;
		double mWeightPursuit;
		double mWeightOffsetPursuit;
		double mWeightInterpose;
		double mWeightHide;
		double mWeightEvade;
		double mWeightFollowPath;

		double mViewDistance;

		Path *mPath;

		double mWaypointSeekDistanceSq;
		Vector2D<double> mOffset;
		int mFlags;

		enum Deceleration { Slow = 3, Normal = 2, Fast = 1 };
		Deceleration mDeceleration;

		bool mCellSpaceOn;
		SummingMethod mSummingMethod;

		//methods
		bool On(BehaviorType behaviorType) { return (mFlags & behaviorType) == behaviorType; }
		bool AccumulateForce(Vector2D<double> &sf, Vector2D<double> forceToAdd);
		void CreateFeelers();

		//TODO all these private methods are going to need a '_' prefix or should be made public
		//behavior methods
		Vector2D<double> Seek(Vector2D<double> targetPos);
		Vector2D<double> Flee(Vector2D<double> targetPos);
		Vector2D<double> Arrive(Vector2D<double> targetPos, Deceleration deceleration);
		Vector2D<double> Pursuit(const Vehicle *agent);
		Vector2D<double> OffsetPursuit(const Vehicle *agent, const Vector2D<double> offset);
		Vector2D<double> Evade(const Vehicle *agent);
		Vector2D<double> Wander();
		Vector2D<double> ObstacleAvoidance(const std::vector<Entity*> &obstacles);
		Vector2D<double> WallAvoidance(const std::vector<Wall2D> &walls);
		Vector2D<double> FollowPath();
		Vector2D<double> Interpose(const Vehicle *vehicleA, const Vehicle *vehicleB);
		Vector2D<double> Hide(const Vehicle *hunter, const std::vector<Entity*> &obstacles);

		Vector2D<double> Cohesion(const std::vector<Vehicle*> &agents);
		Vector2D<double> Separation(const std::vector<Vehicle*> &agents);
		Vector2D<double> Alignment(const std::vector<Vehicle*> &agents);

		Vector2D<double> CohesionPlus(const std::vector<Vehicle*> &agents);
		Vector2D<double> SeparationPlus(const std::vector<Vehicle*> &agents);
		Vector2D<double> AlignmentPlus(const std::vector<Vehicle*> &agents);
	};
};

#endif

