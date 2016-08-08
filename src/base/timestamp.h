#ifndef CALM_BASE_TIMESTAMP_H_
#define CALM_BASE_TIMESTAMP_H_

#include <copyable.h>
#include <types.h>


namespace calm
{
	class Timestamp :calm::copyable
	{
	public:
		Timestamp()
			:microSecondsSinceEpoch_(0)
		{}
		explicit Timestamp(int64_t microSecondsSinceEpochArg)
			: microSecondsSinceEpoch_(microSecondsSinceEpochArg)
		{}
		void swap(Timestamp& that)
		{
			std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
		}
		std::string toString() const;
		std::string toFormattedString(bool showMicro) const;
	private:
		int64_t microSecondsSinceEpoch_;
	};// end class Timestamp 
}// end namespace calm

#endif //CALM_BASE_TIMESTAMP_H_