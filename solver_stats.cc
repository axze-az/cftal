#include "ode.h"

namespace ode {
	solver_stats::solver_stats()
		: steps_(0UL),
		  accepted_(0UL),
		  rejected_(0UL),
		  fcalls_(0UL)
	{
	}

	solver_stats::~solver_stats()
	{
	}

	unsigned long solver_stats::steps() const
	{
		return steps_;
	}

	unsigned long solver_stats::accepted() const
	{
		return steps_;
	}

	unsigned long solver_stats::rejected() const
	{
		return rejected_;
	}

	unsigned long solver_stats::fcalls() const
	{
		return fcalls_;
	}

	void solver_stats::add_steps(unsigned long n) 
	{
		steps_+= n;
	}

	void solver_stats::add_accepted(unsigned long n)
	{
		accepted_+=n;
	}

	void solver_stats::add_rejected(unsigned long n)
	{
		rejected_+=n;
	}
	
	void solver_stats::add_fcalls(unsigned long n)
	{
		fcalls_+=n;
	}

	void solver_stats::add_state(unsigned long steps,
				     unsigned long accepted,
				     unsigned long rejected,
				     unsigned long fcalls)
	{
		steps_+=steps;
		accepted_+=accepted;
		rejected_+=rejected;
		fcalls_+=fcalls;
	}

	void solver_stats::reset()
	{
		steps_=0UL;
		accepted_=0UL;
		rejected_=0UL;
		fcalls_=0UL;
	}
}
