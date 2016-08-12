#ifndef CALM_BASE_UNCOPYABLE_H_
#define CALM_BASE_UNCOPYABLE_H_
namespace calm {
	namespace details
	{
		class uncopyable
		{
		protected:
			uncopyable() {}
			~uncopyable() {}
		private:
			uncopyable(const uncopyable&);
			uncopyable& operator=(const uncopyable&);
		};
	}

	typedef details::uncopyable uncopyable;

}
#endif //CALM_BASE_UNCOPYABLE_H_