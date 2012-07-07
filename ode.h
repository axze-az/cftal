#if !defined (__ODE_H__)
#define __ODE_H__ 1

namespace ode {
	class solver_stats {
	private:
		unsigned long steps_;
		unsigned long accepted_;
		unsigned long rejected_;
		unsigned long fcalls_;
	public:
		solver_stats();
		~solver_stats();
		unsigned long steps() const;
		unsigned long accepted() const;
		unsigned long rejected() const;
		unsigned long fcalls() const;
		void add_steps(unsigned long n);
		void add_accepted(unsigned long n);
		void add_rejected(unsigned long n);
		void add_fcalls(unsigned long n);
		void add_state(unsigned long steps,
			       unsigned long accepted,
			       unsigned long rejected,
			       unsigned long fcalls);
		void reset();
	};

	template <typename C>
	class solver_param {
	public:
		typedef typename C::value_type value_type;
		solver_param( const value_type& x0, 
			      const value_type& xE, 
			      const value_type& h0,
			      const C& abserr, 
			      const C& relerr);
		~solver_param();
		const value_type& x0() const;
		const value_type& xe() const;
		const value_type& h0() const;
		const C& abserr() const;
		const C& relerr() const;
	private:
		value_type x0_;
		value_type xe_;
		value_type h0_;
		C abserr_;
		C relerr_;
	};
	
	template <typename Container> 
	struct DglFunc {
		bool operator() ( Container& res, 
				  typename Container::value_type const& x,
				  const Container& y);
	};

	template <typename Container>
	struct dense_output {
	};

	template <typename C, typename DglFunc>
	class ode_solver {
	public:
		typedef typename C::value_type value_type;
	private:
		ode_solver();
		ode_solver(const ode_solver& r);
		ode_solver& operator=(const ode_solver& r);
	protected:
		const DglFunc& fcn_;
		value_type h_;
		value_type xnm1_;
		value_type xn_;
		solver_stats stats_;
	public:
		ode_solver( const DglFunc& fcn);
		bool solve( const solver_param<C>& param,
			    solver_stats& stats);
		bool solve( const solver_param<C>& param,
			    dense_output<C>& output,
			    solver_stats& stats);
		const value_type& x() const;
	};






// 	class ode_solver {
// 	private:
// 		long nfcn_;
// 		long nstep_;
// 		long naccpt_;
// 		long nrejct_;
// 		fpn hout_;
// 		fpn xold_;
// 		fpn xout_;
// 		unsigned nrds;
// 	public:
// 		virtual contd(unsigned ii, const T& x);
// 		const T& x() const;
// 		const T& h() const;
// 		long steps() const;
// 		long naccpt() const;
// 		long nrejct() const;
// 		long nfcn() const;
// 	};

// 	class dop853 : public ode_solver {
// 	public:
// 	};

// 	class dop54_solver : public ode_solver {
// 	public:
// 	};
}

/*
 * Local variables:
 * mode: c++
 */
#endif
