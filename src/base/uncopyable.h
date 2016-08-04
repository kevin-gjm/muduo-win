#ifndef CALM_BASE_UNCOPYABLE_H_
#define CALM_BASE_UNCOPYABLE_H_

namespace clam
{
	class uncopyable
	{
	protected:
		uncopyable() {}
		~uncopyable() {}
	private:  
		uncopyable(const uncopyable&);
		const uncopyable& operator=(const uncopyable&);
	};
}

#endif //CALM_BASE_UNCOPYABLE_H_